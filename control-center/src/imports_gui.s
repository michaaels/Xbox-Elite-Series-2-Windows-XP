.intel_syntax noprefix
.section .idata$2,"dr"
.globl __impdesc_kernel32
__impdesc_kernel32: .rva int_k; .long 0; .long 0; .rva name_k; .rva iat_k
.globl __impdesc_user32
__impdesc_user32: .rva int_u; .long 0; .long 0; .rva name_u; .rva iat_u
.globl __impdesc_gdi32
__impdesc_gdi32: .rva int_g; .long 0; .long 0; .rva name_g; .rva iat_g
.globl __impdesc_msvcrt
__impdesc_msvcrt: .rva int_m; .long 0; .long 0; .rva name_m; .rva iat_m
 .long 0,0,0,0,0

.section .idata$4,"dr"
int_k:
 .rva hn_ExitProcess; .rva hn_GetModuleHandleA; .rva hn_LoadLibraryA; .rva hn_GetProcAddress; .rva hn_GetModuleFileNameA; .rva hn_SetCurrentDirectoryA; .rva hn_GetTickCount; .rva hn_GetLocalTime; .rva hn_GetPrivateProfileIntA; .rva hn_WritePrivateProfileStringA; .long 0
int_u:
 .rva hn_RegisterClassExA; .rva hn_CreateWindowExA; .rva hn_DefWindowProcA; .rva hn_ShowWindow; .rva hn_UpdateWindow; .rva hn_GetMessageA; .rva hn_TranslateMessage; .rva hn_DispatchMessageA; .rva hn_PostQuitMessage; .rva hn_SetTimer; .rva hn_KillTimer; .rva hn_InvalidateRect; .rva hn_BeginPaint; .rva hn_EndPaint; .rva hn_GetClientRect; .rva hn_LoadCursorA; .rva hn_LoadIconA; .rva hn_FillRect; .rva hn_DrawTextA; .rva hn_MessageBoxA; .long 0
int_g:
 .rva hn_CreateSolidBrush; .rva hn_DeleteObject; .rva hn_SelectObject; .rva hn_SetBkMode; .rva hn_SetTextColor; .rva hn_CreateFontA; .rva hn_RoundRect; .rva hn_Rectangle; .rva hn_Ellipse; .rva hn_CreatePen; .rva hn_MoveToEx; .rva hn_LineTo; .rva hn_CreateCompatibleDC; .rva hn_CreateCompatibleBitmap; .rva hn_DeleteDC; .rva hn_BitBlt; .long 0
int_m:
 .rva hn_sprintf; .rva hn_fopen; .rva hn_fclose; .rva hn_fprintf; .rva hn_fflush; .rva hn_memset; .long 0

.section .idata$5,"drw"
iat_k:
.globl __imp__ExitProcess@4
__imp__ExitProcess@4: .rva hn_ExitProcess
.globl __imp__GetModuleHandleA@4
__imp__GetModuleHandleA@4: .rva hn_GetModuleHandleA
.globl __imp__LoadLibraryA@4
__imp__LoadLibraryA@4: .rva hn_LoadLibraryA
.globl __imp__GetProcAddress@8
__imp__GetProcAddress@8: .rva hn_GetProcAddress
.globl __imp__GetModuleFileNameA@12
__imp__GetModuleFileNameA@12: .rva hn_GetModuleFileNameA
.globl __imp__SetCurrentDirectoryA@4
__imp__SetCurrentDirectoryA@4: .rva hn_SetCurrentDirectoryA
.globl __imp__GetTickCount@0
__imp__GetTickCount@0: .rva hn_GetTickCount
.globl __imp__GetLocalTime@4
__imp__GetLocalTime@4: .rva hn_GetLocalTime
.globl __imp__GetPrivateProfileIntA@16
__imp__GetPrivateProfileIntA@16: .rva hn_GetPrivateProfileIntA
.globl __imp__WritePrivateProfileStringA@16
__imp__WritePrivateProfileStringA@16: .rva hn_WritePrivateProfileStringA
 .long 0

iat_u:
.globl __imp__RegisterClassExA@4
__imp__RegisterClassExA@4: .rva hn_RegisterClassExA
.globl __imp__CreateWindowExA@48
__imp__CreateWindowExA@48: .rva hn_CreateWindowExA
.globl __imp__DefWindowProcA@16
__imp__DefWindowProcA@16: .rva hn_DefWindowProcA
.globl __imp__ShowWindow@8
__imp__ShowWindow@8: .rva hn_ShowWindow
.globl __imp__UpdateWindow@4
__imp__UpdateWindow@4: .rva hn_UpdateWindow
.globl __imp__GetMessageA@16
__imp__GetMessageA@16: .rva hn_GetMessageA
.globl __imp__TranslateMessage@4
__imp__TranslateMessage@4: .rva hn_TranslateMessage
.globl __imp__DispatchMessageA@4
__imp__DispatchMessageA@4: .rva hn_DispatchMessageA
.globl __imp__PostQuitMessage@4
__imp__PostQuitMessage@4: .rva hn_PostQuitMessage
.globl __imp__SetTimer@16
__imp__SetTimer@16: .rva hn_SetTimer
.globl __imp__KillTimer@8
__imp__KillTimer@8: .rva hn_KillTimer
.globl __imp__InvalidateRect@12
__imp__InvalidateRect@12: .rva hn_InvalidateRect
.globl __imp__BeginPaint@8
__imp__BeginPaint@8: .rva hn_BeginPaint
.globl __imp__EndPaint@8
__imp__EndPaint@8: .rva hn_EndPaint
.globl __imp__GetClientRect@8
__imp__GetClientRect@8: .rva hn_GetClientRect
.globl __imp__LoadCursorA@8
__imp__LoadCursorA@8: .rva hn_LoadCursorA
.globl __imp__LoadIconA@8
__imp__LoadIconA@8: .rva hn_LoadIconA
.globl __imp__FillRect@12
__imp__FillRect@12: .rva hn_FillRect
.globl __imp__DrawTextA@20
__imp__DrawTextA@20: .rva hn_DrawTextA
.globl __imp__MessageBoxA@16
__imp__MessageBoxA@16: .rva hn_MessageBoxA
 .long 0

iat_g:
.globl __imp__CreateSolidBrush@4
__imp__CreateSolidBrush@4: .rva hn_CreateSolidBrush
.globl __imp__DeleteObject@4
__imp__DeleteObject@4: .rva hn_DeleteObject
.globl __imp__SelectObject@8
__imp__SelectObject@8: .rva hn_SelectObject
.globl __imp__SetBkMode@8
__imp__SetBkMode@8: .rva hn_SetBkMode
.globl __imp__SetTextColor@8
__imp__SetTextColor@8: .rva hn_SetTextColor
.globl __imp__CreateFontA@56
__imp__CreateFontA@56: .rva hn_CreateFontA
.globl __imp__RoundRect@28
__imp__RoundRect@28: .rva hn_RoundRect
.globl __imp__Rectangle@20
__imp__Rectangle@20: .rva hn_Rectangle
.globl __imp__Ellipse@20
__imp__Ellipse@20: .rva hn_Ellipse
.globl __imp__CreatePen@12
__imp__CreatePen@12: .rva hn_CreatePen
.globl __imp__MoveToEx@16
__imp__MoveToEx@16: .rva hn_MoveToEx
.globl __imp__LineTo@12
__imp__LineTo@12: .rva hn_LineTo
.globl __imp__CreateCompatibleDC@4
__imp__CreateCompatibleDC@4: .rva hn_CreateCompatibleDC
.globl __imp__CreateCompatibleBitmap@12
__imp__CreateCompatibleBitmap@12: .rva hn_CreateCompatibleBitmap
.globl __imp__DeleteDC@4
__imp__DeleteDC@4: .rva hn_DeleteDC
.globl __imp__BitBlt@36
__imp__BitBlt@36: .rva hn_BitBlt
 .long 0

iat_m:
.globl __imp__sprintf
__imp__sprintf: .rva hn_sprintf
.globl __imp__fopen
__imp__fopen: .rva hn_fopen
.globl __imp__fclose
__imp__fclose: .rva hn_fclose
.globl __imp__fprintf
__imp__fprintf: .rva hn_fprintf
.globl __imp__fflush
__imp__fflush: .rva hn_fflush
.globl __imp__memset
__imp__memset: .rva hn_memset
 .long 0

.section .idata$6,"dr"
hn_ExitProcess:.short 0;.asciz "ExitProcess";.balign 2
hn_GetModuleHandleA:.short 0;.asciz "GetModuleHandleA";.balign 2
hn_LoadLibraryA:.short 0;.asciz "LoadLibraryA";.balign 2
hn_GetProcAddress:.short 0;.asciz "GetProcAddress";.balign 2
hn_GetModuleFileNameA:.short 0;.asciz "GetModuleFileNameA";.balign 2
hn_SetCurrentDirectoryA:.short 0;.asciz "SetCurrentDirectoryA";.balign 2
hn_GetTickCount:.short 0;.asciz "GetTickCount";.balign 2
hn_GetLocalTime:.short 0;.asciz "GetLocalTime";.balign 2
hn_GetPrivateProfileIntA:.short 0;.asciz "GetPrivateProfileIntA";.balign 2
hn_WritePrivateProfileStringA:.short 0;.asciz "WritePrivateProfileStringA";.balign 2

hn_RegisterClassExA:.short 0;.asciz "RegisterClassExA";.balign 2
hn_CreateWindowExA:.short 0;.asciz "CreateWindowExA";.balign 2
hn_DefWindowProcA:.short 0;.asciz "DefWindowProcA";.balign 2
hn_ShowWindow:.short 0;.asciz "ShowWindow";.balign 2
hn_UpdateWindow:.short 0;.asciz "UpdateWindow";.balign 2
hn_GetMessageA:.short 0;.asciz "GetMessageA";.balign 2
hn_TranslateMessage:.short 0;.asciz "TranslateMessage";.balign 2
hn_DispatchMessageA:.short 0;.asciz "DispatchMessageA";.balign 2
hn_PostQuitMessage:.short 0;.asciz "PostQuitMessage";.balign 2
hn_SetTimer:.short 0;.asciz "SetTimer";.balign 2
hn_KillTimer:.short 0;.asciz "KillTimer";.balign 2
hn_InvalidateRect:.short 0;.asciz "InvalidateRect";.balign 2
hn_BeginPaint:.short 0;.asciz "BeginPaint";.balign 2
hn_EndPaint:.short 0;.asciz "EndPaint";.balign 2
hn_GetClientRect:.short 0;.asciz "GetClientRect";.balign 2
hn_LoadCursorA:.short 0;.asciz "LoadCursorA";.balign 2
hn_LoadIconA:.short 0;.asciz "LoadIconA";.balign 2
hn_FillRect:.short 0;.asciz "FillRect";.balign 2
hn_DrawTextA:.short 0;.asciz "DrawTextA";.balign 2
hn_MessageBoxA:.short 0;.asciz "MessageBoxA";.balign 2

hn_CreateSolidBrush:.short 0;.asciz "CreateSolidBrush";.balign 2
hn_DeleteObject:.short 0;.asciz "DeleteObject";.balign 2
hn_SelectObject:.short 0;.asciz "SelectObject";.balign 2
hn_SetBkMode:.short 0;.asciz "SetBkMode";.balign 2
hn_SetTextColor:.short 0;.asciz "SetTextColor";.balign 2
hn_CreateFontA:.short 0;.asciz "CreateFontA";.balign 2
hn_RoundRect:.short 0;.asciz "RoundRect";.balign 2
hn_Rectangle:.short 0;.asciz "Rectangle";.balign 2
hn_Ellipse:.short 0;.asciz "Ellipse";.balign 2
hn_CreatePen:.short 0;.asciz "CreatePen";.balign 2
hn_MoveToEx:.short 0;.asciz "MoveToEx";.balign 2
hn_LineTo:.short 0;.asciz "LineTo";.balign 2
hn_CreateCompatibleDC:.short 0;.asciz "CreateCompatibleDC";.balign 2
hn_CreateCompatibleBitmap:.short 0;.asciz "CreateCompatibleBitmap";.balign 2
hn_DeleteDC:.short 0;.asciz "DeleteDC";.balign 2
hn_BitBlt:.short 0;.asciz "BitBlt";.balign 2

hn_sprintf:.short 0;.asciz "sprintf";.balign 2
hn_fopen:.short 0;.asciz "fopen";.balign 2
hn_fclose:.short 0;.asciz "fclose";.balign 2
hn_fprintf:.short 0;.asciz "fprintf";.balign 2
hn_fflush:.short 0;.asciz "fflush";.balign 2
hn_memset:.short 0;.asciz "memset";.balign 2

name_k:.asciz "KERNEL32.dll"
name_u:.asciz "USER32.dll"
name_g:.asciz "GDI32.dll"
name_m:.asciz "MSVCRT.dll"
