static int pick_joystick(void){
 UINT n,i; JOYCAPSA c; JOYINFOEX j; if(!g_jnum||!g_jcaps||!g_jpos)return -1; n=g_jnum(); if(n>16)n=16;
 for(i=0;i<n;i++){
  memset(&c,0,sizeof(c)); if(g_jcaps(i,&c,sizeof(c))!=JOYERR_NOERROR)continue;
  if(c.wNumButtons<10 || c.wNumAxes<5)continue;
  memset(&j,0,sizeof(j));j.dwSize=sizeof(j);j.dwFlags=JOY_RETURNALL;if(g_jpos(i,&j)!=JOYERR_NOERROR)continue;
  g_caps=c; scopy(g_device,c.szPname,sizeof(g_device)); return (int)i;
 }
 return -1;
}
static void init_backends(void){
 g_xmod=LoadLibraryA(".\\xinput1_3.dll");
 if(g_xmod){scopy(g_backend,"XInputBridgeXP local / xinput1_3.dll",sizeof(g_backend));}
 if(!g_xmod){g_xmod=LoadLibraryA("xinput1_4.dll");if(g_xmod)scopy(g_backend,"System XInput 1.4",sizeof(g_backend));}
 if(!g_xmod){g_xmod=LoadLibraryA("xinput9_1_0.dll");if(g_xmod)scopy(g_backend,"System XInput 9.1.0",sizeof(g_backend));}
 if(g_xmod){g_xget=(PFN_XInputGetState)GetProcAddress(g_xmod,"XInputGetState");g_xset=(PFN_XInputSetState)GetProcAddress(g_xmod,"XInputSetState");g_xraw=(PFN_XInputBridgeGetRawState)GetProcAddress(g_xmod,"XInputBridgeGetRawState");g_xreload=(PFN_XInputBridgeReloadConfig)GetProcAddress(g_xmod,"XInputBridgeReloadConfig");}
 g_winmm=LoadLibraryA("winmm.dll");
 if(g_winmm){g_jnum=(PFN_joyGetNumDevs)GetProcAddress(g_winmm,"joyGetNumDevs");g_jcaps=(PFN_joyGetDevCapsA)GetProcAddress(g_winmm,"joyGetDevCapsA");g_jpos=(PFN_joyGetPosEx)GetProcAddress(g_winmm,"joyGetPosEx");}
 g_joyId=pick_joystick();
 load_paddle_map();
 load_game_profile();
}

static void reset_stats(void){
 int i; memset(g_ax,0,sizeof(g_ax)); for(i=0;i<4;i++){g_ax[i].minv=32767;g_ax[i].maxv=-32768;g_ax[i].baseMin=32767;g_ax[i].baseMax=-32768;}
 g_ltMax=g_rtMax=0;g_rawButtonSeen=g_xButtonSeen=0;memset(g_pressCount,0,sizeof(g_pressCount));g_prevRawButtons=0;memset(g_povSeen,0,sizeof(g_povSeen));memset(g_xPovSeen,0,sizeof(g_xPovSeen));g_xErrors=g_rawErrors=g_samples=0;g_rawEver=0;
}
static int axis_coverage(const AXSTAT*a){LONG range=a->maxv-a->minv;if(range<0)return 0;return clampi((int)((range*100L)/65535L),0,100);}
static int pov_bucket(DWORD p){if(p==JOY_POVCENTERED)return -1;return (int)(((p+2250UL)/4500UL)&7UL);}
static int x_pov_bucket(WORD w){int u=(w&XINPUT_GAMEPAD_DPAD_UP)!=0,d=(w&XINPUT_GAMEPAD_DPAD_DOWN)!=0,l=(w&XINPUT_GAMEPAD_DPAD_LEFT)!=0,r=(w&XINPUT_GAMEPAD_DPAD_RIGHT)!=0;if(u&&!d){if(r&&!l)return 1;if(l&&!r)return 7;return 0;}if(d&&!u){if(r&&!l)return 3;if(l&&!r)return 5;return 4;}if(r&&!l)return 2;if(l&&!r)return 6;return -1;}
static int count_x_normal(void){static WORD m[10]={XINPUT_GAMEPAD_A,XINPUT_GAMEPAD_B,XINPUT_GAMEPAD_X,XINPUT_GAMEPAD_Y,XINPUT_GAMEPAD_LEFT_SHOULDER,XINPUT_GAMEPAD_RIGHT_SHOULDER,XINPUT_GAMEPAD_BACK,XINPUT_GAMEPAD_START,XINPUT_GAMEPAD_LEFT_THUMB,XINPUT_GAMEPAD_RIGHT_THUMB};int i,n=0;for(i=0;i<10;i++)if(g_xButtonSeen&m[i])n++;return n;}
static void update_stats(int baseline){
 LONG vals[4]; int i,b,p; DWORD changed,down;
 if(g_xret==ERROR_SUCCESS){
  vals[0]=g_xstate.Gamepad.sThumbLX;vals[1]=g_xstate.Gamepad.sThumbLY;vals[2]=g_xstate.Gamepad.sThumbRX;vals[3]=g_xstate.Gamepad.sThumbRY;
  for(i=0;i<4;i++){
   if(vals[i]<g_ax[i].minv)g_ax[i].minv=vals[i];if(vals[i]>g_ax[i].maxv)g_ax[i].maxv=vals[i];
   if(baseline){if(vals[i]<g_ax[i].baseMin)g_ax[i].baseMin=vals[i];if(vals[i]>g_ax[i].baseMax)g_ax[i].baseMax=vals[i];g_ax[i].baseSum+=vals[i];g_ax[i].baseCount++;}
  }
  if(g_xstate.Gamepad.bLeftTrigger>g_ltMax)g_ltMax=g_xstate.Gamepad.bLeftTrigger;
  if(g_xstate.Gamepad.bRightTrigger>g_rtMax)g_rtMax=g_xstate.Gamepad.bRightTrigger;
  g_xButtonSeen|=g_xstate.Gamepad.wButtons; p=x_pov_bucket(g_xstate.Gamepad.wButtons);if(p>=0&&p<8)g_xPovSeen[p]=1;
 } else g_xErrors++;
 if(g_jret==JOYERR_NOERROR){
  g_rawEver=1;g_rawButtonSeen|=g_raw.dwButtons; changed=g_raw.dwButtons^g_prevRawButtons;down=changed&g_raw.dwButtons;
  for(b=0;b<32;b++)if(down&(1UL<<b))g_pressCount[b]++;
  g_prevRawButtons=g_raw.dwButtons; p=pov_bucket(g_raw.dwPOV);if(p>=0&&p<8)g_povSeen[p]=1;
 } else g_rawErrors++;
 g_samples++;
}
static int count_pov_raw(void){int i,n=0;for(i=0;i<8;i++)if(g_povSeen[i])n++;return n;}
static int count_pov_x(void){int i,n=0;for(i=0;i<8;i++)if(g_xPovSeen[i])n++;return n;}
static int count_normal_best(void){int i,n=0;if(!g_rawEver)return count_x_normal();for(i=0;i<10;i++)if(g_rawButtonSeen&(1UL<<i))n++;return n;}
static int count_paddles_best(void){int i,n=0;if(!g_rawEver)return -1;for(i=10;i<14;i++)if(g_rawButtonSeen&(1UL<<i))n++;return n;}
static int count_pov_best(void){return g_rawEver?count_pov_raw():count_pov_x();}

static void close_logs(void){if(g_csv){fclose(g_csv);g_csv=NULL;}if(g_log){fclose(g_log);g_log=NULL;}}
static void write_summary_file(void){
 char fn[160]; void*f; int i,normal,paddles,pov; if(!g_baseName[0])return; sprintf(fn,"%s_SUMMARY.txt",g_baseName);f=fopen(fn,"wt");if(!f)return;
 normal=count_normal_best();paddles=count_paddles_best();pov=count_pov_best();
 fprintf(f,"Xbox Elite Series 2 Control Center - Summary\n============================================\n");
 fprintf(f,"OS=%s\nBackend=%s\nDevice=%s\nJoyID=%d\n",g_os,g_backend,g_device,g_joyId);
 fprintf(f,"Samples=%lu\nXInputErrors=%lu\nRawErrors=%lu\n",g_samples,g_xErrors,g_rawErrors);
 fprintf(f,"LeftStickCoverageX=%d%%\nLeftStickCoverageY=%d%%\nRightStickCoverageX=%d%%\nRightStickCoverageY=%d%%\n",axis_coverage(&g_ax[0]),axis_coverage(&g_ax[1]),axis_coverage(&g_ax[2]),axis_coverage(&g_ax[3]));
 fprintf(f,"LTMax=%u\nRTMax=%u\nButtons1to10=%d/10\n",g_ltMax,g_rtMax,normal);fprintf(f,"PaddleMap=P1:%s,P2:%s,P3:%s,P4:%s\n",map_name(g_paddleMap[0]),map_name(g_paddleMap[1]),map_name(g_paddleMap[2]),map_name(g_paddleMap[3]));if(paddles>=0)fprintf(f,"Paddles11to14=%d/4\n",paddles);else fprintf(f,"Paddles11to14=N/A (sin RAW fisico)\n");fprintf(f,"POVDirections=%d/8\nRumbleCommandsOK=%lu\nRawSource=%s\n",pov,g_rumbleCommands,g_rawSource==1?"XInputBridgeXP":(g_rawSource==2?"WinMM":"XInput fallback"));
 for(i=0;i<4;i++){LONG jitter=(g_ax[i].baseMax>=g_ax[i].baseMin)?g_ax[i].baseMax-g_ax[i].baseMin:0;LONG avg=g_ax[i].baseCount?g_ax[i].baseSum/(LONG)g_ax[i].baseCount:0;fprintf(f,"Axis%d BaselineAvg=%ld BaselineJitter=%ld Min=%ld Max=%ld\n",i,avg,jitter,g_ax[i].minv,g_ax[i].maxv);}
 for(i=0;i<14;i++)fprintf(f,"Button%02dPresses=%lu Seen=%s\n",i+1,g_pressCount[i],(g_rawButtonSeen&(1UL<<i))?"YES":"NO");
 fclose(f);
}
static void start_test(void){
 SYSTEMTIME st; char fn[160]; close_logs(); reset_stats();GetLocalTime(&st);
 sprintf(g_baseName,"XboxElite2_%04u%02u%02u_%02u%02u%02u",st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond);
 sprintf(fn,"%s_RAW.csv",g_baseName);g_csv=fopen(fn,"wt");sprintf(fn,"%s_SESSION.log",g_baseName);g_log=fopen(fn,"wt");
 if(g_csv)fprintf(g_csv,"ms,packet,LX,LY,RX,RY,LT,RT,xbuttons,rawX,rawY,rawZ,rawR,rawU,rawV,rawButtons,POV,xret,joyret\n");
 if(g_log)fprintf(g_log,"XboxElite2ControlCenter v1.5\nOS=%s\nBackend=%s\nDevice=%s\nJoyID=%d\n",g_os,g_backend,g_device,g_joyId);
 g_testState=TEST_BASELINE;g_testStart=GetTickCount();g_recordStart=g_testStart;g_lastCsv=0;scopy(g_status,"CALIBRANDO 3 segundos: no toques sticks ni gatillos.",sizeof(g_status));
}
static void stop_test(void){if(g_testState==TEST_IDLE)return;g_testState=TEST_COMPLETE;write_summary_file();close_logs();scopy(g_status,"Prueba finalizada. SUMMARY, SESSION y RAW CSV generados.",sizeof(g_status));}
static void export_snapshot(void){
 if(!g_baseName[0]){SYSTEMTIME st;GetLocalTime(&st);sprintf(g_baseName,"XboxElite2_SNAPSHOT_%04u%02u%02u_%02u%02u%02u",st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond);}
 write_summary_file();scopy(g_status,"Resumen exportado en la carpeta de la aplicacion.",sizeof(g_status));
}

static void poll_input(void){
 DWORD now=GetTickCount();
 if(g_xget){memset(&g_xstate,0,sizeof(g_xstate));g_xret=g_xget(0,&g_xstate);}else g_xret=ERROR_DEVICE_NOT_CONNECTED;
 {int gotRaw=0;if(g_xraw){XIB_RAW_STATE br;memset(&br,0,sizeof(br));br.cbSize=sizeof(br);g_bridgeRawRet=g_xraw(0,&br);if(g_bridgeRawRet==ERROR_SUCCESS){memset(&g_raw,0,sizeof(g_raw));g_raw.dwSize=sizeof(g_raw);g_raw.dwFlags=JOY_RETURNALL;g_raw.dwXpos=br.rawX;g_raw.dwYpos=br.rawY;g_raw.dwZpos=br.rawZ;g_raw.dwRpos=br.rawR;g_raw.dwUpos=br.rawU;g_raw.dwVpos=br.rawV;g_raw.dwButtons=br.rawButtons;g_raw.dwButtonNumber=br.rawButtonNumber;g_raw.dwPOV=br.rawPOV;g_jret=JOYERR_NOERROR;g_joyId=(int)br.joyId;g_rawSource=1;if(br.productName[0])scopy(g_device,br.productName,sizeof(g_device));gotRaw=1;}}if(!gotRaw){if(g_jpos && g_joyId>=0){memset(&g_raw,0,sizeof(g_raw));g_raw.dwSize=sizeof(g_raw);g_raw.dwFlags=JOY_RETURNALL;g_jret=g_jpos((UINT)g_joyId,&g_raw);if(g_jret==JOYERR_NOERROR){g_rawSource=2;gotRaw=1;}}if(!gotRaw){g_jret=1;g_rawSource=0;}}}
 if(g_rumbleStopAt && (LONG)(now-g_rumbleStopAt)>=0){XINPUT_VIBRATION v;v.wLeftMotorSpeed=0;v.wRightMotorSpeed=0;if(g_xset)g_xset(0,&v);g_rumbleStopAt=0;g_rumbleLeft=0;g_rumbleRight=0;scopy(g_status,"Rumble detenido automaticamente por seguridad (10 s).",sizeof(g_status));}
 if(g_testState==TEST_BASELINE){update_stats(1);if(now-g_testStart>=3000UL){g_testState=TEST_RUNNING;g_recordStart=now;scopy(g_status,"GRABANDO: mueve sticks completos, LT/RT, D-Pad, botones y paddles.",sizeof(g_status));}}
 else if(g_testState==TEST_RUNNING){
  update_stats(0);
  if(g_csv && (now-g_lastCsv)>=20UL){fprintf(g_csv,"%lu,%lu,%d,%d,%d,%d,%u,%u,0x%04X,%lu,%lu,%lu,%lu,%lu,%lu,0x%08lX,%lu,%lu,%lu\n",now-g_recordStart,g_xstate.dwPacketNumber,g_xstate.Gamepad.sThumbLX,g_xstate.Gamepad.sThumbLY,g_xstate.Gamepad.sThumbRX,g_xstate.Gamepad.sThumbRY,g_xstate.Gamepad.bLeftTrigger,g_xstate.Gamepad.bRightTrigger,g_xstate.Gamepad.wButtons,g_raw.dwXpos,g_raw.dwYpos,g_raw.dwZpos,g_raw.dwRpos,g_raw.dwUpos,g_raw.dwVpos,g_raw.dwButtons,g_raw.dwPOV,g_xret,g_jret);g_lastCsv=now;if((g_samples%50UL)==0)fflush(g_csv);}
 }
}
static void rumble(WORD l,WORD r,DWORD ms,const char*label){XINPUT_VIBRATION v;if(!g_xset){scopy(g_status,"XInputSetState no disponible.",sizeof(g_status));return;}v.wLeftMotorSpeed=l;v.wRightMotorSpeed=r;g_rumbleLastRet=g_xset(0,&v);if(g_rumbleLastRet==ERROR_SUCCESS){g_rumbleCommands++;g_rumbleLeft=l;g_rumbleRight=r;sprintf(g_status,"Rumble %s ACTIVO. Presiona STOP para detener (seguridad %lu s).",label,ms/1000UL);g_rumbleStopAt=GetTickCount()+ms;}else sprintf(g_status,"Rumble fallo: XInputSetState=%lu",g_rumbleLastRet);if(g_log)fprintf(g_log,"RUMBLE %s L=%u R=%u ret=%lu\n",label,l,r,g_rumbleLastRet);}
static void rumble_stop(void){XINPUT_VIBRATION v;v.wLeftMotorSpeed=0;v.wRightMotorSpeed=0;if(g_xset)g_rumbleLastRet=g_xset(0,&v);g_rumbleStopAt=0;g_rumbleLeft=0;g_rumbleRight=0;scopy(g_status,"Rumble detenido por STOP.",sizeof(g_status));}
