/*
 XboxElite2ControlCenter v1.5
 Native Win32/GDI diagnostic UI for Xbox Elite Series 2.
 Target: Windows XP SP3 x86 through Windows 11 (WoW64).

 Runtime:
 - local xinput1_3.dll is preferred (XInputBridgeXP v2.3 in this package)
 - physical RAW state is read from the XInputBridgeXP diagnostic extension; WinMM is fallback
 - no .NET, Qt, WebView, browser or VC++ redistributable required
*/

typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef short SHORT;
typedef unsigned long DWORD;
typedef unsigned int UINT;
typedef unsigned long ULONG;
typedef long LONG;
typedef int BOOL;
typedef unsigned long MMRESULT;
typedef unsigned long COLORREF;
typedef long LPARAM;
typedef unsigned int WPARAM;
typedef long LRESULT;
typedef unsigned short ATOM;
typedef void* HANDLE;
typedef void* HINSTANCE;
typedef void* HMODULE;
typedef void* HWND;
typedef void* HDC;
typedef void* HGDIOBJ;
typedef void* HBRUSH;
typedef void* HPEN;
typedef void* HFONT;
typedef void* HICON;
typedef void* HCURSOR;
typedef void* HMENU;
typedef void* HBITMAP;
typedef void* PVOID;
typedef unsigned int UINT_PTR;
typedef LONG (__stdcall *WNDPROC)(HWND,UINT,WPARAM,LPARAM);

#define NULL 0
#define TRUE 1
#define FALSE 0
#define MAX_PATH 260
#define MAXPNAMELEN 32
#define MAX_JOYSTICKOEMVXDNAME 260

#define ERROR_SUCCESS 0UL
#define ERROR_DEVICE_NOT_CONNECTED 1167UL
#define JOYERR_NOERROR 0
#define JOY_RETURNALL 0x000000FFUL
#define JOY_POVCENTERED 0xFFFFUL

#define WM_DESTROY 0x0002
#define WM_PAINT 0x000F
#define WM_ERASEBKGND 0x0014
#define WM_TIMER 0x0113
#define WM_LBUTTONDOWN 0x0201
#define CS_VREDRAW 0x0001
#define CS_HREDRAW 0x0002
#define SW_SHOW 5
#define WS_CAPTION 0x00C00000UL
#define WS_SYSMENU 0x00080000UL
#define WS_MINIMIZEBOX 0x00020000UL
#define WS_CLIPCHILDREN 0x02000000UL
#define WS_CLIPSIBLINGS 0x04000000UL
#define CW_USEDEFAULT ((int)0x80000000)
#define TRANSPARENT 1
#define PS_SOLID 0
#define SRCCOPY 0x00CC0020UL
#define DT_LEFT 0x00000000
#define DT_CENTER 0x00000001
#define DT_RIGHT 0x00000002
#define DT_VCENTER 0x00000004
#define DT_SINGLELINE 0x00000020
#define DT_END_ELLIPSIS 0x00008000
#define DEFAULT_GUI_FONT 17
#define FW_NORMAL 400
#define FW_SEMIBOLD 600
#define FW_BOLD 700
#define DEFAULT_CHARSET 1
#define OUT_DEFAULT_PRECIS 0
#define CLIP_DEFAULT_PRECIS 0
#define CLEARTYPE_QUALITY 5
#define DEFAULT_PITCH 0
#define FF_DONTCARE 0
#define IDC_ARROW 32512
#define IDI_APPLICATION 32512
#define MB_OK 0x00000000UL
#define MB_ICONERROR 0x00000010UL
#define OFN_FILEMUSTEXIST 0x00001000UL
#define OFN_PATHMUSTEXIST 0x00000800UL
#define OFN_HIDEREADONLY  0x00000004UL
#define SW_SHOWNORMAL 1
#define INVALID_FILE_ATTRIBUTES 0xFFFFFFFFUL
#define FILE_ATTRIBUTE_DIRECTORY 0x00000010UL
