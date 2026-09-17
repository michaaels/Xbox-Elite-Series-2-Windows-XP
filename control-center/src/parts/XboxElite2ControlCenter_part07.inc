static int hit_button(int x,int y){int i;for(i=0;i<N_UIBUTTONS;i++){UIBUTTON*b=&g_buttons[i];if(x>=b->x&&x<b->x+b->w&&y>=b->y&&y<b->y+b->h)return b->id;}return 0;}
static void on_click(int id){
 switch(id){case 1:start_test();break;case 2:stop_test();break;case 3:close_logs();g_testState=TEST_IDLE;g_baseName[0]=0;reset_stats();scopy(g_status,"Estadisticas reiniciadas.",sizeof(g_status));break;case 4:export_snapshot();break;case 5:rumble(32768,0,10000,"LEFT 50%");break;case 6:rumble(0,32768,10000,"RIGHT 50%");break;case 7:rumble(32768,32768,10000,"BOTH 50%");break;case 8:rumble_stop();break;}
 InvalidateRect(g_hwnd,NULL,FALSE);
}

static LRESULT __stdcall WndProc(HWND hwnd,UINT msg,WPARAM wp,LPARAM lp){
 if(msg==WM_ERASEBKGND)return 1;
 if(msg==WM_TIMER){poll_input();InvalidateRect(hwnd,NULL,FALSE);return 0;}
 if(msg==WM_LBUTTONDOWN){int mx=GET_X_LPARAM_(lp),my=GET_Y_LPARAM_(lp);if(g_gamesOpen){games_click(mx,my);InvalidateRect(hwnd,NULL,FALSE);return 0;}if(g_mapOpen){map_click(mx,my);InvalidateRect(hwnd,NULL,FALSE);return 0;}if(inrect(mx,my,700,18,90,24)){g_gamesOpen=1;InvalidateRect(hwnd,NULL,FALSE);return 0;}if(inrect(mx,my,354,352,82,30)){int i;for(i=0;i<4;i++)g_paddleDraft[i]=g_paddleMap[i];g_mapSelected=0;g_mapOpen=1;InvalidateRect(hwnd,NULL,FALSE);return 0;}on_click(hit_button(mx,my));return 0;}
 if(msg==WM_PAINT){PAINTSTRUCT ps;RECT rc;HDC dc=BeginPaint(hwnd,&ps),mem;HBITMAP bmp;HGDIOBJ old;GetClientRect(hwnd,&rc);mem=CreateCompatibleDC(dc);bmp=CreateCompatibleBitmap(dc,rc.right-rc.left,rc.bottom-rc.top);old=SelectObject(mem,bmp);render(mem,rc.right-rc.left,rc.bottom-rc.top);BitBlt(dc,0,0,rc.right,rc.bottom,mem,0,0,SRCCOPY);SelectObject(mem,old);DeleteObject(bmp);DeleteDC(mem);EndPaint(hwnd,&ps);return 0;}
 if(msg==WM_DESTROY){KillTimer(hwnd,TIMER_ID);rumble_stop();if(g_testState==TEST_RUNNING||g_testState==TEST_BASELINE)stop_test();close_logs();PostQuitMessage(0);return 0;}
 return DefWindowProcA(hwnd,msg,wp,lp);
}

static int app_main(void){
 WNDCLASSEXA wc;MSG m;HINSTANCE hi=GetModuleHandleA(NULL);set_exe_dir();detect_os();init_backends();reset_stats();
 g_font12=CreateFontA(-13,0,0,0,FW_NORMAL,0,0,0,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY,DEFAULT_PITCH|FF_DONTCARE,"Segoe UI");
 g_font14=CreateFontA(-15,0,0,0,FW_SEMIBOLD,0,0,0,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY,DEFAULT_PITCH|FF_DONTCARE,"Segoe UI");
 g_font16=CreateFontA(-17,0,0,0,FW_SEMIBOLD,0,0,0,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY,DEFAULT_PITCH|FF_DONTCARE,"Segoe UI");
 g_font20=CreateFontA(-22,0,0,0,FW_BOLD,0,0,0,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY,DEFAULT_PITCH|FF_DONTCARE,"Segoe UI");
 memset(&wc,0,sizeof(wc));wc.cbSize=sizeof(wc);wc.style=CS_HREDRAW|CS_VREDRAW;wc.lpfnWndProc=WndProc;wc.hInstance=hi;wc.hCursor=LoadCursorA(NULL,MAKEINTRESOURCEA_(IDC_ARROW));wc.hIcon=LoadIconA(NULL,MAKEINTRESOURCEA_(IDI_APPLICATION));wc.hIconSm=wc.hIcon;wc.lpszClassName="XboxElite2ControlCenterClass";
 if(!RegisterClassExA(&wc)){MessageBoxA(NULL,"No se pudo registrar la ventana.","Xbox Elite 2 Control Center",MB_OK|MB_ICONERROR);return 2;}
 g_hwnd=CreateWindowExA(0,wc.lpszClassName,"Xbox Elite Series 2 Control Center v1.5",WS_CAPTION|WS_SYSMENU|WS_MINIMIZEBOX|WS_CLIPCHILDREN|WS_CLIPSIBLINGS,CW_USEDEFAULT,CW_USEDEFAULT,960,550,NULL,NULL,hi,NULL);
 if(!g_hwnd){MessageBoxA(NULL,"No se pudo crear la ventana.","Xbox Elite 2 Control Center",MB_OK|MB_ICONERROR);return 3;}
 ShowWindow(g_hwnd,SW_SHOW);UpdateWindow(g_hwnd);SetTimer(g_hwnd,TIMER_ID,TIMER_MS,NULL);
 while(GetMessageA(&m,NULL,0,0)>0){TranslateMessage(&m);DispatchMessageA(&m);}return 0;
}
extern "C" void mainCRTStartup(void){int rc=app_main();ExitProcess((DWORD)rc);}
