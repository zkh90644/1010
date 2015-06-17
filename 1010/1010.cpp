// 1010.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "resource.h"
#include "Block.h"
#include "Background.h"
#include "Bigsquare.h"

using namespace std;

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];								// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];								// The title bar text

// Foward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);


Background bg;
Bigsquare bs[3];
int begin_game = 0;
bool endgame = false;
int clickNum,score=0;
RECT square_rect, bg_rect;
HDC hdc,mdc,imghdc;
HBITMAP bitmap, bitmap_logo, bitmap_cup,bitmap_score,bitmap_restart,bitmap_exit;
RECT rt;
HBRUSH hbrush_bg,hbrush_score;
HPEN hpen_bord;
char num[50];
HFONT score_font;
POINT mouse_point_last;

void init(HDC hdc){
	//MessageBox(NULL, "游戏开始", "开始", MB_OK);
	bg.drawBack(hdc);
	begin_game = 1;
	clickNum = 0;
	score = 0;
	bg_rect.left = bg.pos.x;
	bg_rect.right = bg_rect.left + (10 * 31);
	bg_rect.top = bg.pos.y;
	bg_rect.bottom = bg_rect.top + (10 * 31);
	bs[0].setBasic(0, 440);
	bs[1].setBasic(bs[0].pos.x + 31 * 5, bs[0].pos.y);
	bs[2].setBasic(bs[1].pos.x + 31 * 5, bs[1].pos.y);
	endgame = false;
}

void resetBigSquare(HDC hdc ){
	int r = (unsigned)time(0);
	for (int i = 0; i < 3; i++)
	{
		r = bs[i].randomStyle(r);
		bs[i].drawSquare(hdc);
	}
}

bool finished(Background bg, Bigsquare bs[]){
	bool flag = false;
	int length = 0,num = 0;
	for (int i = 0; i < 3; i++)		//选择对应的bs对象
	{
		if (bs[i].type != TYPE_NULL){
			switch (bs[i].type)			//确定对应的bs的类型。线、折线、块
			{
			case TYPE_1:				//线
				if (bs[i].model >3)		//横线
				{
					for (int j = 0; j < (10-bs[i].model+2); j++)
					{
						for (int k = 0; k < 10; k++)	//确定空的点
						{
							for (length = 0; length < (bs[i].model-2) ; length++)
							{
								if (bg.arr[j + length][k].type == 1)
									break;
							}
							if (length == (bs[i].model-2))
							{
								flag = true;
							}
						}
						if (flag == true)
						{
							break;
						}
					}
				}
				else							//纵向
				{
					for (int j = 0; j < 10; j++)
					{
						for (int k = 0; k < (10 - bs[i].model - 2); k++)
						{
							for (length = 0; length < (bs[i].model + 2); length++)
							{
								if (bg.arr[j][k + length].type == 1)
									break;
							}
							if (length == (bs[i].model + 2))
							{
								flag = true;
							}
						}
						if (flag == true)
						{
							break;
						}
					}
				}
				break;
			case TYPE_2:				//折线
				if (bs[i].model<=3)
				{
					int j = 0;
					switch (bs[i].model % 4)		//确定折线方向
					{
					case 0:
						for (j = 0; j < 10; j++)
						{
							for (int k = 0; k < 10; k++)
							{
								if (bg.arr[j][k].type == 0 && j + 1<10 && k + 1<10 && bg.arr[j + 1][k + 1].type == 0 && bg.arr[j][k + 1].type == 0)
								{
									flag = true;
								}
							}
							if (flag == true)
							{
								break;
							}
						}
						break;
					case 1:
						for (j = 0; j < 10; j++)
						{
							for (int k = 0; k < 10; k++)
							{
								if (bg.arr[j][k].type == 0 && j + 1<10 && k - 1 >= 0 && bg.arr[j + 1][k - 1].type == 0 && bg.arr[j + 1][k].type == 0)
								{
									flag = true;
								}
							}
							if (flag == true)
							{
								break;
							}
						}
						break;
					case 2:
						for (j = 0; j < 10; j++)
						{
							for (int k = 0; k < 10; k++)
							{
								if (bg.arr[j][k].type == 0 && j + 1<10 && k + 1<10 && bg.arr[j + 1][k].type == 0 && bg.arr[j][k + 1].type == 0)
								{
									flag = true;
								}
							}
							if (flag == true)
							{
								break;
							}
						}
						break;
					case 3:
						for (j = 0; j < 10; j++)
						{
							for (int k = 0; k < 10; k++)
							{
								if (bg.arr[j][k].type == 0 && j + 1<10 && k + 1<10 && bg.arr[j + 1][k].type == 0 && bg.arr[j + 1][k + 1].type == 0)
								{
									flag = true;
								}
							}
							if (flag == true)
							{
								break;
							}
						}
						break;
					}
				}
				else
				{
					int j = 0;
					switch (bs[i].model % 4)		//确定折线方向
					{
					case 0:
						for (j = 0; j < 10; j++)
						{
							for (int k = 0; k < 10; k++)
							{
								if (bg.arr[j][k].type == 0 && j + 2 < 10 && k + 2 < 10 && bg.arr[j + 2][k + 2].type == 0
									&& bg.arr[j][k + 2].type == 0 && bg.arr[j][k + 1].type == 0 && bg.arr[j + 1][k + 2].type == 0)
								{
									flag = true;
								}
							}
							if (flag == true)
							{
								break;
							}
						}
						break;
					case 1:
						for (j = 0; j < 10; j++)
						{
							for (int k = 0; k < 10; k++)
							{
								if (bg.arr[j][k].type == 0 && j + 2 < 10 && k - 2 >= 0 && bg.arr[j + 1][k].type == 0
									&& bg.arr[j + 2][k].type == 0 && bg.arr[j + 2][k - 1].type == 0 && bg.arr[j + 2][k - 2].type == 0)
								{
									flag = true;
								}
							}
							if (flag == true)
							{
								break;
							}
						}
						break;
					case 2:
						for (j = 0; j < 10; j++)
						{
							for (int k = 0; k < 10; k++)
							{
								if (j + 2 < 10 && k + 2 < 10 && bg.arr[j + 1][k].type == 0 && bg.arr[j][k + 1].type == 0
									&& bg.arr[j + 2][k].type == 0 && bg.arr[j][k + 2].type == 0)
								{
									flag = true;
								}
							}
							if (flag == true)
							{
								break;
							}
						}
						break;
					case 3:
						for (j = 0; j < 10; j++)
						{
							for (int k = 0; k < 10; k++)
							{
								if (j + 2 < 10 && k + 2 < 10 && bg.arr[j + 1][k].type == 0 && bg.arr[j][k].type == 0 && bg.arr[j + 2][k].type == 0
									&& bg.arr[j + 2][k + 1].type == 0 && bg.arr[j + 2][k + 2].type == 0)
								{
									flag = true;
									break;
								}
							}
							if (flag == true)
							{
								break;
							}
						}
						break;
					}
				}
				break;
			case TYPE_3:
				int j = 0;
				switch (bs[i].model)
				{
				case 0:
					for (j = 0; j < 8; j++)
					{
						for (int k = 0; k < 8; k++)
						{
							if (bg.arr[j][k].type == 0 && bg.arr[j + 1][k].type == 0 && bg.arr[j+2][k].type == 0 
								&& bg.arr[j][k+1].type == 0 && bg.arr[j + 1][k + 1].type == 0 && bg.arr[j + 2][k+1].type == 0
								&& bg.arr[j][k + 2].type == 0 && bg.arr[j + 1][k + 2].type == 0 && bg.arr[j + 2][k+2].type == 0)
							{
								flag = true;
								break;
							}
						}
						if (flag == true)
						{
							break;
						}
					}
					break;
				case 1:
					for (j = 0; j < 9; j++)
					{
						for (int k = 0; k < 9; k++)
						{
							if (bg.arr[j][k].type == 0 && bg.arr[j + 1][k].type == 0 && bg.arr[j][k + 1].type == 0 && bg.arr[j + 1][k + 1].type == 0)
							{
								flag = true;
								break;
							}
						}
						if (flag == true)
						{
							break;
						}
					}
					break;
				}
				break;
			}
		}
		else
		{
			num++;
		}
	}
	if (num == 3)
	{
		flag = true;
	}
	return flag;
}

void clickBigSquare(int x, int y){

	clickNum = 0;
	for (int i = 0; i < 3; i++)
	{
		if (bs[i].isInBigSquare(x,y))
		{
			clickNum = i + 1;
		}
	}
}

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_MY1010, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow)) 
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_MY1010);

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage is only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); 

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_MY1010);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HANDLE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX& ~WS_THICKFRAME,		//设置无法最大化，更改长宽
      CW_USEDEFAULT, 0, 480, 640, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   GetClientRect(hWnd, &rt);

   hdc = GetDC(hWnd);
   mdc = CreateCompatibleDC(NULL);
   imghdc = CreateCompatibleDC(hdc);

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   bitmap_logo = LoadBitmap(hInst, MAKEINTRESOURCE(IMG_LOGO));
   bitmap_cup = LoadBitmap(hInst, MAKEINTRESOURCE(IMG_CUP));
   bitmap_score = LoadBitmap(hInst, MAKEINTRESOURCE(IMG_SCORE));
   bitmap_restart = LoadBitmap(hInst, MAKEINTRESOURCE(IMG_RESTART));
   bitmap_exit = LoadBitmap(hInst, MAKEINTRESOURCE(IMG_EXIT));

   //GetObject(bitmap_logo, sizeof(BITMAP), &bitmap1);
   //SelectObject(mdc, imghdc);

   bitmap = CreateCompatibleBitmap(hdc, rt.right, rt.bottom);//内存中撑出整个页面
   SelectObject(mdc, bitmap);

   score_font = CreateFont(30, 0, 0, 0, FW_NORMAL, 0, 0, 0, GB2312_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
	   DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "方正舒体");
   hbrush_bg = CreateSolidBrush(RGB(255, 255, 255));
   hbrush_score = CreateSolidBrush(RGB(90, 190, 226));
   hpen_bord = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, unsigned, WORD, LONG)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	
	int wmId, wmEvent;
	POINT mouse_point;
	sprintf(num, "%d", score);

	switch (message) 
	{
		case WM_CREATE:
			endgame = false;
			break;
		case WM_LBUTTONDOWN:
			mouse_point_last.x = LOWORD(lParam);
			mouse_point_last.y = HIWORD(lParam);
			if (endgame)
			{
				if (mouse_point_last.x > 132&&mouse_point_last.x<232&&mouse_point_last.y>260&&mouse_point_last.y<360)	//退出
				{
					PostQuitMessage(0);
				}else if(mouse_point_last.x > 233&&mouse_point_last.x<333&&mouse_point_last.y>260&&mouse_point_last.y<360)
				{
					endgame = false;
					begin_game = 0; 
					bg.clear();
					for (int i = 0; i < 3; i++)
					{
						bs[i].clear();
					}
					SetTextColor(mdc, RGB(90, 190, 226));
					SetBkColor(mdc, RGB(255, 255, 255));
					
				}
			}
			else
			{
				clickBigSquare(mouse_point_last.x, mouse_point_last.y);
			}
			break;
		case WM_MOUSEMOVE:
			if (clickNum)
			{
				mouse_point.x = LOWORD(lParam);
				mouse_point.y = HIWORD(lParam);
				bs[clickNum-1].moveSquare(mouse_point.x - mouse_point_last.x, mouse_point.y - mouse_point_last.y);
				square_rect.top = bs[clickNum-1].pos.y - 1;
				square_rect.left = bs[clickNum-1].pos.x - 1;
				square_rect.right = square_rect.top + (15 * 31) + 2;
				square_rect.bottom = square_rect.top + (15 * 31) + 2;

				mouse_point_last = mouse_point;
				InvalidateRect(hWnd, &square_rect, 0);

				square_rect.top = 0;
				square_rect.left = 0;
				square_rect.right = 0;
				square_rect.bottom = 0;
			}
			break;
		case WM_LBUTTONUP:
			if (clickNum!=0)
			{
				if (bs[clickNum-1].beSet(bg))
				{
					score += bs[clickNum - 1].blockNum;
					bs[clickNum - 1].clear();
				}
				bs[clickNum - 1].reset();
			}
			clickNum = 0;
			bg.liquidate(score);
			if (!finished(bg, bs))
			{
				endgame = true;
			}
			InvalidateRect(hWnd, NULL, 0);
			break;
		case WM_COMMAND:
			wmId    = LOWORD(wParam); 
			wmEvent = HIWORD(wParam); 
			// Parse the menu selections:
			switch (wmId)
			{
				case IDM_ABOUT:
				   DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
				   break;
				case IDM_EXIT:
				   DestroyWindow(hWnd);
				   break;
				default:
				   return DefWindowProc(hWnd, message, wParam, lParam);
			}
			break;
		case WM_PAINT:
			SelectObject(mdc, hpen_bord);
			SelectObject(mdc, hbrush_bg);
			Rectangle(mdc, rt.left, rt.top, rt.right, rt.bottom);
			if (!endgame)
			{
				SelectObject(imghdc, bitmap_logo);
				BitBlt(mdc, (rt.right - 77) / 2, 5, 77, 24, imghdc, 0, 0, SRCCOPY);//绘制logo

				SelectObject(imghdc, bitmap_cup);
				BitBlt(mdc, rt.right / 2 - 36, 50, 36, 29, imghdc, 0, 0, SRCCOPY);//绘制奖杯

				SetTextColor(mdc, RGB(90, 190, 226));
				SelectObject(mdc, score_font);
				TextOut(mdc, rt.right / 2 + 10, 47, num, strlen(num));
				if (begin_game == 0)
				{
					init(mdc);
				}
				else
				{
					bg.drawBack(mdc);
					for (int i = 0; i < 3; i++)
					{
						bs[i].drawSquare(mdc);
					}
				}
				if (bs[0].type == TYPE_NULL && bs[1].type == TYPE_NULL && bs[2].type == TYPE_NULL)
				{
					resetBigSquare(mdc);
					if (!finished(bg, bs))
					{
						endgame = true;
					}
				}
			}
			else
			{
				SelectObject(mdc, hbrush_score);
				RoundRect(mdc, (rt.right - 201) / 2, (rt.bottom - 80) / 2-80, (rt.right + 201) / 2, (rt.bottom + 80) / 2-80, 20, 20);

				SelectObject(imghdc, bitmap_score);
				BitBlt(mdc, (rt.right - 38) / 2, (rt.bottom - 34) / 2 - 90, 38, 34, imghdc, 0, 0, SRCCOPY);	//分数图

				SelectObject(imghdc, bitmap_restart);
				BitBlt(mdc, (rt.right) / 2 + 1, (rt.bottom) / 2 - 40, 100, 100, imghdc, 0, 0, SRCCOPY);		//restart图
				SelectObject(imghdc, bitmap_exit);
				BitBlt(mdc, (rt.right) / 2 - 100, (rt.bottom) / 2 - 40, 100, 100, imghdc, 0, 0, SRCCOPY);	//退出图

				SetTextColor(mdc, RGB(255, 255, 255));
				SetBkColor(mdc, RGB(90, 190, 226));
				SelectObject(mdc, score_font);
				TextOut(mdc, rt.right / 2-(strlen(num)*17)/2, rt.bottom/2-75, num, strlen(num));
			}

			
			BitBlt(hdc, 0, 0, rt.right, rt.bottom, mdc, rt.left, rt.top, SRCCOPY);
			break;
		case WM_DESTROY:
			DeleteObject(hbrush_score);
			DeleteObject(hpen_bord);
			DeleteObject(score_font);
			DeleteObject(bitmap_logo);
			DeleteObject(bitmap_cup);
			DeleteObject(hbrush_bg);
			DeleteObject(bitmap);
			DeleteDC(mdc);
			ReleaseDC(hWnd, hdc);
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
   return 0;
}

// Mesage handler for about box.
LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_INITDIALOG:
				return TRUE;

		case WM_COMMAND:
			if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) 
			{
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}
			break;
	}
    return FALSE;
}
