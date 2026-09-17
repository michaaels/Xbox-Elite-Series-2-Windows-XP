/* visual paddle mapping */
static int g_paddleMap[4]={1,2,3,4};
static int g_paddleDraft[4]={1,2,3,4};
static int g_mapOpen=0;
static int g_mapSelected=0;
static const char *g_mapIni=".\\XInputBridgeXP.ini";

/* dynamic game profile / deployment manager */
static int g_gamesOpen=0;
static char g_gameExePath[MAX_PATH]={0};
static char g_gameDir[MAX_PATH]={0};
static char g_gameExeName[96]={0};
static char g_gameName[96]="Ningun juego seleccionado";
static char g_exeDir[MAX_PATH]={0};
static const char *g_appIni=".\\XboxElite2ControlCenter.ini";

/* statistics */
typedef struct { LONG minv,maxv,baseMin,baseMax; DWORD baseCount; LONG baseSum; } AXSTAT;
static AXSTAT g_ax[4]; /* LX LY RX RY */
static BYTE g_ltMax=0,g_rtMax=0;
static DWORD g_rawButtonSeen=0,g_xButtonSeen=0;
static DWORD g_pressCount[32];
static DWORD g_prevRawButtons=0;
static BYTE g_povSeen[8];
static BYTE g_xPovSeen[8];
static DWORD g_xErrors=0,g_rawErrors=0,g_samples=0;

/* button rectangles */
typedef struct { int x,y,w,h; const char* label; int id; } UIBUTTON;
static UIBUTTON g_buttons[] = {
 {28,414,120,32,"INICIAR PRUEBA",1}, {158,414,86,32,"DETENER",2}, {254,414,86,32,"RESET",3}, {350,414,118,32,"EXPORTAR",4},
 {494,414,92,32,"MOTOR L",5}, {596,414,92,32,"MOTOR R",6}, {698,414,92,32,"AMBOS",7}, {800,414,92,32,"STOP",8}
};
#define N_UIBUTTONS ((int)(sizeof(g_buttons)/sizeof(g_buttons[0])))

static int slen(const char*s){int n=0;while(s&&s[n])n++;return n;}
static void scopy(char*d,const char*s,int max){int i=0;if(max<=0)return;while(s&&s[i]&&i<max-1){d[i]=s[i];i++;}d[i]=0;}
static LONG labs_(LONG v){return v<0?-v:v;}
static int clampi(int v,int lo,int hi){return v<lo?lo:(v>hi?hi:v);}
static int popcount32(DWORD v){int n=0;while(v){n+=(int)(v&1);v>>=1;}return n;}

static const char* map_name(int t){
 static const char* n[12]={"NONE","A","B","X","Y","LB","RB","BACK","START","L3","R3","GUIDE"};
 if(t<0||t>11)return "NONE";return n[t];
}
static void load_paddle_map(void){
 int i,defv[4]={1,2,3,4}; char key[32];
 for(i=0;i<4;i++){sprintf(key,"Button%dTarget",11+i);g_paddleMap[i]=(int)GetPrivateProfileIntA("Paddles",key,defv[i],g_mapIni);if(g_paddleMap[i]<0||g_paddleMap[i]>11)g_paddleMap[i]=defv[i];g_paddleDraft[i]=g_paddleMap[i];}
}
static void save_paddle_map(void){
 int i,ok=1;char key[32],val[16];
 for(i=0;i<4;i++){sprintf(key,"Button%dTarget",11+i);sprintf(val,"%d",g_paddleDraft[i]);if(!WritePrivateProfileStringA("Paddles",key,val,g_mapIni))ok=0;}
 if(!ok){scopy(g_status,"No se pudo guardar XInputBridgeXP.ini. Usa una carpeta con permiso de escritura.",sizeof(g_status));return;}
 for(i=0;i<4;i++)g_paddleMap[i]=g_paddleDraft[i];
 if(g_xreload){DWORD r=g_xreload();sprintf(g_status,"Mapeo aplicado en vivo. P1>%s  P2>%s  P3>%s  P4>%s",map_name(g_paddleMap[0]),map_name(g_paddleMap[1]),map_name(g_paddleMap[2]),map_name(g_paddleMap[3]));if(g_log)fprintf(g_log,"PADDLE_MAP P1=%s P2=%s P3=%s P4=%s reload=%lu\n",map_name(g_paddleMap[0]),map_name(g_paddleMap[1]),map_name(g_paddleMap[2]),map_name(g_paddleMap[3]),r);}
 else scopy(g_status,"Mapeo guardado. Reinicia la aplicacion o el juego para aplicarlo.",sizeof(g_status));
}
static int inrect(int x,int y,int rx,int ry,int rw,int rh){return x>=rx&&x<rx+rw&&y>=ry&&y<ry+rh;}

static void path_join(char*out,int max,const char*dir,const char*name){int n=0,i=0;if(max<=0)return;while(dir&&dir[n]&&n<max-1){out[n]=dir[n];n++;}if(n>0&&out[n-1]!='\\'&&out[n-1]!='/'&&n<max-1)out[n++]='\\';while(name&&name[i]&&n<max-1)out[n++]=name[i++];out[n]=0;}
static void dirname_from_file(char*out,int max,const char*file){int i,last=-1;scopy(out,file,max);for(i=0;out[i];i++)if(out[i]=='\\'||out[i]=='/')last=i;if(last>=0)out[last]=0;else out[0]=0;}
static int file_exists(const char*path){HMODULE k=GetModuleHandleA("kernel32.dll");PFN_GetFileAttributesA_ f=k?(PFN_GetFileAttributesA_)GetProcAddress(k,"GetFileAttributesA"):NULL;DWORD a;if(!f)return 0;a=f(path);return a!=INVALID_FILE_ATTRIBUTES && !(a&FILE_ATTRIBUTE_DIRECTORY);}
static DWORD get_last_error_(void){HMODULE k=GetModuleHandleA("kernel32.dll");PFN_GetLastError_ f=k?(PFN_GetLastError_)GetProcAddress(k,"GetLastError"):NULL;return f?f():0;}
static int path_eq_ci(const char*a,const char*b){int i=0;char ca,cb;if(!a||!b)return 0;for(;;){ca=a[i];cb=b[i];if(ca>='A'&&ca<='Z')ca=(char)(ca+32);if(cb>='A'&&cb<='Z')cb=(char)(cb+32);if(ca!=cb)return 0;if(!ca)return 1;i++;}}
static int copy_file_(const char*src,const char*dst){HMODULE k=GetModuleHandleA("kernel32.dll");PFN_CopyFileA_ f=k?(PFN_CopyFileA_)GetProcAddress(k,"CopyFileA"):NULL;if(path_eq_ci(src,dst))return 1;return f?f(src,dst,FALSE):0;}
static void basename_from_file(char*out,int max,const char*file){int i,last=-1,n=0;if(max<=0)return;for(i=0;file&&file[i];i++)if(file[i]=='\\'||file[i]=='/')last=i;for(i=last+1;file&&file[i]&&n<max-1;i++)out[n++]=file[i];out[n]=0;}
static void display_name_from_exe(char*out,int max,const char*exe){int i;basename_from_file(out,max,exe);for(i=0;out[i];i++){if(out[i]=='.' && (out[i+1]=='e'||out[i+1]=='E') && (out[i+2]=='x'||out[i+2]=='X') && (out[i+3]=='e'||out[i+3]=='E') && out[i+4]==0){out[i]=0;break;}}if(!out[0])scopy(out,"Juego",max);}
static void normalize_game_profile(void){if(g_gameExePath[0]){dirname_from_file(g_gameDir,MAX_PATH,g_gameExePath);basename_from_file(g_gameExeName,sizeof(g_gameExeName),g_gameExePath);display_name_from_exe(g_gameName,sizeof(g_gameName),g_gameExePath);}else{g_gameDir[0]=0;g_gameExeName[0]=0;scopy(g_gameName,"Ningun juego seleccionado",sizeof(g_gameName));}}
static void load_game_profile(void){HMODULE k=GetModuleHandleA("kernel32.dll");PFN_GetPrivateProfileStringA_ f=k?(PFN_GetPrivateProfileStringA_)GetProcAddress(k,"GetPrivateProfileStringA"):NULL;if(!f)return;f("Game","ExePath","",g_gameExePath,MAX_PATH,g_appIni);normalize_game_profile();}
static void save_game_profile(void){WritePrivateProfileStringA("Game","ExePath",g_gameExePath,g_appIni);}
static int browse_game(void){HMODULE c=LoadLibraryA("comdlg32.dll");PFN_GetOpenFileNameA_ f=c?(PFN_GetOpenFileNameA_)GetProcAddress(c,"GetOpenFileNameA"):NULL;OPENFILENAMEA_ o;char file[MAX_PATH];const char*filter="Ejecutables de juegos (*.exe)\0*.exe\0Todos los archivos\0*.*\0\0";if(!f){scopy(g_status,"No se pudo abrir el selector de archivos.",sizeof(g_status));return 0;}memset(file,0,sizeof(file));memset(&o,0,sizeof(o));o.lStructSize=sizeof(o);o.hwndOwner=g_hwnd;o.lpstrFilter=filter;o.lpstrFile=file;o.nMaxFile=MAX_PATH;o.lpstrTitle="Selecciona el ejecutable del juego";o.Flags=OFN_FILEMUSTEXIST|OFN_PATHMUSTEXIST|OFN_HIDEREADONLY;if(!f(&o))return 0;scopy(g_gameExePath,file,MAX_PATH);normalize_game_profile();save_game_profile();sprintf(g_status,"Juego seleccionado: %s",g_gameName);return 1;}
static int selected_game_ok(void){return g_gameExePath[0] && file_exists(g_gameExePath);}
static int game_file(const char*name,char*out){if(!g_gameDir[0]){if(out)out[0]=0;return 0;}path_join(out,MAX_PATH,g_gameDir,name);return file_exists(out);}
static void game_status_text(char*out,int max){char p[MAX_PATH];int exe=selected_game_ok();int xb=game_file("xinput1_3.dll",p);int x9=game_file("xinput9_1_0.dll",p);int xi=game_file("XInputBridgeXP.ini",p);if(!g_gameExePath[0])scopy(out,"Selecciona cualquier .EXE de juego",max);else sprintf(out,"EXE %s | XInput 1.3 %s | 9.1.0 %s | Perfil %s",exe?"OK":"NO",xb?"OK":"NO",x9?"OK":"NO",xi?"OK":"NO");}
static void write_current_map_to_ini(const char*ini){int i;char key[32],val[16];for(i=0;i<4;i++){sprintf(key,"Button%dTarget",11+i);sprintf(val,"%d",g_paddleMap[i]);WritePrivateProfileStringA("Paddles",key,val,ini);}}
static int prepare_existing_target(const char*dst){HMODULE k=GetModuleHandleA("kernel32.dll");PFN_GetFileAttributesA_ ga=k?(PFN_GetFileAttributesA_)GetProcAddress(k,"GetFileAttributesA"):NULL;PFN_SetFileAttributesA_ sa=k?(PFN_SetFileAttributesA_)GetProcAddress(k,"SetFileAttributesA"):NULL;DWORD a;if(!file_exists(dst)||!ga||!sa)return 1;a=ga(dst);if(a!=INVALID_FILE_ATTRIBUTES && (a&1UL))sa(dst,a&~1UL);return 1;}
static int backup_then_copy(const char*srcName,const char*dstName){char src[MAX_PATH],dst[MAX_PATH],bak[MAX_PATH];DWORD e;path_join(src,MAX_PATH,g_exeDir,srcName);path_join(dst,MAX_PATH,g_gameDir,dstName);if(!file_exists(src)){sprintf(g_status,"Paquete incompleto: falta %s junto al Control Center.",srcName);return 0;}if(path_eq_ci(src,dst))return 1;if(file_exists(dst)){sprintf(bak,"%s.xboxelite2xp.bak",dst);if(!file_exists(bak))copy_file_(dst,bak);prepare_existing_target(dst);}if(!copy_file_(src,dst)){e=get_last_error_();if(e==5)sprintf(g_status,"Acceso denegado (%lu). Cierra el juego y ejecuta Control Center como administrador.",e);else if(e==32)sprintf(g_status,"Archivo en uso (%lu). Cierra el juego antes de instalar el Bridge.",e);else sprintf(g_status,"No se pudo copiar %s. Error Win32=%lu.",dstName,e);return 0;}return 1;}
static void install_bridge_game(void){char ini[MAX_PATH],srcini[MAX_PATH];if(!selected_game_ok()){scopy(g_status,"Primero selecciona un ejecutable de juego valido.",sizeof(g_status));return;}if(!backup_then_copy("xinput1_3.dll","xinput1_3.dll"))return;if(!backup_then_copy("xinput9_1_0.dll","xinput9_1_0.dll"))return;path_join(ini,MAX_PATH,g_gameDir,"XInputBridgeXP.ini");path_join(srcini,MAX_PATH,g_exeDir,"XInputBridgeXP.ini");if(!file_exists(ini)){if(!copy_file_(srcini,ini)){DWORD e=get_last_error_();sprintf(g_status,"DLL copiados, pero no se pudo crear el perfil INI. Error=%lu.",e);return;}}write_current_map_to_ini(ini);sprintf(g_status,"Bridge instalado en %s. Se crearon backups si habia DLL previos.",g_gameName);}
static void apply_map_to_game(void){char ini[MAX_PATH];if(!selected_game_ok()){scopy(g_status,"Primero selecciona un ejecutable de juego valido.",sizeof(g_status));return;}path_join(ini,MAX_PATH,g_gameDir,"XInputBridgeXP.ini");if(!file_exists(ini)){scopy(g_status,"No existe XInputBridgeXP.ini. Usa INSTALAR BRIDGE primero.",sizeof(g_status));return;}write_current_map_to_ini(ini);sprintf(g_status,"Mapeo P1-P4 aplicado a %s.",g_gameName);}
static void load_map_from_game(void){char ini[MAX_PATH],key[32];int i,defv[4]={1,2,3,4};if(!selected_game_ok()){scopy(g_status,"Primero selecciona un ejecutable de juego valido.",sizeof(g_status));return;}path_join(ini,MAX_PATH,g_gameDir,"XInputBridgeXP.ini");if(!file_exists(ini)){scopy(g_status,"No existe perfil Bridge en ese juego.",sizeof(g_status));return;}for(i=0;i<4;i++){sprintf(key,"Button%dTarget",11+i);g_paddleDraft[i]=(int)GetPrivateProfileIntA("Paddles",key,defv[i],ini);if(g_paddleDraft[i]<0||g_paddleDraft[i]>11)g_paddleDraft[i]=defv[i];}save_paddle_map();sprintf(g_status,"Mapeo de %s cargado al Control Center.",g_gameName);}
static void launch_game(void){HMODULE sh=LoadLibraryA("shell32.dll");PFN_ShellExecuteA_ f=sh?(PFN_ShellExecuteA_)GetProcAddress(sh,"ShellExecuteA"):NULL;if(!selected_game_ok()){scopy(g_status,"No se encontro el ejecutable seleccionado.",sizeof(g_status));return;}if(!f){scopy(g_status,"ShellExecuteA no disponible.",sizeof(g_status));return;}f(g_hwnd,"open",g_gameExePath,NULL,g_gameDir,SW_SHOWNORMAL);sprintf(g_status,"Iniciando %s...",g_gameName);}

static void set_exe_dir(void){
 char p[MAX_PATH]; int i,last=-1; if(!GetModuleFileNameA(NULL,p,MAX_PATH))return;
 for(i=0;p[i];i++) if(p[i]=='\\'||p[i]=='/')last=i;
 if(last>0){p[last]=0;scopy(g_exeDir,p,MAX_PATH);SetCurrentDirectoryA(p);}else scopy(g_exeDir,".",MAX_PATH);
}
static void detect_os(void){
 HMODULE ntdll=LoadLibraryA("ntdll.dll"); PFN_RtlGetVersion rv=NULL; RTL_OSVERSIONINFOW_ o;
 memset(&o,0,sizeof(o)); o.dwOSVersionInfoSize=sizeof(o);
 if(ntdll)rv=(PFN_RtlGetVersion)GetProcAddress(ntdll,"RtlGetVersion");
 if(rv && rv(&o)==0) sprintf(g_os,"Windows NT %lu.%lu build %lu",o.dwMajorVersion,o.dwMinorVersion,o.dwBuildNumber);
 else scopy(g_os,"Windows (version no disponible)",sizeof(g_os));
}
static void enable_dpi_if_available(void){
 HMODULE u=GetModuleHandleA("user32.dll"); PFN_SetProcessDPIAware f=u?(PFN_SetProcessDPIAware)GetProcAddress(u,"SetProcessDPIAware"):NULL; if(f)f();
}
