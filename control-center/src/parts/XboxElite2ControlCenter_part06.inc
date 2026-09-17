/* drawing helpers */
static void fill(HDC dc,int x,int y,int w,int h,COLORREF c){RECT r;HBRUSH b=CreateSolidBrush(c);r.left=x;r.top=y;r.right=x+w;r.bottom=y+h;FillRect(dc,&r,b);DeleteObject(b);}
static void rr(HDC dc,int x,int y,int w,int h,COLORREF fillc,COLORREF border,int radius){HBRUSH b=CreateSolidBrush(fillc);HPEN p=CreatePen(PS_SOLID,1,border);HGDIOBJ ob=SelectObject(dc,b),op=SelectObject(dc,p);RoundRect(dc,x,y,x+w,y+h,radius,radius);SelectObject(dc,ob);SelectObject(dc,op);DeleteObject(b);DeleteObject(p);}
static void txt(HDC dc,int x,int y,int w,int h,const char*s,COLORREF c,HFONT f,UINT flags){RECT r;r.left=x;r.top=y;r.right=x+w;r.bottom=y+h;SetBkMode(dc,TRANSPARENT);SetTextColor(dc,c);SelectObject(dc,f);DrawTextA(dc,s,-1,&r,flags|DT_END_ELLIPSIS);}
static void pill(HDC dc,int x,int y,int w,const char*s,COLORREF c){rr(dc,x,y,w,24,RGB_(26,43,40),c,12);txt(dc,x,y,w,24,s,c,g_font12,DT_CENTER|DT_VCENTER|DT_SINGLELINE);}
static void circle_button(HDC dc,int cx,int cy,int r,const char*label,int on,COLORREF accent){HBRUSH b=CreateSolidBrush(on?accent:C_PANEL2);HPEN p=CreatePen(PS_SOLID,1,on?accent:C_LINE);HGDIOBJ ob=SelectObject(dc,b),op=SelectObject(dc,p);Ellipse(dc,cx-r,cy-r,cx+r,cy+r);SelectObject(dc,ob);SelectObject(dc,op);DeleteObject(b);DeleteObject(p);txt(dc,cx-r,cy-r,r*2,r*2,label,on?RGB_(15,20,25):C_TEXT,g_font14,DT_CENTER|DT_VCENTER|DT_SINGLELINE);}
static void stick(HDC dc,int cx,int cy,int radius,SHORT x,SHORT y,const char*name){char s[96];HBRUSH b=CreateSolidBrush(RGB_(22,27,34));HPEN p=CreatePen(PS_SOLID,1,C_LINE);HGDIOBJ ob=SelectObject(dc,b),op=SelectObject(dc,p);Ellipse(dc,cx-radius,cy-radius,cx+radius,cy+radius);MoveToEx(dc,cx-radius+8,cy,NULL);LineTo(dc,cx+radius-8,cy);MoveToEx(dc,cx,cy-radius+8,NULL);LineTo(dc,cx,cy+radius-8);SelectObject(dc,ob);SelectObject(dc,op);DeleteObject(b);DeleteObject(p);
 {int dx=(int)(((LONG)x*(radius-9))/32768L),dy=(int)((-(LONG)y*(radius-9))/32768L);circle_button(dc,cx+dx,cy+dy,6,"",1,C_BLUE);} sprintf(s,"%s  X %6d  Y %6d",name,x,y);txt(dc,cx-radius-28,cy+radius+8,radius*2+56,20,s,C_MUTED,g_font12,DT_CENTER|DT_VCENTER|DT_SINGLELINE);}
static void bar(HDC dc,int x,int y,int w,int h,int val,const char*label){char s[48];int fw=(w-4)*clampi(val,0,255)/255;rr(dc,x,y,w,h,RGB_(22,27,34),C_LINE,8);if(fw>0)rr(dc,x+2,y+2,fw,h-4,C_BLUE,C_BLUE,6);sprintf(s,"%s  %3d",label,val);txt(dc,x,y,w,h,s,C_TEXT,g_font12,DT_CENTER|DT_VCENTER|DT_SINGLELINE);}
static int pressed(WORD mask){return g_xret==ERROR_SUCCESS && (g_xstate.Gamepad.wButtons&mask)!=0;}
static int raw_pressed(int idx){return g_jret==JOYERR_NOERROR && idx>=1 && idx<=32 && (g_raw.dwButtons&(1UL<<(idx-1)))!=0;}
static void small_key(HDC dc,int x,int y,int w,int h,const char*label,int on){rr(dc,x,y,w,h,on?C_BLUE:C_PANEL2,on?C_BLUE:C_LINE,7);txt(dc,x,y,w,h,label,on?RGB_(12,18,24):C_TEXT,g_font12,DT_CENTER|DT_VCENTER|DT_SINGLELINE);}
static void diag_row(HDC dc,int x,int y,const char*name,const char*value,int state){COLORREF c=state>0?C_GREEN:(state<0?C_RED:C_YELLOW);circle_button(dc,x+8,y+9,5,"",1,c);txt(dc,x+22,y,150,18,name,C_TEXT,g_font12,DT_LEFT|DT_VCENTER|DT_SINGLELINE);txt(dc,x+170,y,120,18,value,c,g_font12,DT_RIGHT|DT_VCENTER|DT_SINGLELINE);}
static void draw_uibutton(HDC dc,const UIBUTTON*b){int disabled=(b->id==2 && (g_testState==TEST_IDLE||g_testState==TEST_COMPLETE));int active=(b->id==5&&g_rumbleLeft&& !g_rumbleRight)||(b->id==6&&g_rumbleRight&&!g_rumbleLeft)||(b->id==7&&g_rumbleLeft&&g_rumbleRight);COLORREF fc=(b->id==1)?C_BLUE:C_PANEL2;COLORREF bc=(b->id==1)?C_BLUE:C_LINE;COLORREF tc=disabled?C_OFF:C_TEXT;if(active){fc=RGB_(34,92,79);bc=C_GREEN;}if(b->id==8&&(g_rumbleLeft||g_rumbleRight)){fc=RGB_(92,38,42);bc=C_RED;}if(disabled)fc=RGB_(30,35,42);rr(dc,b->x,b->y,b->w,b->h,fc,bc,8);txt(dc,b->x,b->y,b->w,b->h,b->label,tc,g_font12,DT_CENTER|DT_VCENTER|DT_SINGLELINE);}


static void render_mapping(HDC dc,int W,int H){
 char s[128];int i,t,c,r;fill(dc,0,0,W,H,C_BG);
 txt(dc,30,20,600,32,"Configurar paddles - Xbox Elite Series 2",C_TEXT,g_font20,DT_LEFT|DT_VCENTER|DT_SINGLELINE);
 txt(dc,30,54,800,20,"Selecciona P1-P4 y luego el boton XInput que quieres duplicar.",C_MUTED,g_font12,DT_LEFT|DT_VCENTER|DT_SINGLELINE);
 rr(dc,80,90,800,370,C_PANEL,C_LINE,14);
 txt(dc,110,108,520,22,"1. Selecciona el paddle fisico",C_TEXT,g_font14,DT_LEFT|DT_VCENTER|DT_SINGLELINE);
 for(i=0;i<4;i++){int x=120+i*180;char lab[40];sprintf(lab,"P%d  ->  %s",i+1,map_name(g_paddleDraft[i]));rr(dc,x,140,150,42,i==g_mapSelected?RGB_(34,77,108):C_PANEL2,i==g_mapSelected?C_BLUE:C_LINE,9);txt(dc,x,140,150,42,lab,C_TEXT,g_font14,DT_CENTER|DT_VCENTER|DT_SINGLELINE);if(raw_pressed(11+i))circle_button(dc,x+136,151,5,"",1,C_GREEN);}
 txt(dc,110,198,520,22,"2. Elige el destino XInput",C_TEXT,g_font14,DT_LEFT|DT_VCENTER|DT_SINGLELINE);
 for(t=0;t<12;t++){c=t%4;r=t/4;{int x=120+c*180,y=230+r*50;int sel=(g_paddleDraft[g_mapSelected]==t);rr(dc,x,y,150,36,sel?RGB_(34,77,108):C_PANEL2,sel?C_BLUE:C_LINE,8);txt(dc,x,y,150,36,map_name(t),sel?C_TEXT:C_MUTED,g_font14,DT_CENTER|DT_VCENTER|DT_SINGLELINE);}}
 sprintf(s,"P%d se enviara como %s. El boton fisico B%d sigue visible en RAW.",g_mapSelected+1,map_name(g_paddleDraft[g_mapSelected]),11+g_mapSelected);txt(dc,120,377,650,18,s,C_MUTED,g_font12,DT_LEFT|DT_VCENTER|DT_SINGLELINE);
 txt(dc,120,396,650,16,"NONE desactiva el remapeo. GUIDE puede requerir XInputGetStateEx.",C_YELLOW,g_font12,DT_LEFT|DT_VCENTER|DT_SINGLELINE);
 rr(dc,120,414,190,34,C_PANEL2,C_LINE,8);txt(dc,120,414,190,34,"RESTAURAR A/B/X/Y",C_TEXT,g_font12,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
 rr(dc,530,414,120,34,C_PANEL2,C_LINE,8);txt(dc,530,414,120,34,"CANCELAR",C_TEXT,g_font12,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
 rr(dc,665,414,175,34,C_BLUE,C_BLUE,8);txt(dc,665,414,175,34,"GUARDAR Y APLICAR",RGB_(12,18,24),g_font12,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
}
static void map_click(int x,int y){
 int i,t,c,r;if(!g_mapOpen)return;
 for(i=0;i<4;i++)if(inrect(x,y,120+i*180,140,150,42)){g_mapSelected=i;return;}
 for(t=0;t<12;t++){c=t%4;r=t/4;if(inrect(x,y,120+c*180,230+r*50,150,36)){g_paddleDraft[g_mapSelected]=t;return;}}
 if(inrect(x,y,120,414,190,34)){g_paddleDraft[0]=1;g_paddleDraft[1]=2;g_paddleDraft[2]=3;g_paddleDraft[3]=4;return;}
 if(inrect(x,y,530,414,120,34)){for(i=0;i<4;i++)g_paddleDraft[i]=g_paddleMap[i];g_mapOpen=0;scopy(g_status,"Mapeo cancelado.",sizeof(g_status));return;}
 if(inrect(x,y,665,414,175,34)){save_paddle_map();g_mapOpen=0;return;}
}

static void render_games(HDC dc,int W,int H){
 char st[260],pathshow[320],s[220];fill(dc,0,0,W,H,C_BG);
 txt(dc,24,16,520,28,"JUEGO / PERFIL XINPUT",C_TEXT,g_font20,DT_LEFT|DT_VCENTER|DT_SINGLELINE);
 txt(dc,24,46,760,18,"Selecciona cualquier .EXE. No hay juegos predefinidos ni rutas quemadas.",C_MUTED,g_font12,DT_LEFT|DT_VCENTER|DT_SINGLELINE);
 rr(dc,820,18,110,28,C_PANEL2,C_LINE,7);txt(dc,820,18,110,28,"VOLVER",C_TEXT,g_font12,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
 rr(dc,22,86,916,252,C_PANEL,C_LINE,14);
 txt(dc,42,104,560,26,g_gameName,C_TEXT,g_font16,DT_LEFT|DT_VCENTER|DT_SINGLELINE);
 game_status_text(st,sizeof(st));txt(dc,42,136,850,20,st,C_MUTED,g_font12,DT_LEFT|DT_VCENTER|DT_SINGLELINE);
 if(g_gameExePath[0])scopy(pathshow,g_gameExePath,sizeof(pathshow));else scopy(pathshow,"Selecciona el ejecutable del juego...",sizeof(pathshow));
 txt(dc,42,166,850,20,pathshow,C_TEXT,g_font12,DT_LEFT|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS);
 rr(dc,42,206,150,36,C_PANEL2,C_BLUE,8);txt(dc,42,206,150,36,"SELECCIONAR EXE",C_TEXT,g_font12,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
 rr(dc,204,206,160,36,C_PANEL2,C_BLUE,8);txt(dc,204,206,160,36,"INSTALAR BRIDGE",C_TEXT,g_font12,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
 rr(dc,376,206,150,36,C_PANEL2,C_LINE,8);txt(dc,376,206,150,36,"APLICAR MAPEO",C_TEXT,g_font12,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
 rr(dc,538,206,150,36,C_PANEL2,C_LINE,8);txt(dc,538,206,150,36,"CARGAR MAPEO",C_TEXT,g_font12,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
 rr(dc,700,206,138,36,C_GREEN,C_GREEN,8);txt(dc,700,206,138,36,"EJECUTAR",RGB_(12,18,24),g_font12,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
 sprintf(s,"P1>%s   P2>%s   P3>%s   P4>%s",map_name(g_paddleMap[0]),map_name(g_paddleMap[1]),map_name(g_paddleMap[2]),map_name(g_paddleMap[3]));txt(dc,42,260,600,18,s,C_MUTED,g_font12,DT_LEFT|DT_VCENTER|DT_SINGLELINE);
 txt(dc,42,288,850,18,"INSTALAR BRIDGE copia xinput1_3.dll + xinput9_1_0.dll + perfil INI al directorio del EXE.",C_TEXT,g_font12,DT_LEFT|DT_VCENTER|DT_SINGLELINE);
 txt(dc,42,312,850,18,"Si ya existe una DLL, se conserva un .xboxelite2xp.bak antes de reemplazarla.",C_MUTED,g_font12,DT_LEFT|DT_VCENTER|DT_SINGLELINE);
 rr(dc,22,360,916,120,C_PANEL,C_LINE,12);
 txt(dc,42,374,850,20,"Compatibilidad",C_TEXT,g_font14,DT_LEFT|DT_VCENTER|DT_SINGLELINE);
 txt(dc,42,402,850,18,"- Juegos XInput 1.3 / 9.1.0: usa el Bridge directamente.",C_MUTED,g_font12,DT_LEFT|DT_VCENTER|DT_SINGLELINE);
 txt(dc,42,426,850,18,"- Juegos DirectInput: el Bridge por si solo no cambia el API; pueden necesitar GInput/wrapper/mod.",C_MUTED,g_font12,DT_LEFT|DT_VCENTER|DT_SINGLELINE);
 txt(dc,42,450,850,18,"- Error 5 = permisos; Error 32 = DLL en uso. Cierra el juego antes de instalar.",C_YELLOW,g_font12,DT_LEFT|DT_VCENTER|DT_SINGLELINE);
}
static void games_click(int x,int y){if(inrect(x,y,820,18,110,28)){g_gamesOpen=0;return;}if(inrect(x,y,42,206,150,36)){browse_game();return;}if(inrect(x,y,204,206,160,36)){install_bridge_game();return;}if(inrect(x,y,376,206,150,36)){apply_map_to_game();return;}if(inrect(x,y,538,206,150,36)){load_map_from_game();return;}if(inrect(x,y,700,206,138,36)){launch_game();return;}}

static void render(HDC dc,int W,int H){
 char s[160]; int i,normal,paddles,pov,lcover,rcover; WORD xb=(g_xret==ERROR_SUCCESS)?g_xstate.Gamepad.wButtons:0;
 if(g_gamesOpen){render_games(dc,W,H);return;}
 if(g_mapOpen){render_mapping(dc,W,H);return;}
 fill(dc,0,0,W,H,C_BG);
 /* header */
 txt(dc,22,14,510,28,"Xbox Elite Series 2 Control Center",C_TEXT,g_font20,DT_LEFT|DT_VCENTER|DT_SINGLELINE);
 txt(dc,24,43,560,18,g_os,C_MUTED,g_font12,DT_LEFT|DT_VCENTER|DT_SINGLELINE);
 rr(dc,W-260,18,90,24,C_PANEL2,C_LINE,7);txt(dc,W-260,18,90,24,"JUEGOS",C_TEXT,g_font12,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
 if(g_xret==ERROR_SUCCESS)pill(dc,W-150,18,120,"CONECTADO",C_GREEN);else pill(dc,W-150,18,120,"SIN XINPUT",C_RED);
 /* controller card */
 rr(dc,16,76,570,312,C_PANEL,C_LINE,14);
 txt(dc,32,90,250,20,"CONTROLADOR EN TIEMPO REAL",C_MUTED,g_font12,DT_LEFT|DT_VCENTER|DT_SINGLELINE);
 sprintf(s,"%s",g_device);txt(dc,305,90,260,20,s,C_TEXT,g_font12,DT_RIGHT|DT_VCENTER|DT_SINGLELINE);
 bar(dc,36,120,190,26,g_xstate.Gamepad.bLeftTrigger,"LT");bar(dc,376,120,190,26,g_xstate.Gamepad.bRightTrigger,"RT");
 small_key(dc,70,154,54,24,"LB",pressed(XINPUT_GAMEPAD_LEFT_SHOULDER));small_key(dc,462,154,54,24,"RB",pressed(XINPUT_GAMEPAD_RIGHT_SHOULDER));
 stick(dc,142,247,48,g_xstate.Gamepad.sThumbLX,g_xstate.Gamepad.sThumbLY,"LEFT");stick(dc,444,247,48,g_xstate.Gamepad.sThumbRX,g_xstate.Gamepad.sThumbRY,"RIGHT");
 /* D-Pad */
 small_key(dc,220,210,34,28,"U",pressed(XINPUT_GAMEPAD_DPAD_UP));small_key(dc,220,268,34,28,"D",pressed(XINPUT_GAMEPAD_DPAD_DOWN));small_key(dc,184,239,34,28,"L",pressed(XINPUT_GAMEPAD_DPAD_LEFT));small_key(dc,256,239,34,28,"R",pressed(XINPUT_GAMEPAD_DPAD_RIGHT));
 /* ABXY */
 circle_button(dc,349,211,15,"Y",pressed(XINPUT_GAMEPAD_Y),C_YELLOW);circle_button(dc,349,273,15,"A",pressed(XINPUT_GAMEPAD_A),C_GREEN);circle_button(dc,318,242,15,"X",pressed(XINPUT_GAMEPAD_X),C_BLUE);circle_button(dc,380,242,15,"B",pressed(XINPUT_GAMEPAD_B),C_RED);
 small_key(dc,222,322,58,24,"BACK",pressed(XINPUT_GAMEPAD_BACK));small_key(dc,290,322,58,24,"START",pressed(XINPUT_GAMEPAD_START));small_key(dc,70,322,54,24,"L3",pressed(XINPUT_GAMEPAD_LEFT_THUMB));small_key(dc,462,322,54,24,"R3",pressed(XINPUT_GAMEPAD_RIGHT_THUMB));
 txt(dc,32,358,72,18,"PADDLES",C_MUTED,g_font12,DT_LEFT|DT_VCENTER|DT_SINGLELINE);
 {char m[20];sprintf(m,"P1>%s",map_name(g_paddleMap[0]));small_key(dc,102,354,58,26,m,raw_pressed(11));sprintf(m,"P2>%s",map_name(g_paddleMap[1]));small_key(dc,164,354,58,26,m,raw_pressed(12));sprintf(m,"P3>%s",map_name(g_paddleMap[2]));small_key(dc,226,354,58,26,m,raw_pressed(13));sprintf(m,"P4>%s",map_name(g_paddleMap[3]));small_key(dc,288,354,58,26,m,raw_pressed(14));}
 rr(dc,354,352,82,30,C_PANEL2,C_BLUE,7);txt(dc,354,352,82,30,"MAPEAR",C_TEXT,g_font12,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
 sprintf(s,"RAW %s %08lX",g_rawSource==1?"B":(g_rawSource==2?"W":"-"),g_raw.dwButtons);txt(dc,442,358,118,18,s,C_MUTED,g_font12,DT_RIGHT|DT_VCENTER|DT_SINGLELINE);
 /* diagnostics card */
 rr(dc,600,76,344,312,C_PANEL,C_LINE,14);txt(dc,618,90,220,20,"DIAGNOSTICO DE SESION",C_MUTED,g_font12,DT_LEFT|DT_VCENTER|DT_SINGLELINE);
 lcover=(axis_coverage(&g_ax[0])+axis_coverage(&g_ax[1]))/2;rcover=(axis_coverage(&g_ax[2])+axis_coverage(&g_ax[3]))/2;normal=count_normal_best();paddles=count_paddles_best();pov=count_pov_best();
 sprintf(s,"%s",g_xret==0?"OK":"NO");diag_row(dc,620,124,"XInput",s,g_xret==0?1:-1);
 sprintf(s,"%d%%",lcover);diag_row(dc,620,151,"Stick izquierdo",s,lcover>=90?1:(lcover?0:-1));
 sprintf(s,"%d%%",rcover);diag_row(dc,620,178,"Stick derecho",s,rcover>=90?1:(rcover?0:-1));
 sprintf(s,"LT %u / RT %u",g_ltMax,g_rtMax);diag_row(dc,620,205,"Gatillos",s,(g_ltMax>220&&g_rtMax>220)?1:0);
 sprintf(s,"%d / 10",normal);diag_row(dc,620,232,"Botones 1-10",s,normal==10?1:0);
 if(paddles>=0){sprintf(s,"%d / 4",paddles);diag_row(dc,620,259,"Paddles 11-14",s,paddles==4?1:0);}else diag_row(dc,620,259,"Paddles 11-14","N/A - sin RAW",0);
 sprintf(s,"%d / 8",pov);diag_row(dc,620,286,"D-Pad / POV",s,pov==8?1:0);
 if(g_rumbleLeft&&g_rumbleRight)sprintf(s,"%lu OK / BOTH",g_rumbleCommands);else if(g_rumbleLeft)sprintf(s,"%lu OK / L",g_rumbleCommands);else if(g_rumbleRight)sprintf(s,"%lu OK / R",g_rumbleCommands);else sprintf(s,"%lu OK / OFF",g_rumbleCommands);diag_row(dc,620,313,"Comandos rumble",s,g_rumbleCommands?1:0);
 sprintf(s,"XErr %lu  RawErr %lu  Samples %lu",g_xErrors,g_rawErrors,g_samples);txt(dc,620,347,304,18,s,C_MUTED,g_font12,DT_LEFT|DT_VCENTER|DT_SINGLELINE);
 sprintf(s,"RAW: %s | %s",g_rawSource==1?"Bridge":(g_rawSource==2?"WinMM":"XInput fallback"),g_backend);txt(dc,620,367,304,18,s,C_MUTED,g_font12,DT_LEFT|DT_VCENTER|DT_SINGLELINE);
 /* command strip */
 rr(dc,16,400,928,108,C_PANEL,C_LINE,14);for(i=0;i<N_UIBUTTONS;i++)draw_uibutton(dc,&g_buttons[i]);
 txt(dc,28,458,105,18,"ESTADO",C_MUTED,g_font12,DT_LEFT|DT_VCENTER|DT_SINGLELINE);txt(dc,92,458,800,18,g_status,C_TEXT,g_font12,DT_LEFT|DT_VCENTER|DT_SINGLELINE);
 if(g_testState==TEST_BASELINE){DWORD elapsed=GetTickCount()-g_testStart;int pct=clampi((int)(elapsed*100UL/3000UL),0,100);sprintf(s,"Calibrando %d%%",pct);}else if(g_testState==TEST_RUNNING)sprintf(s,"Grabando RAW + eventos");else if(g_testState==TEST_COMPLETE)sprintf(s,"Prueba completa");else sprintf(s,"Sin grabacion activa");
 txt(dc,28,484,300,18,s,g_testState==TEST_RUNNING?C_GREEN:C_MUTED,g_font12,DT_LEFT|DT_VCENTER|DT_SINGLELINE);
 sprintf(s,"Packet %lu | XButtons 0x%04X | JoyID %d | RAW %s",g_xstate.dwPacketNumber,xb,g_joyId,g_rawSource==1?"Bridge":(g_rawSource==2?"WinMM":"N/A"));txt(dc,568,484,324,18,s,C_MUTED,g_font12,DT_RIGHT|DT_VCENTER|DT_SINGLELINE);
}
