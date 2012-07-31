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

DECLARE_WM(WM_NULL);
DECLARE_WM(WM_CREATE);
DECLARE_WM(WM_DESTROY);
DECLARE_WM(WM_MOVE);
DECLARE_WM(WM_SIZE);
DECLARE_WM(WM_ACTIVATE);
DECLARE_WM(WM_SETFOCUS);
DECLARE_WM(WM_KILLFOCUS);
DECLARE_WM(WM_ENABLE);
DECLARE_WM(WM_SETREDRAW);
DECLARE_WM(WM_SETTEXT);
DECLARE_WM(WM_GETTEXT);
DECLARE_WM(WM_GETTEXTLENGTH);
DECLARE_WM(WM_PAINT);
DECLARE_WM(WM_CLOSE);
DECLARE_WM(WM_QUERYENDSESSION);
DECLARE_WM(WM_QUIT);
DECLARE_WM(WM_QUERYOPEN);
DECLARE_WM(WM_ERASEBKGND);
DECLARE_WM(WM_SYSCOLORCHANGE);
DECLARE_WM(WM_ENDSESSION);
DECLARE_WM(WM_SHOWWINDOW);
DECLARE_WM(WM_WININICHANGE);
DECLARE_WM(WM_DEVMODECHANGE);
DECLARE_WM(WM_ACTIVATEAPP);
DECLARE_WM(WM_FONTCHANGE);
DECLARE_WM(WM_TIMECHANGE);
DECLARE_WM(WM_CANCELMODE);
DECLARE_WM(WM_SETCURSOR);
DECLARE_WM(WM_MOUSEACTIVATE);
DECLARE_WM(WM_CHILDACTIVATE);
DECLARE_WM(WM_QUEUESYNC);
DECLARE_WM(WM_GETMINMAXINFO);
DECLARE_WM(WM_PAINTICON);
DECLARE_WM(WM_ICONERASEBKGND);
DECLARE_WM(WM_NEXTDLGCTL);
DECLARE_WM(WM_SPOOLERSTATUS);
DECLARE_WM(WM_DRAWITEM);
DECLARE_WM(WM_MEASUREITEM);
DECLARE_WM(WM_DELETEITEM);
DECLARE_WM(WM_VKEYTOITEM);
DECLARE_WM(WM_CHARTOITEM);
DECLARE_WM(WM_SETFONT);
DECLARE_WM(WM_GETFONT);
DECLARE_WM(WM_SETHOTKEY);
DECLARE_WM(WM_GETHOTKEY);
DECLARE_WM(WM_QUERYDRAGICON);
DECLARE_WM(WM_COMPAREITEM);
DECLARE_WM(WM_GETOBJECT);
DECLARE_WM(WM_COMPACTING);
DECLARE_WM(WM_COMMNOTIFY);
DECLARE_WM(WM_WINDOWPOSCHANGING);
DECLARE_WM(WM_WINDOWPOSCHANGED);
DECLARE_WM(WM_POWER);
DECLARE_WM(WM_COPYDATA);
DECLARE_WM(WM_CANCELJOURNAL);
DECLARE_WM(WM_NOTIFY);
DECLARE_WM(WM_INPUTLANGCHANGEREQUEST);
DECLARE_WM(WM_INPUTLANGCHANGE);
DECLARE_WM(WM_TCARD);
DECLARE_WM(WM_HELP);
DECLARE_WM(WM_USERCHANGED);
DECLARE_WM(WM_NOTIFYFORMAT);
DECLARE_WM(WM_CONTEXTMENU);
DECLARE_WM(WM_STYLECHANGING);
DECLARE_WM(WM_STYLECHANGED);
DECLARE_WM(WM_DISPLAYCHANGE);
DECLARE_WM(WM_GETICON);
DECLARE_WM(WM_SETICON);
DECLARE_WM(WM_NCCREATE);
DECLARE_WM(WM_NCDESTROY);
DECLARE_WM(WM_NCCALCSIZE);
DECLARE_WM(WM_NCHITTEST);
DECLARE_WM(WM_NCPAINT);
DECLARE_WM(WM_NCACTIVATE);
DECLARE_WM(WM_GETDLGCODE);
DECLARE_WM(WM_SYNCPAINT);
DECLARE_WM(WM_NCMOUSEMOVE);
DECLARE_WM(WM_NCLBUTTONDOWN);
DECLARE_WM(WM_NCLBUTTONUP);
DECLARE_WM(WM_NCLBUTTONDBLCLK);
DECLARE_WM(WM_NCRBUTTONDOWN);
DECLARE_WM(WM_NCRBUTTONUP);
DECLARE_WM(WM_NCRBUTTONDBLCLK);
DECLARE_WM(WM_NCMBUTTONDOWN);
DECLARE_WM(WM_NCMBUTTONUP);
DECLARE_WM(WM_NCMBUTTONDBLCLK);
DECLARE_WM(WM_NCXBUTTONDOWN);
DECLARE_WM(WM_NCXBUTTONUP);
DECLARE_WM(WM_NCXBUTTONDBLCLK);
DECLARE_WM(WM_INPUT);
DECLARE_WM(WM_KEYDOWN);
DECLARE_WM(WM_KEYUP);
DECLARE_WM(WM_CHAR);
DECLARE_WM(WM_DEADCHAR);
DECLARE_WM(WM_SYSKEYDOWN);
DECLARE_WM(WM_SYSKEYUP);
DECLARE_WM(WM_SYSCHAR);
DECLARE_WM(WM_SYSDEADCHAR);
DECLARE_WM(WM_KEYLAST);
DECLARE_WM(WM_IME_STARTCOMPOSITION);
DECLARE_WM(WM_IME_ENDCOMPOSITION);
DECLARE_WM(WM_IME_COMPOSITION);
DECLARE_WM(WM_INITDIALOG);
DECLARE_WM(WM_COMMAND);
DECLARE_WM(WM_SYSCOMMAND);
DECLARE_WM(WM_TIMER);
DECLARE_WM(WM_HSCROLL);
DECLARE_WM(WM_VSCROLL);
DECLARE_WM(WM_INITMENU);
DECLARE_WM(WM_INITMENUPOPUP);
DECLARE_WM(WM_MENUSELECT);
DECLARE_WM(WM_MENUCHAR);
DECLARE_WM(WM_ENTERIDLE);
DECLARE_WM(WM_MENURBUTTONUP);
DECLARE_WM(WM_MENUDRAG);
DECLARE_WM(WM_MENUGETOBJECT);
DECLARE_WM(WM_UNINITMENUPOPUP);
DECLARE_WM(WM_MENUCOMMAND);
DECLARE_WM(WM_CHANGEUISTATE);
DECLARE_WM(WM_UPDATEUISTATE);
DECLARE_WM(WM_QUERYUISTATE);
DECLARE_WM(WM_CTLCOLORMSGBOX);
DECLARE_WM(WM_CTLCOLOREDIT);
DECLARE_WM(WM_CTLCOLORLISTBOX);
DECLARE_WM(WM_CTLCOLORBTN);
DECLARE_WM(WM_CTLCOLORDLG);
DECLARE_WM(WM_CTLCOLORSCROLLBAR);
DECLARE_WM(WM_CTLCOLORSTATIC);
DECLARE_WM(WM_MOUSEFIRST);
DECLARE_WM(WM_LBUTTONDOWN);
DECLARE_WM(WM_LBUTTONUP);
DECLARE_WM(WM_LBUTTONDBLCLK);
DECLARE_WM(WM_RBUTTONDOWN);
DECLARE_WM(WM_RBUTTONUP);
DECLARE_WM(WM_RBUTTONDBLCLK);
DECLARE_WM(WM_MBUTTONDOWN);
DECLARE_WM(WM_MBUTTONUP);
DECLARE_WM(WM_MBUTTONDBLCLK);
DECLARE_WM(WM_MOUSELAST);
DECLARE_WM(WM_MOUSEWHEEL);
DECLARE_WM(WM_XBUTTONDOWN);
DECLARE_WM(WM_XBUTTONUP);
DECLARE_WM(WM_XBUTTONDBLCLK);
DECLARE_WM(WM_PARENTNOTIFY);
DECLARE_WM(WM_ENTERMENULOOP);
DECLARE_WM(WM_EXITMENULOOP);
DECLARE_WM(WM_NEXTMENU);
DECLARE_WM(WM_SIZING);
DECLARE_WM(WM_CAPTURECHANGED);
DECLARE_WM(WM_MOVING);
DECLARE_WM(WM_POWERBROADCAST);
DECLARE_WM(WM_DEVICECHANGE);
DECLARE_WM(WM_MDICREATE);
DECLARE_WM(WM_MDIDESTROY);
DECLARE_WM(WM_MDIACTIVATE);
DECLARE_WM(WM_MDIRESTORE);
DECLARE_WM(WM_MDINEXT);
DECLARE_WM(WM_MDIMAXIMIZE);
DECLARE_WM(WM_MDITILE);
DECLARE_WM(WM_MDICASCADE);
DECLARE_WM(WM_MDIICONARRANGE);
DECLARE_WM(WM_MDIGETACTIVE);
DECLARE_WM(WM_MDISETMENU);
DECLARE_WM(WM_ENTERSIZEMOVE);
DECLARE_WM(WM_EXITSIZEMOVE);
DECLARE_WM(WM_DROPFILES);
DECLARE_WM(WM_MDIREFRESHMENU);
DECLARE_WM(WM_IME_SETCONTEXT);
DECLARE_WM(WM_IME_CONTROL);
DECLARE_WM(WM_IME_COMPOSITIONFULL);
DECLARE_WM(WM_IME_SELECT);
DECLARE_WM(WM_IME_CHAR);
DECLARE_WM(WM_IME_REQUEST);
DECLARE_WM(WM_IME_KEYDOWN);
DECLARE_WM(WM_IME_KEYUP);
DECLARE_WM(WM_NCMOUSEHOVER);
DECLARE_WM(WM_MOUSEHOVER);
DECLARE_WM(WM_NCMOUSELEAVE);
DECLARE_WM(WM_MOUSELEAVE);
DECLARE_WM(WM_CUT);
DECLARE_WM(WM_COPY);
DECLARE_WM(WM_PASTE);
DECLARE_WM(WM_CLEAR);
DECLARE_WM(WM_UNDO);
DECLARE_WM(WM_RENDERFORMAT);
DECLARE_WM(WM_RENDERALLFORMATS);
DECLARE_WM(WM_DRAWCLIPBOARD);
DECLARE_WM(WM_PAINTCLIPBOARD);
DECLARE_WM(WM_VSCROLLCLIPBOARD);
DECLARE_WM(WM_SIZECLIPBOARD);
DECLARE_WM(WM_ASKCBFORMATNAME);
DECLARE_WM(WM_CHANGECBCHAIN);
DECLARE_WM(WM_HSCROLLCLIPBOARD);
DECLARE_WM(WM_QUERYNEWPALETTE);
DECLARE_WM(WM_PALETTEISCHANGING);
DECLARE_WM(WM_PALETTECHANGED);
DECLARE_WM(WM_HOTKEY);
DECLARE_WM(WM_PRINT);
DECLARE_WM(WM_PRINTCLIENT);
DECLARE_WM(WM_APPCOMMAND);
DECLARE_WM(WM_HANDHELDFIRST);
DECLARE_WM(WM_HANDHELDLAST);
DECLARE_WM(WM_AFXFIRST);
DECLARE_WM(WM_AFXLAST);
DECLARE_WM(WM_PENWINLAST);
DECLARE_WM(DM_GETDEFID);
DECLARE_WM(DM_SETDEFID);
DECLARE_WM(DM_REPOSITION);
DECLARE_WM(WM_APP);