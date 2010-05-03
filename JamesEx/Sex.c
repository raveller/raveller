/*
** sex.c: Sex main window stuff.
** Copyright (C) 1998, Nullsoft Inc.
** Free for noncommercial use.
** http://www.nullsoft.com/
**/

#include <windows.h>
#include <windowsx.h>
#include <richedit.h>
#include "resource.h"

int moved=0;
BOOL word_wrap = 1;

int config_w=300, config_h=200,config_x=50,config_y=50,config_border=4,config_topborder=10,
	config_color=RGB(255,255,0), config_bcolor1=RGB(150,150,150), config_bcolor2=0, config_icon=1;

char app_name[] = "Sex";
char text_file[MAX_PATH]="";
char ini_file[MAX_PATH]="";

void config_read();
void read_text();
void write_text();
void config_write();
BOOL choose_color(LPCHOOSECOLOR lpcs, HWND hwnd);
void get_font (LOGFONT* plf, CHARFORMAT* pfmt, CHOOSEFONT* pcf);
void set_font (LOGFONT* plf, CHARFORMAT* pfmt, CHOOSEFONT* pcf, BOOL bBold, BOOL bItalic, BOOL bUnder, BOOL bColor, unsigned long color);
void choose_font();
void choose_icon(int icon_num);
void change_icon(HWND hwnd);

HMENU hmenu_main;
HWND hwnd_rich,hwnd_main;
HINSTANCE hMainInstance;
DWORD iconRes;

BOOL systray_add(HWND hwnd, UINT uID, HICON hIcon, LPSTR lpszTip);
BOOL systray_del(HWND hwnd, UINT uID);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst,LPSTR lpszCmdParam, int nCmdShow);
BOOL InitApplication(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpszCmdParam, int nCmdShow) 
{
	MSG msg;
	HACCEL hAccel;
	hMainInstance=hInstance;
	hAccel = LoadAccelerators(hMainInstance,MAKEINTRESOURCE(IDR_ACCELERATOR1));
	if (!LoadLibrary("RICHED32.DLL"))
	{
		MessageBox(NULL, "Could not load RICHED32.DLL", NULL, MB_OK);
		return (FALSE);
	}

	if (!InitApplication(hInstance)) 
	{
		MessageBox(NULL, "Could not initialize application", NULL, MB_OK);
		return (FALSE);
	}

	if (!InitInstance(hInstance, nCmdShow)) 
	{
		MessageBox(NULL, "Could not create window", NULL, MB_OK);
		return (FALSE);
	}

	// message loop
	while (GetMessage(&msg,NULL,0,0)) 
	{
		if (!TranslateAccelerator(hwnd_main,hAccel,&msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	} // while(GetMessage...
	
	return msg.wParam;
} // WinMain

BOOL InitApplication(HINSTANCE hInstance)
{
	WNDCLASS wc;	
	wc.style = CS_DBLCLKS|CS_VREDRAW|CS_HREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = NULL;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = app_name;
	if (!RegisterClass(&wc)) return FALSE;
	return TRUE;
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	int style = 0;
	int exStyle = WS_EX_TOOLWINDOW;
	HWND hwnd;					
	hwnd = CreateWindowEx(exStyle,app_name,app_name,style,0,0,1,1,NULL, NULL,hInstance,NULL);
	
	if (!hwnd) return FALSE;
	
	if (nCmdShow ==	SW_SHOWMAXIMIZED || nCmdShow == SW_MAXIMIZE)
		ShowWindow(hwnd,SW_SHOWNORMAL);
	else
		ShowWindow(hwnd,nCmdShow);

	return TRUE;
}

static BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);
static void OnDestroy(HWND hwnd);
static void OnClose(HWND hwnd);
static void OnActivate(HWND hwnd, UINT state, HWND hwndActDeact, BOOL fMinimized);
static UINT OnNCHitTest(HWND hwnd, int x, int y);
static void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
static void OnSize(HWND hwnd, UINT state, int cx, int cy);
static void OnMove(HWND hwnd, int x, int y);
static void OnPaint(HWND hwnd);

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) 
	{
		HANDLE_MSG(hwnd,WM_CREATE,OnCreate);
		HANDLE_MSG(hwnd,WM_DESTROY,OnDestroy);
		HANDLE_MSG(hwnd,WM_CLOSE,OnClose);
		HANDLE_MSG(hwnd,WM_PAINT,OnPaint);
		HANDLE_MSG(hwnd,WM_MOVE,OnMove);
		HANDLE_MSG(hwnd,WM_SIZE,OnSize);
		HANDLE_MSG(hwnd,WM_COMMAND,OnCommand);
		HANDLE_MSG(hwnd,WM_ACTIVATE,OnActivate);
		HANDLE_MSG(hwnd,WM_NCHITTEST,OnNCHitTest);
		case WM_USER:
			switch (LOWORD(lParam))
			{
				case WM_LBUTTONDOWN:
					SetForegroundWindow(hwnd);
				break;
				case WM_RBUTTONUP:
					{
					POINT p;
					GetCursorPos(&p);
					SetForegroundWindow(hwnd);
					TrackPopupMenu(hmenu_main,TPM_LEFTALIGN|TPM_LEFTBUTTON|TPM_RIGHTBUTTON,p.x,p.y,0,hwnd_main,NULL);
					}
				break;
			}
		return 0;
		default: break;
	}
	return (DefWindowProc(hwnd, uMsg, wParam, lParam));

}

WNDPROC Rich_OldWndProc;
LRESULT CALLBACK Rich_WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg==WM_RBUTTONUP)
	{
		POINT p;
		GetCursorPos(&p);
		TrackPopupMenu(hmenu_main,TPM_LEFTALIGN|TPM_LEFTBUTTON|TPM_RIGHTBUTTON,p.x,p.y,0,hwnd_main,NULL);
	}
	return CallWindowProc(Rich_OldWndProc,hwnd,uMsg,wParam,lParam);
}


static BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct)
{
	hwnd_main=hwnd;
	hmenu_main=LoadMenu(hMainInstance,MAKEINTRESOURCE(IDR_MENU1));
	hmenu_main=GetSubMenu(hmenu_main,0);
	config_read();
	SetWindowLong(hwnd,GWL_STYLE,GetWindowLong(hwnd,GWL_STYLE)&~(WS_CAPTION));
	SetWindowPos(hwnd, 0, 0,0, 0,0, SWP_NOMOVE|SWP_NOSIZE|SWP_NOZORDER|SWP_DRAWFRAME|SWP_NOACTIVATE);
	SetWindowPos(hwnd, 0, config_x, config_y, config_w, config_h, SWP_NOACTIVATE|SWP_NOZORDER);
	systray_add(hwnd,1024,LoadIcon(hMainInstance,MAKEINTRESOURCE(iconRes)),app_name);
	hwnd_rich=CreateWindowEx(WS_EX_CLIENTEDGE,"RichEdit","",
		WS_CHILD|WS_VISIBLE|ES_MULTILINE|ES_AUTOVSCROLL|WS_VSCROLL,  //WS_HSCROLL|ES_AUTOHSCROLL|
		config_border,config_topborder,config_w-config_border*2,config_h-(config_border+config_topborder),
		hwnd, NULL,hMainInstance,NULL);
	Rich_OldWndProc = (WNDPROC) GetWindowLong(hwnd_rich,GWL_WNDPROC);
	SetWindowLong(hwnd_rich,GWL_WNDPROC,(int)Rich_WndProc);
	if (!hwnd_rich) 
	{
		MessageBox(hwnd,"Error creating RichEdit control","Error",MB_OK);
		return 0;
	}
	SendMessage(hwnd_rich,EM_SETBKGNDCOLOR,FALSE,config_color);
	read_text();
	return 1;
}

static void OnDestroy(HWND hwnd)
{
	write_text();
	config_write();
	systray_del(hwnd,1024);
	PostQuitMessage(0);
}

static void OnClose(HWND hwnd)
{
	SetWindowPos(hwnd,HWND_BOTTOM,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE|SWP_DRAWFRAME|SWP_NOACTIVATE);
//	DestroyWindow(hwnd);
}

static void OnActivate(HWND hwnd, UINT state, HWND hwndActDeact, BOOL fMinimized)
{
	if (state==WA_INACTIVE)
	{
		if (moved)
		{
			moved=0;
			config_write();
		}
		write_text();
		SetPriorityClass(hMainInstance,IDLE_PRIORITY_CLASS);
	}
	else
	{
		SetPriorityClass(hMainInstance,NORMAL_PRIORITY_CLASS);
	}
}

static UINT OnNCHitTest(HWND hwnd, int x, int y)
{
	POINT p;
	RECT r;
	p.x=x;p.y=y;
	GetClientRect(hwnd,&r);
	ScreenToClient(hwnd,&p);
	if (p.x <= config_border && p.y <= config_topborder*3) return HTTOPLEFT;
	if (p.x <= config_border*3 && p.y <= config_topborder) return HTTOPLEFT;
	if (p.x >= r.right-config_border && p.y >= r.bottom-config_border*3) return HTBOTTOMRIGHT;
	if (p.x >= r.right-config_border*3 && p.y >= r.bottom-config_border) return HTBOTTOMRIGHT;
	if (p.x >= r.right-config_border && p.y <= config_border*3) return HTTOPRIGHT;
	if (p.x >= r.right-config_border*3 && p.y <= config_border) return HTTOPRIGHT;
	if (p.x <= config_border && p.y >= r.bottom-config_border*3) return HTBOTTOMLEFT;
	if (p.x <= config_border*3 && p.y >= r.bottom-config_border) return HTBOTTOMLEFT;
	if (p.y <= config_topborder) return HTCAPTION;
	if (p.x <= config_border) return HTLEFT;
	if (p.y >= r.bottom-config_border) return HTBOTTOM;
	if (p.x >= r.right-config_border) return HTRIGHT;
	return HTCLIENT;
}

BOOL ModifyStyle(HWND hWnd, DWORD dwAdd, DWORD dwRemove, BOOL bEx)
{
    DWORD dwStyle,dwNewStyle;
    SetLastError(0);

    dwStyle = GetWindowLong(hWnd, (bEx ? GWL_EXSTYLE : GWL_STYLE));
    dwNewStyle = (dwStyle & (~dwRemove)) | dwAdd;
    SetWindowLong(hWnd, (bEx ? GWL_EXSTYLE : GWL_STYLE), dwNewStyle);

    SetWindowPos(hWnd, NULL, 0, 0, 0, 0, SWP_NOZORDER | SWP_NOMOVE | SWP_NOSIZE);

    return (GetLastError() == 0);
}

static void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	LOGFONT lf={0,};
	CHOOSEFONT cf={sizeof(cf),hwnd,0,&lf,0,
		CF_EFFECTS|CF_SCREENFONTS|CF_INITTOLOGFONTSTRUCT,
		0,};
	CHARFORMAT fmt={sizeof(fmt),};
	CHOOSECOLOR cs;

    switch (id)
	{
		case IDM_ABOUT:
			MessageBox(hwnd,"Sex v0.1\n"
				            "Copyright (C) 1998, Nullsoft Inc.","About sex",MB_OK);
		return;
		case IDM_PASTE:
            SendMessage(hwnd_rich, WM_PASTE, 0, 0);
		return;
		case IDM_COPY:
            SendMessage(hwnd_rich, WM_COPY, 0, 0);
        return;
		case IDM_CUT:
            SendMessage(hwnd_rich, WM_CUT, 0, 0);
        return;
		case IDM_CLOSE:
			SendMessage(hwnd,WM_CLOSE,0,0);
		return;
		case IDM_QUIT:
			DestroyWindow(hwnd);
		return;
		case IDM_FONT:
			{
				get_font (&lf, &fmt, &cf);
				
				if (ChooseFont(&cf))
				{
                    set_font (&lf, &fmt, &cf, FALSE, FALSE, FALSE, FALSE, FALSE);
				}
			}
		return;
		case IDM_BGCOLOR:
			{
				if (choose_color(&cs, hwnd))
				{
					config_color=cs.rgbResult;
					config_write();
					SendMessage(hwnd_rich,EM_SETBKGNDCOLOR,FALSE,config_color);
				}
			}
		return;
        case IDM_FGCOLOR:
            {
				get_font (&lf, &fmt, &cf);

				if (choose_color(&cs, hwnd))
				{
                    set_font (&lf, &fmt, &cf, FALSE, FALSE, FALSE, TRUE, cs.rgbResult);
                }
            }
		return;
        case IDM_UNDERLINE:
            {
				get_font (&lf, &fmt, &cf);

                set_font (&lf, &fmt, &cf, FALSE, FALSE, TRUE, FALSE, 0);
            }
		return;
        case IDM_ITALIC:
            {
				get_font (&lf, &fmt, &cf);

                set_font (&lf, &fmt, &cf, FALSE, TRUE, FALSE, FALSE, 0);
            }
		return;
        case IDM_BOLD:
            {
				get_font (&lf, &fmt, &cf);

                set_font (&lf, &fmt, &cf, TRUE, FALSE, FALSE, FALSE, 0);
            }
		return;
        case IDM_WORDWRAP:
            {
                if (word_wrap)
                {
                    ModifyStyle(hwnd_rich, 0 ,WS_HSCROLL|ES_AUTOHSCROLL,  0 );
                    word_wrap = 0;
                }
                else
                {
                    ModifyStyle(hwnd_rich, WS_HSCROLL|ES_AUTOHSCROLL, 0 , 0 );
                    word_wrap = 1;
                }
            }
		return;
        case IDM_REDL:
            {
                if (config_icon != 1)
                {
					choose_icon(1);
					change_icon(hwnd);
                }
            }
		return;
        case IDM_BLUEL:
            {
                if (config_icon != 2)
                {
					choose_icon(2);
					change_icon(hwnd);
                }
            }
		return;
        case IDM_BLACKL:
            {
                if (config_icon != 3)
                {
					choose_icon(3);
					change_icon(hwnd);
                }
            }
		return;
        case IDM_BLUER:
            {
                if (config_icon != 4)
                {
					choose_icon(4);
					change_icon(hwnd);
                }
            }
		return;
    }
}

static void OnSize(HWND hwnd, UINT state, int cx, int cy)
{
	moved=1;
	SetWindowPos(hwnd_rich, 0, config_border,config_topborder, cx-config_border*2,cy-(config_border+config_topborder), SWP_NOACTIVATE|SWP_NOZORDER);
}

static void OnMove(HWND hwnd, int x, int y)
{
	moved=1;
}

static void OnPaint(HWND hwnd)
{
	PAINTSTRUCT ps;
	HDC hdc;
	HBRUSH hOldBrush,hBrush;
	HPEN hPen, hOldPen;
	RECT r;
	hdc = BeginPaint(hwnd,&ps);
	GetClientRect(hwnd,&r);
	hPen=CreatePen(PS_SOLID,0,config_bcolor2);
	{
		LOGBRUSH lb={BS_SOLID,config_bcolor1,};
		hBrush=CreateBrushIndirect(&lb); 
	}

	hOldPen=SelectObject(hdc,hPen);
	hOldBrush=SelectObject(hdc,hBrush);
	Rectangle(hdc,r.left,r.top,r.right,r.bottom);
	SelectObject(hdc,hOldPen);
	SelectObject(hdc,hOldBrush);
	DeleteObject(hPen);
	DeleteObject(hBrush);
	EndPaint(hwnd,&ps);
}


static int _r_i(char *name, int def)
{
	return GetPrivateProfileInt(app_name,name,def,ini_file);
}
#define RI(x) (( x ) = _r_i(#x,( x )))
static void _w_i(char *name, int d)
{
	char str[120];
	wsprintf(str,"%d",d);
	WritePrivateProfileString(app_name,name,str,ini_file);
}
#define WI(x) _w_i(#x,( x ))

static void _r_s(char *name,char *data, int mlen)
{
	char buf[2048];
	strcpy_s(buf,sizeof(buf),data);
	GetPrivateProfileString(app_name,name,buf,data,mlen,ini_file);
}
#define RS(x) (_r_s(#x,x,sizeof(x)))

static void _w_s(char *name, char *data)
{
	WritePrivateProfileString(app_name,name,data,ini_file);
}
#define WS(x) (_w_s(#x,x))



void config_read()
{
	char *p,*ip;

	GetModuleFileName(hMainInstance,ini_file,sizeof(ini_file));
	strcpy_s(text_file,sizeof(text_file),ini_file);
	p=ini_file+strlen(ini_file); ip=p;
	while (p >= ini_file && *p != '.') p--;
	strcpy_s(++p,ip-p+1,"ini");
	p=text_file+strlen(text_file); ip=p;
	while (p >= text_file && *p != '.') p--;
	strcpy_s(++p,ip-p+1,"rtf");
	RI(config_x);
	RI(config_y);
	RI(config_w);
	RI(config_h);
	RI(config_border);
	RI(config_color);
	RI(config_bcolor1);
	RI(config_bcolor2);
	RI(config_icon);
	choose_icon(config_icon);
}

static HANDLE esFile;

DWORD CALLBACK esCb(DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG FAR *pcb)
{
	if (dwCookie == 1) // write
	{
		WriteFile(esFile,pbBuff,cb,pcb,NULL);
	}
	else // read
	{
		ReadFile(esFile,pbBuff,cb,pcb,NULL);
	}
	return 0;
}
 


void read_text()
{
	esFile=CreateFile(text_file,GENERIC_READ,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	if (esFile)
	{
		EDITSTREAM es;
		es.dwCookie=0;
		es.pfnCallback=esCb;
		SendMessage(hwnd_rich,EM_STREAMIN,SF_RTF,(LPARAM) &es);
		CloseHandle(esFile);
	}
}

void write_text()
{
	esFile=CreateFile(text_file,GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
	if (esFile) 
	{
		EDITSTREAM es;
		es.dwCookie=1;
		es.pfnCallback=esCb;
		SendMessage(hwnd_rich,EM_STREAMOUT,SF_RTF,(LPARAM) &es);
		CloseHandle(esFile);
	} else  MessageBox(hwnd_main,"Error writing .rtf", "Error",0);
}

void config_write()
{
	RECT r;
	GetWindowRect(hwnd_main,&r);
	config_x=r.left;
	config_y=r.top;
	config_w=r.right-r.left;
	config_h=r.bottom-r.top;
	WI(config_x);
	WI(config_y);
	WI(config_w);
	WI(config_h);
	WI(config_border);
	WI(config_color);
	WI(config_bcolor1);
	WI(config_bcolor2);
	WI(config_icon);
}

BOOL choose_color(LPCHOOSECOLOR lpcs, HWND hwnd)
{
    CHOOSECOLOR dcs;
	static COLORREF custcolors[16];

    lpcs->lStructSize = sizeof(dcs);
    lpcs->hwndOwner = hwnd;
    lpcs->hInstance = 0;
    lpcs->rgbResult=config_color;
    lpcs->lpCustColors = custcolors;
    lpcs->Flags = CC_RGBINIT|CC_FULLOPEN;
    return ChooseColor(lpcs);
}

void get_font (LOGFONT* plf, CHARFORMAT* pfmt, CHOOSEFONT* pcf)
{
	SendMessage(hwnd_rich,EM_GETCHARFORMAT,1,(LPARAM)pfmt);

    if (pfmt->dwMask & CFM_FACE) strcpy_s(plf->lfFaceName,sizeof(plf->lfFaceName),pfmt->szFaceName);
	else plf->lfFaceName[0]=0;
	if (pfmt->dwMask & CFM_SIZE) plf->lfHeight=pfmt->yHeight/15;
	else plf->lfHeight=0;
	if (pfmt->dwMask & CFM_COLOR) pcf->rgbColors=pfmt->crTextColor;
	else pcf->rgbColors=0xffffff;
	plf->lfItalic=(pfmt->dwEffects&CFE_ITALIC)?1:0;
	plf->lfWeight=(pfmt->dwEffects&CFE_BOLD)?FW_BOLD:FW_NORMAL;
	plf->lfUnderline=(pfmt->dwEffects&CFE_UNDERLINE)?1:0;
	plf->lfStrikeOut=(pfmt->dwEffects&CFE_STRIKEOUT)?1:0;
	plf->lfCharSet=DEFAULT_CHARSET;
	plf->lfOutPrecision=OUT_DEFAULT_PRECIS;
	plf->lfClipPrecision=CLIP_DEFAULT_PRECIS;
	plf->lfQuality=DEFAULT_QUALITY;
	plf->lfPitchAndFamily=pfmt->bPitchAndFamily;
}

void set_font (LOGFONT* plf, CHARFORMAT* pfmt, CHOOSEFONT* pcf, BOOL bBold, BOOL bItalic, BOOL bUnder, BOOL bColor, unsigned long color)
{
    pfmt->dwMask=CFM_BOLD|CFM_COLOR|CFM_ITALIC|CFM_STRIKEOUT|CFM_UNDERLINE;
    if (plf->lfFaceName[0]) pfmt->dwMask|=CFM_FACE;
    if (plf->lfHeight) pfmt->dwMask|=CFM_SIZE;
    pfmt->dwEffects=0;
    if ((plf->lfItalic && !bItalic) ||
        (!plf->lfItalic && bItalic)) pfmt->dwEffects |= CFE_ITALIC;

    if ((plf->lfUnderline && !bUnder) ||
        (!plf->lfUnderline && bUnder)) pfmt->dwEffects |= CFE_UNDERLINE;
    if (plf->lfStrikeOut) pfmt->dwEffects |= CFE_STRIKEOUT;

    if ((plf->lfWeight!=FW_NORMAL && !bBold) ||
        (plf->lfWeight==FW_NORMAL && bBold)) pfmt->dwEffects |= CFE_BOLD;
    pfmt->yHeight = pcf->iPointSize*2;

    if (bColor) pfmt->crTextColor=color;
    else pfmt->crTextColor = pcf->rgbColors;

    pfmt->bPitchAndFamily=plf->lfPitchAndFamily;
    pfmt->bCharSet = plf->lfCharSet;
    strcpy_s(pfmt->szFaceName,sizeof(pfmt->szFaceName),plf->lfFaceName);
    SendMessage(hwnd_rich,EM_SETCHARFORMAT,SCF_SELECTION,(LPARAM)pfmt);
}

void choose_icon(int icon_num)
{
	config_icon = icon_num;
	switch (icon_num)
	{
	case 4:  // Blue Right
		iconRes = IDI_ICON1;
		break;
	case 3: // Black Left
		iconRes = IDI_ICON3;
		break;
	case 2: // Blue Left
		iconRes = IDI_ICON4;
		break;
	case 1: // Red Left
		iconRes = IDI_ICON2;
		break;
	}
}

void change_icon(HWND hwnd)
{
	systray_del(hwnd,1024);
	systray_add(hwnd,1024,LoadIcon(hMainInstance,MAKEINTRESOURCE(iconRes)),app_name);
}