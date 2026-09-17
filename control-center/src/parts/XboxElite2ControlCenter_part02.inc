#define XINPUT_GAMEPAD_DPAD_UP        0x0001
#define XINPUT_GAMEPAD_DPAD_DOWN      0x0002
#define XINPUT_GAMEPAD_DPAD_LEFT      0x0004
#define XINPUT_GAMEPAD_DPAD_RIGHT     0x0008
#define XINPUT_GAMEPAD_START          0x0010
#define XINPUT_GAMEPAD_BACK           0x0020
#define XINPUT_GAMEPAD_LEFT_THUMB     0x0040
#define XINPUT_GAMEPAD_RIGHT_THUMB    0x0080
#define XINPUT_GAMEPAD_LEFT_SHOULDER  0x0100
#define XINPUT_GAMEPAD_RIGHT_SHOULDER 0x0200
#define XINPUT_GAMEPAD_GUIDE          0x0400
#define XINPUT_GAMEPAD_A              0x1000
#define XINPUT_GAMEPAD_B              0x2000
#define XINPUT_GAMEPAD_X              0x4000
#define XINPUT_GAMEPAD_Y              0x8000

#define TIMER_ID 1
#define TIMER_MS 20
#define TEST_IDLE 0
#define TEST_BASELINE 1
#define TEST_RUNNING 2
#define TEST_COMPLETE 3

#define RGB_(r,g,b) ((COLORREF)(((BYTE)(r)) | ((WORD)((BYTE)(g))<<8) | (((DWORD)(BYTE)(b))<<16)))
#define LOWORD_(l) ((WORD)((DWORD)(l)&0xffff))
#define HIWORD_(l) ((WORD)((DWORD)(l)>>16))
#define GET_X_LPARAM_(lp) ((int)(short)LOWORD_(lp))
#define GET_Y_LPARAM_(lp) ((int)(short)HIWORD_(lp))
#define MAKEINTRESOURCEA_(i) ((const char*)((ULONG)((WORD)(i))))

#pragma pack(push,1)
typedef struct { WORD wButtons; BYTE bLeftTrigger; BYTE bRightTrigger; SHORT sThumbLX; SHORT sThumbLY; SHORT sThumbRX; SHORT sThumbRY; } XINPUT_GAMEPAD;
typedef struct { DWORD dwPacketNumber; XINPUT_GAMEPAD Gamepad; } XINPUT_STATE;
typedef struct { WORD wLeftMotorSpeed; WORD wRightMotorSpeed; } XINPUT_VIBRATION;
#pragma pack(pop)

typedef struct { LONG left,top,right,bottom; } RECT;
typedef struct { LONG x,y; } POINT;
typedef struct { HWND hwnd; UINT message; WPARAM wParam; LPARAM lParam; DWORD time; POINT pt; } MSG;
typedef struct { HDC hdc; BOOL fErase; RECT rcPaint; BOOL fRestore; BOOL fIncUpdate; BYTE rgbReserved[32]; } PAINTSTRUCT;
typedef struct {
 UINT cbSize; UINT style; WNDPROC lpfnWndProc; int cbClsExtra; int cbWndExtra; HINSTANCE hInstance;
 HICON hIcon; HCURSOR hCursor; HBRUSH hbrBackground; const char* lpszMenuName; const char* lpszClassName; HICON hIconSm;
} WNDCLASSEXA;
typedef struct { WORD wYear,wMonth,wDayOfWeek,wDay,wHour,wMinute,wSecond,wMilliseconds; } SYSTEMTIME;

typedef struct {
 WORD wMid,wPid; char szPname[MAXPNAMELEN];
 UINT wXmin,wXmax,wYmin,wYmax,wZmin,wZmax,wNumButtons,wPeriodMin,wPeriodMax;
 UINT wRmin,wRmax,wUmin,wUmax,wVmin,wVmax,wCaps,wMaxAxes,wNumAxes,wMaxButtons;
 char szRegKey[MAXPNAMELEN]; char szOEMVxD[MAX_JOYSTICKOEMVXDNAME];
} JOYCAPSA;
typedef struct { DWORD dwSize,dwFlags,dwXpos,dwYpos,dwZpos,dwRpos,dwUpos,dwVpos,dwButtons,dwButtonNumber,dwPOV,dwReserved1,dwReserved2; } JOYINFOEX;

typedef struct {
 DWORD cbSize;
 DWORD apiVersion;
 DWORD joyId;
 DWORD rawX,rawY,rawZ,rawR,rawU,rawV;
 DWORD rawButtons;
 DWORD rawButtonNumber;
 DWORD rawPOV;
 DWORD numButtons;
 DWORD numAxes;
 DWORD caps;
 WORD vendorId;
 WORD productId;
 char productName[MAXPNAMELEN];
} XIB_RAW_STATE;

typedef struct {
 DWORD dwOSVersionInfoSize; DWORD dwMajorVersion,dwMinorVersion,dwBuildNumber,dwPlatformId; char szCSDVersion[128];
} OSVERSIONINFOA;
typedef struct {
 DWORD dwOSVersionInfoSize; DWORD dwMajorVersion,dwMinorVersion,dwBuildNumber,dwPlatformId; WORD szCSDVersion[128];
} RTL_OSVERSIONINFOW_;

typedef struct {
 DWORD lStructSize; HWND hwndOwner; HINSTANCE hInstance; const char* lpstrFilter; char* lpstrCustomFilter; DWORD nMaxCustFilter; DWORD nFilterIndex;
 char* lpstrFile; DWORD nMaxFile; char* lpstrFileTitle; DWORD nMaxFileTitle; const char* lpstrInitialDir; const char* lpstrTitle; DWORD Flags;
 WORD nFileOffset; WORD nFileExtension; const char* lpstrDefExt; LPARAM lCustData; PVOID lpfnHook; const char* lpTemplateName;
} OPENFILENAMEA_;

typedef DWORD (__stdcall *PFN_XInputGetState)(DWORD,XINPUT_STATE*);
typedef DWORD (__stdcall *PFN_XInputSetState)(DWORD,XINPUT_VIBRATION*);
typedef DWORD (__stdcall *PFN_XInputBridgeGetRawState)(DWORD,XIB_RAW_STATE*);
typedef DWORD (__stdcall *PFN_XInputBridgeReloadConfig)(void);
typedef UINT (__stdcall *PFN_joyGetNumDevs)(void);
typedef MMRESULT (__stdcall *PFN_joyGetDevCapsA)(UINT_PTR,JOYCAPSA*,UINT);
typedef MMRESULT (__stdcall *PFN_joyGetPosEx)(UINT,JOYINFOEX*);
typedef LONG (__stdcall *PFN_RtlGetVersion)(RTL_OSVERSIONINFOW_*);
typedef BOOL (__stdcall *PFN_SetProcessDPIAware)(void);
typedef BOOL (__stdcall *PFN_GetOpenFileNameA_)(OPENFILENAMEA_*);
typedef DWORD (__stdcall *PFN_GetFileAttributesA_)(const char*);
typedef BOOL (__stdcall *PFN_CopyFileA_)(const char*,const char*,BOOL);
typedef DWORD (__stdcall *PFN_GetPrivateProfileStringA_)(const char*,const char*,const char*,char*,DWORD,const char*);
typedef HINSTANCE (__stdcall *PFN_ShellExecuteA_)(HWND,const char*,const char*,const char*,const char*,int);
typedef DWORD (__stdcall *PFN_GetLastError_)(void);
typedef BOOL (__stdcall *PFN_SetFileAttributesA_)(const char*,DWORD);
