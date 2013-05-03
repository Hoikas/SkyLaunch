/* Copyright (C) 2012 Adam Johnson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
*/

#include "SkyLaunch.hpp"

#include <Shlwapi.h>
#include <tlhelp32.h>
#include <tuple>

static HANDLE    g_SkyrimProcess = 0;
static bool      g_SkyrimReady = false;

#define MAKE_PATH(ptr, base, add) \
    std::wstring ptr = base; \
    ptr += L"\\"; \
    ptr += add;
#define TEST_SKYRIM_EXE(e) \
    { \
        MAKE_PATH(test, data, e); \
        if (PathFileExistsW(test.c_str())) \
            return std::make_tuple(data, e); \
    }
static std::tuple<std::wstring, std::wstring> find_skyrim()
{
    // find the path to skyrim from the registry
    DWORD type = 0;
    wchar_t data[MAX_PATH];
    DWORD size = sizeof(data) * sizeof(wchar_t);
    if (RegGetValueW(HKEY_CURRENT_USER, L"Software\\Valve\\Steam", L"SteamPath",
        RRF_RT_REG_SZ, &type, &data, &size) == SL_OK)
    {
        if (!PathFileExistsW(data))
        {
            SL_DERROR("steam directory bogus");
            return std::make_tuple(L"", L"");
        }
        PathAppendW(data, L"steamapps\\common\\skyrim");
        if (!PathFileExistsW(data))
        {
            SL_DERROR("skyrim directory missing");
            return std::make_tuple(L"", L"");
        }
        TEST_SKYRIM_EXE(L"skse_loader.exe"); // lots of people use SkyUI
        TEST_SKYRIM_EXE(L"SkyrimLauncher.exe")
        SL_DERROR("No Skyrim EXE found!");
    }
    return std::make_pair(nullptr, nullptr);
}

static bool launch_skyrim(std::tuple<std::wstring, std::wstring> path)
{
    std::wstring& dir = std::get<0>(path);
    std::wstring& exe = std::get<1>(path);
    MAKE_PATH(skyrim, dir, exe);

    STARTUPINFOW info;
    memset(&info, 0, sizeof(info));
    info.cb = sizeof(info);
    PROCESS_INFORMATION garbage; // will be handles to the launcher. trash.

    BOOL ret = CreateProcessW(skyrim.c_str(), 0, 0, 0, TRUE, CREATE_NO_WINDOW | NORMAL_PRIORITY_CLASS,
                              0, dir.c_str(), &info, &garbage);
    CloseHandle(garbage.hProcess);
    CloseHandle(garbage.hThread);
    return ret != 0;
}

static void find_process_handle()
{
    do
    {
        // We want to check all the processes for TESV.exe-ness
        PROCESSENTRY32W entry;
        entry.dwSize = sizeof(PROCESSENTRY32W);
        HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        SL_ASSERT(Process32FirstW(snapshot, &entry), "failed to open SYSTEM process");
        while (Process32NextW(snapshot, &entry) == TRUE)
        {
            if (wcscmp(entry.szExeFile, L"TESV.exe") == 0)
            {
                g_SkyrimProcess = OpenProcess(PROCESS_ALL_ACCESS, TRUE, entry.th32ProcessID);
                SL_ASSERT(g_SkyrimProcess, "failed to open TESV.exe");
            }
        }

        CloseHandle(snapshot);

        // Don't thrash the CPU
        if (!g_SkyrimProcess)
            Sleep(500);
    } while (!g_SkyrimProcess);
}

static BOOL CALLBACK _hwnd_callback(HWND hwnd, LPARAM lParam)
{
    DWORD pid = 0;
    GetWindowThreadProcessId(hwnd, &pid);
    if (pid == GetProcessId(g_SkyrimProcess))
        g_SkyrimReady = true;
    return (BOOL)g_SkyrimReady;
}

static bool inject_dll()
{
    // For some reason, this explodes if the skyrim window isn't running.
    // So let's look for the Skyrim window before we inject our DLL
    do
    {
        EnumWindows(_hwnd_callback, 0);
        Sleep(2000); // wait a bit for the window to be fully initialized
    } while (!g_SkyrimReady);

    // objective: create a remote thread that executes ::LoadLibrary on our
    // dll that contains our wndproc
    // NOTE: working dirs might be different, so we need the full path here
    wchar_t dll[MAX_PATH * 2]; memset(dll, 0, MAX_PATH * 2);
    SL_FAIL(GetCurrentDirectoryW(MAX_PATH, dll), "failed to get current directory");
    wcscat_s(dll, L"\\SkyLaunchHook.dll");
    SL_ASSERT(PathFileExistsW(dll), "hook dll not found");

    // Need to alloc the DLL name into the remote process.
    SIZE_T bytesToWrite = wcslen(dll) * sizeof(wchar_t);
    SIZE_T bytesWritten = 0;
    void* rPtr = VirtualAllocEx(g_SkyrimProcess, 0, bytesToWrite, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    SL_FAIL(rPtr, "failed to allocate remote memory");
    WriteProcessMemory(g_SkyrimProcess, rPtr, dll, bytesToWrite, &bytesWritten);
    SL_FAIL(bytesToWrite == bytesWritten, "WriteProcessMemory failed");

    // Now, create the hack thread :D
    FARPROC proc = GetProcAddress(GetModuleHandle("kernel32.dll"), "LoadLibraryW");
    HANDLE thread = CreateRemoteThread(g_SkyrimProcess, 0, 0, (LPTHREAD_START_ROUTINE)proc, rPtr, 0, 0);
    CloseHandle(thread);
    return true;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    std::tuple<std::wstring, std::wstring> path = find_skyrim();
    if (std::get<0>(path).empty() || std::get<0>(path).empty())
    {
        SL_ERROR("Couldn't find Skyrim.");
        return SL_OK;
    }
    if (!launch_skyrim(path))
    {
        SL_ERROR("Failed to launch Skyrim. Please contact the SkyLaunch Team.");
        return SL_OK;
    }
    find_process_handle();
    if (!inject_dll())
    {
        SL_ERROR("Failed to hook into Skyrim. Please contact the SkyLaunch Team.");
        return SL_OK;
    }
    return SL_OK;
}

