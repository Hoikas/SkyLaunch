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

#ifndef _SKYLAUNCH_INC
#define _SKYLAUNCH_INC

/* BIG TODO NOTE
 * This was once in a precompiled header...
 * Then I rearranged stuff. Need to put it back in a PCH.
 */
#include <crtdbg.h>
#include <cstdio>
#include <cstring>
#include <string>
#include <utility>

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>
/* End "BIG TODO NOTE" */

#define SL_OK 0
#define SL_ERR 1

inline int ErrorDialog(const char* msg, const char* file, int line)
{
#ifdef _DEBUG
    int result = _CrtDbgReport(_CRT_ASSERT, file, line, 0, msg);
    switch (result)
    {
    case -1:
        DebugBreak();
        return SL_ERR;
    case 0:
        return SL_OK;
    case 1:
        DebugBreak();
        return SL_OK;
    }
#else
    MessageBoxA(0, msg, "SkyLaunch Error", MB_OK | MB_ICONERROR);
    return SL_ERR;
#endif
}

#ifdef _DEBUG
#   define SL_ASSERT(cond, msg) if (cond == 0) ErrorDialog(msg, __FILE__, __LINE__)
#   define SL_DERROR(msg) ErrorDialog(msg, __FILE__, __LINE__)
#   define SL_ERROR(msg) ErrorDialog(msg, __FILE__, __LINE__)
#   define SL_FAIL(cond, assertmsg) \
        if (cond == 0) { \
            ErrorDialog(assertmsg, __FILE__, __LINE__); \
            return false; \
        }
#else
#   define SL_ASSERT(cond, msg) __noop
#   define SL_DERROR(msg) __noop
#   define SL_ERROR(msg) ErrorDialog(msg, nullptr, -1)
#   define SL_FAIL(cond, assertmsg) if (cond == 0) return false;
#endif

#endif // _SKYLAUNCH_INC
