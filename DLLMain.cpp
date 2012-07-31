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

static FILE* g_DebugLog = 0;
static WNDPROC g_OldWndProc = 0;

#define DEF_PROC DefWindowProcA(hwnd, msg, wParam, lParam);
#define SKYRIM_PROC g_OldWndProc(hwnd, msg, wParam, lParam);

//////////////////////////////////////////////////////////////////////////////

static void DebugMsg(const char* fmt, ...)
{
    if (!g_DebugLog) return;
    va_list args;
    va_start(args, fmt);
    vfprintf_s(g_DebugLog, fmt, args);
    fputs("\r\n", g_DebugLog);
    _fflush_nolock(g_DebugLog);
}

//////////////////////////////////////////////////////////////////////////////

// Enable this to pass through ALL window messages and see what Skyrim does
// with them. Useful for when you're too slack to use IDA.
//#define SKYRIM_PROC_INVESTIGATION

static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
#ifdef SKYRIM_PROC_INVESTIGATION
    /* Thar be majick here -- I remembered this from DS >.< */
    switch (msg)
    {
#define DECLARE_WM(x) \
    case x: \
    { \
        LRESULT r = SKYRIM_PROC; \
        DebugMsg("-> " #x); \
        DebugMsg("  -> wParam: %X", wParam); \
        DebugMsg("  -> lParam: %X", lParam); \
        DebugMsg("  -> RETURN VALUE: %X", r); \
        return r; \
    }
#include "WM.inl"
    default:
        return SKYRIM_PROC;
    }
#endif

#ifndef SKYRIM_PROC_INVESTIGATION
    switch (msg)
    {
    case WM_ACTIVATE:
        if (wParam != WA_INACTIVE)
            for (int i = ShowCursor(FALSE); i >= 0; i = ShowCursor(FALSE));
        return DEF_PROC;
    case WM_ACTIVATEAPP:
        DebugMsg("WM_ACTIVATEAPP %X %X", wParam, GetWindowLongA(hwnd, GWL_STYLE));
        if (wParam)
        {
            LONG ws = GetWindowLongA(hwnd, GWL_STYLE) & ~WS_MINIMIZE;
            SetWindowLongA(hwnd, GWL_STYLE, ws);
        }
        return SKYRIM_PROC;
    default:
        return SKYRIM_PROC;
    }
#endif
}

static BOOL CALLBACK _enum_hwnds(HWND hwnd, LPARAM lParam)
{
    DWORD wPid = 0;
    GetWindowThreadProcessId(hwnd, &wPid);
    if (GetCurrentProcessId() == wPid)
    {
        wchar_t title[MAX_PATH]; // longer than MAX_PATH? GTH.
        GetWindowTextW(hwnd, title, MAX_PATH);
        g_OldWndProc = (WNDPROC)GetWindowLongPtrA(hwnd, GWLP_WNDPROC);
        if (g_OldWndProc)
        {
            DebugMsg("    Original WndProc: %S@%X", title, g_OldWndProc);
            SetWindowLongPtrA(hwnd, GWLP_WNDPROC, (LONG)WndProc);
            return FALSE;
        }
        else
        {
            DebugMsg("    Ignored: %S", title);
            return TRUE;
        }
    }
    return TRUE;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason)
    {
    case DLL_PROCESS_ATTACH:
        g_DebugLog = fopen("skylaunch.log", "w");
        DebugMsg("Attached to TESV.exe");

        // Try to override the WndProc
        DebugMsg("---WndProc Override---\r\n    New WndProc: %X", WndProc);
        EnumWindows(_enum_hwnds, 0);
        if (g_OldWndProc)
        {
            DebugMsg("---WndProc Success---");
            return TRUE;
        }
        else
        {
            DebugMsg("---WndProc Failed---");
            return FALSE;
        }
        break;
    case DLL_PROCESS_DETACH:
        DebugMsg("Unloading DLL");
        if (g_DebugLog)
            fclose(g_DebugLog);
        break;
    }

    return TRUE;
}