/* imports */
extern "C" {
__declspec(dllimport) void __stdcall ExitProcess(DWORD);
__declspec(dllimport) HMODULE __stdcall GetModuleHandleA(const char*);
__declspec(dllimport) HMODULE __stdcall LoadLibraryA(const char*);
__declspec(dllimport) void* __stdcall GetProcAddress(HMODULE,const char*);
__declspec(dllimport) DWORD __stdcall GetModuleFileNameA(HMODULE,char*,DWORD);
__declspec(dllimport) BOOL __stdcall SetCurrentDirectoryA(const char*);
__declspec(dllimport) DWORD __stdcall GetTickCount(void);
__declspec(dllimport) void __stdcall GetLocalTime(SYSTEMTIME*);
__declspec(dllimport) UINT __stdcall GetPrivateProfileIntA(const char*,const char*,int,const char*);
__declspec(dllimport) BOOL __stdcall WritePrivateProfileStringA(const char*,const char*,const char*,const char*);

__declspec(dllimport) ATOM __stdcall RegisterClassExA(const WNDCLASSEXA*);
__declspec(dllimport) HWND __stdcall CreateWindowExA(DWORD,const char*,const char*,DWORD,int,int,int,int,HWND,HMENU,HINSTANCE,PVOID);
__declspec(dllimport) LRESULT __stdcall DefWindowProcA(HWND,UINT,WPARAM,LPARAM);
__declspec(dllimport) BOOL __stdcall ShowWindow(HWND,int);
__declspec(dllimport) BOOL __stdcall UpdateWindow(HWND);
__declspec(dllimport) BOOL __stdcall GetMessageA(MSG*,HWND,UINT,UINT);
__declspec(dllimport) BOOL __stdcall TranslateMessage(const MSG*);
__declspec(dllimport) LRESULT __stdcall DispatchMessageA(const MSG*);
__declspec(dllimport) void __stdcall PostQuitMessage(int);
__declspec(dllimport) UINT_PTR __stdcall SetTimer(HWND,UINT_PTR,UINT,PVOID);
__declspec(dllimport) BOOL __stdcall KillTimer(HWND,UINT_PTR);
__declspec(dllimport) BOOL __stdcall InvalidateRect(HWND,const RECT*,BOOL);
__declspec(dllimport) HDC __stdcall BeginPaint(HWND,PAINTSTRUCT*);
__declspec(dllimport) BOOL __stdcall EndPaint(HWND,const PAINTSTRUCT*);
__declspec(dllimport) BOOL __stdcall GetClientRect(HWND,RECT*);
__declspec(dllimport) HCURSOR __stdcall LoadCursorA(HINSTANCE,const char*);
__declspec(dllimport) HICON __stdcall LoadIconA(HINSTANCE,const char*);
__declspec(dllimport) int __stdcall FillRect(HDC,const RECT*,HBRUSH);
__declspec(dllimport) int __stdcall DrawTextA(HDC,const char*,int,RECT*,UINT);
__declspec(dllimport) int __stdcall MessageBoxA(HWND,const char*,const char*,UINT);

__declspec(dllimport) HBRUSH __stdcall CreateSolidBrush(COLORREF);
__declspec(dllimport) BOOL __stdcall DeleteObject(HGDIOBJ);
__declspec(dllimport) HGDIOBJ __stdcall SelectObject(HDC,HGDIOBJ);
__declspec(dllimport) int __stdcall SetBkMode(HDC,int);
__declspec(dllimport) COLORREF __stdcall SetTextColor(HDC,COLORREF);
__declspec(dllimport) HFONT __stdcall CreateFontA(int,int,int,int,int,DWORD,DWORD,DWORD,DWORD,DWORD,DWORD,DWORD,DWORD,const char*);
__declspec(dllimport) BOOL __stdcall RoundRect(HDC,int,int,int,int,int,int);
__declspec(dllimport) BOOL __stdcall Rectangle(HDC,int,int,int,int);
__declspec(dllimport) BOOL __stdcall Ellipse(HDC,int,int,int,int);
__declspec(dllimport) HPEN __stdcall CreatePen(int,int,COLORREF);
__declspec(dllimport) BOOL __stdcall MoveToEx(HDC,int,int,POINT*);
__declspec(dllimport) BOOL __stdcall LineTo(HDC,int,int);
__declspec(dllimport) HDC __stdcall CreateCompatibleDC(HDC);
__declspec(dllimport) HBITMAP __stdcall CreateCompatibleBitmap(HDC,int,int);
__declspec(dllimport) BOOL __stdcall DeleteDC(HDC);
__declspec(dllimport) BOOL __stdcall BitBlt(HDC,int,int,int,int,HDC,int,int,DWORD);

__declspec(dllimport) int __cdecl sprintf(char*,const char*,...);
__declspec(dllimport) void* __cdecl fopen(const char*,const char*);
__declspec(dllimport) int __cdecl fclose(void*);
__declspec(dllimport) int __cdecl fprintf(void*,const char*,...);
__declspec(dllimport) int __cdecl fflush(void*);
__declspec(dllimport) void* __cdecl memset(void*,int,unsigned int);

}

/* palette */
static COLORREF C_BG      = RGB_(18,22,28);
static COLORREF C_PANEL   = RGB_(28,34,42);
static COLORREF C_PANEL2  = RGB_(35,42,51);
static COLORREF C_LINE    = RGB_(55,64,76);
static COLORREF C_TEXT    = RGB_(235,239,244);
static COLORREF C_MUTED   = RGB_(154,166,181);
static COLORREF C_BLUE    = RGB_(65,145,255);
static COLORREF C_GREEN   = RGB_(63,203,132);
static COLORREF C_YELLOW  = RGB_(244,190,73);
static COLORREF C_RED     = RGB_(238,92,92);
static COLORREF C_OFF     = RGB_(68,77,90);

static HWND g_hwnd=NULL;
static HFONT g_font14=NULL,g_font16=NULL,g_font20=NULL,g_font12=NULL;
static PFN_XInputGetState g_xget=NULL;
static PFN_XInputSetState g_xset=NULL;
static PFN_XInputBridgeGetRawState g_xraw=NULL;
static PFN_XInputBridgeReloadConfig g_xreload=NULL;
static PFN_joyGetNumDevs g_jnum=NULL;
static PFN_joyGetDevCapsA g_jcaps=NULL;
static PFN_joyGetPosEx g_jpos=NULL;
static HMODULE g_xmod=NULL,g_winmm=NULL;
static int g_joyId=-1;
static JOYCAPSA g_caps;
static XINPUT_STATE g_xstate;
static JOYINFOEX g_raw;
static DWORD g_xret=ERROR_DEVICE_NOT_CONNECTED;
static MMRESULT g_jret=1;
static DWORD g_bridgeRawRet=ERROR_DEVICE_NOT_CONNECTED;
static int g_rawSource=0; /* 0 none, 1 bridge extension, 2 direct WinMM */
static int g_rawEver=0;
static char g_backend[96]="No XInput";
static char g_device[96]="No joystick";
static char g_os[96]="Windows";
static int g_testState=TEST_IDLE;
static DWORD g_testStart=0,g_recordStart=0,g_lastCsv=0;
static void* g_csv=NULL;
static void* g_log=NULL;
static char g_baseName[96]="";
static char g_status[160]="Listo. Presiona INICIAR PRUEBA.";
static DWORD g_rumbleStopAt=0;
static DWORD g_rumbleLastRet=ERROR_DEVICE_NOT_CONNECTED;
static DWORD g_rumbleCommands=0;
static WORD g_rumbleLeft=0,g_rumbleRight=0;
