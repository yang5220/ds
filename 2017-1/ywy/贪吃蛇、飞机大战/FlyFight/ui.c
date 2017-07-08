#include <Windows.h>
#include "auto_fly.h"
#include "LinkList.h"
#include "ui.h"

#pragma comment (lib, "Winmm.lib")

#define CLASS_NAME_BK		"bk_class"
#define CLASS_NAME_FIGHT	"fight_class"
#define CLASS_NAME_FLYS		"flys_class"

#define BITMAP_FILE_BK		"cloud.bmp"

#define TIMER_ID			12340                                                           
#define TRANS_BK_COLOR		RGB(200��200��200)
#define FIGHTER_HEIGHT		50
#define FIGHTER_WIDTH		50


#define FIGHTER_MOVE_STEP	8		// �ɻ��ڷ�����������£�ÿ���ƶ������أ�

#define GAME_HEIGHT 1000
#define GAME_WIDTH	500



HINSTANCE hinst;

HWND hwndFighter;
HWND hwndAutoflys;
HWND hwndBackground;

HBITMAP hbmpFighter;
HBITMAP hbmpBackground;

#define COLOR_BULLET	RGB(256,150,132)//255
#define COLOR_ENEMY		RGB(187,45,150)//255
#define COLOR_BOMB		RGB(150, 78, 98)//255

POINT ptFighter;
DWORD dwTimerElapse = 40;

/// ��������

LONG FighterTimer(HWND hwnd);

LONG CALLBACK BackGroundWindowProc(
	HWND hwnd, //
	UINT msg, // ��Ϣ
	WPARAM wParam, // ��Ϣ��������ͬ����Ϣ�в�ͬ�����壬���MSDN��ÿ����Ϣ���ĵ�
	LPARAM lParam) // ��Ϣ��������ͬ����Ϣ�в�ͬ�����壬���MSDN��ÿ����Ϣ���ĵ�
{
	RECT rectNew;
	// ע�⣬��switch-case, ÿ��������������ã�ֻ�����뵽һ��case�С�
	switch (msg)
	{
		// �����ڱ�����ʱ���յ��ĵ�һ����Ϣ����WM_CREATE��
		// һ���յ������Ϣ��������У�������������һЩ��ʼ���Ĺ���
	case WM_CREATE:
		BackgroundCreate(hwnd);
		SetFocus(hwnd);
		PostMessage(hwnd, WM_LBUTTONDOWN, 0, (DWORD)0x0050050);
		PostMessage(hwnd, WM_LBUTTONUP, 0, (DWORD)0x0050050);

		break;

		// ��ϵͳ��Ϊ�����ϵ�GDI����Ӧ�ñ��ػ�ʱ�����򴰿ڷ���һ��WM_PAINT��Ϣ��
		// ��ȻӦ�ó���Ҳ����ͨ������ UpateWindow�������򴰿ڷ���һ��WM_PAINT��Ϣ��
		// ����ʹ��GDI�ڴ����ϻ���ͼ�εĳ��� �����롱 д�����
		// ���������WM_PAINT��Ϣ�Ĵ�������л���GDIͼ�Σ���ô�ڴ���ˢ��ʱ�ͻᱻ�±�Ĩ���͸���
	case WM_PAINT:
		BackgroundPaint(hwnd);
		break;

	case WM_MOVING:

		BackgroundResizeAndMove(hwnd, (LPRECT)lParam);
		break;

	case WM_KILLFOCUS:
		KillTimer(hwndFighter, TIMER_ID);
		break;

	case WM_SETFOCUS:
		SetTimer(hwndFighter, TIMER_ID, dwTimerElapse, NULL);
		break;

	case WM_SIZE:
		GetWindowRect(hwnd, &rectNew);
		BackgroundResizeAndMove(hwnd, &rectNew);
		break;

	case WM_KEYDOWN:
		OnKeydown(hwnd, (UINT)wParam);
		break;

	case WM_LBUTTONDOWN:
		break;

	case WM_TIMER:
		break;

	case WM_DESTROY:
		ExitProcess(0);
		break;

	default:
		break;
	}
	return DefWindowProc(hwnd,
		msg,
		wParam,
		lParam);
}



BOOL BackGroundWindwowRegister(HINSTANCE hinstance)
{
	WNDCLASS wc;
	// ���ھ����hwnd�����������ڵľ�������������ֻ�õ���һ�����ڡ�

	// Fill in the window class structure with parameters 
	// that describe the main window. 

	// ���������ʽ���������õ���ʽ��ʾ�����ڴ�С�仯����Ҫ�ػ�
	wc.style = CS_HREDRAW | CS_VREDRAW;
	// һ������ָ�룬�������������������Ϣ�� ��� MainWndProc������ע�͡�
	wc.lpfnWndProc = BackGroundWindowProc;
	// no extra class memory 
	wc.cbClsExtra = 0;
	// no extra window memory
	wc.cbWndExtra = 0;
	// handle to instance 
	wc.hInstance = hinstance;
	// hIcon��Ա����ָ�����ڵ�ͼ��
	// ����ֱ��ʹ��LoadIcon����������һ��ϵͳԤ�����ͼ�꣬������Ա��Ҳ�����Լ�����ͼ�ꡣ
	wc.hIcon = NULL;
	// Cursor������꣬�������趨����������ʽ��
	// ֱ��ʹ��LoadCursor API����������һ��ϵͳԤ����Ĺ����ʽ������IDC_CROSS,IDC_HAND����ʽ 
	wc.hCursor = LoadCursor(NULL,
		IDC_CROSS);
	// GetStockObject�Ĺ����Ǽ���һ��ϵͳԤ���壨��ջ�У���GDI����
	// ������ص���һ����ɫ�Ļ�ˢ���йػ�ˢ��GDI�������GDI˵����
	wc.hbrBackground = (HBRUSH)GetStockObject(
		WHITE_BRUSH);
	// ���ڵĲ˵�����Դ����
	wc.lpszMenuName = NULL;
	// ����������һ�����֣��ڴ�������ʱ��Ҫ������֡�
	wc.lpszClassName = CLASS_NAME_BK;

	// Register the window class. 

	if (!RegisterClass(&wc))
	{
		// ����ע��ʧ�ܣ���Ϣ����ʾ�����˳���
		MessageBox(NULL, "��������classʧ��", "����", MB_ICONERROR | MB_OK);
		return FALSE;
	}
	// ����ע��ɹ����������С�
	return TRUE;
}

HWND BackgroundWindowCreate(HINSTANCE hinstance)
{

	// Create the main window. 
	HWND hwnd;
	hwnd = CreateWindowEx(
		WS_EX_APPWINDOW | WS_EX_LAYERED | WS_EX_TOPMOST,
		CLASS_NAME_BK,			// �����������������Ѿ�ע���˵Ĵ�����
		"",		// title-bar string 
		WS_POPUP,	// ���ڵ�style�������ʾΪtop-level window 
		CW_USEDEFAULT,			// ����ˮƽλ��default horizontal POINT 
		CW_USEDEFAULT,			// ���ڴ�ֱλ��default vertical POINT 
		CW_USEDEFAULT,			// ���ڿ�� default width 
		CW_USEDEFAULT,			// ���ڸ߶� default height 
		(HWND)NULL,				// �����ھ�� no owner window 
		(HMENU)NULL,			// ���ڲ˵��ľ�� use class menu 
		hinstance,				// Ӧ�ó���ʵ����� handle to application instance 
		(LPVOID)NULL);			// ָ�򸽼����ݵ�ָ�� no window-creation data 

	if (!hwnd)
	{
		// ���ڴ���ʧ�ܣ���Ϣ����ʾ�����˳���
		MessageBox(NULL, "��������ʧ��", "����", MB_ICONERROR | MB_OK);
		return NULL;
	}

	if (!SetLayeredWindowAttributes(
		hwnd, TRANS_BK_COLOR,
		150, LWA_ALPHA))
	{
		DWORD dwError = GetLastError();
	}

	// ���ڴ����ɹ����������С�

	// ��ʾ���ڣ�WinMain������nCmdShow���������﷢�����ã�һ�㶼����ΪSW_SHOW
	ShowWindow(hwnd, SW_SHOW);

	// ˢ�´��ڣ��򴰿ڷ���һ��WM_PAINT��Ϣ��ʹ�ô��ڽ����ػ档
	UpdateWindow(hwnd);
	return hwnd;

}

LONG FightWindowPaint(HWND hwnd)
{
	HDC hdc, hdcMem, hdcBitmapSrc;
	HBITMAP hBitmap;
	//PAINTSTRUCT ps;
	//RECT rect;
	int num, i;
	LPAUTO_FLY auto_fly;
	BITMAP bmp;

	RECT rect;
	HFONT hFont;

	HPEN oldPen, hpenBullet;
	HBRUSH oldBursh, hbrBullet, hbrEnemy, bhrBomb;

	CHAR debug_info[100];

	GetClientRect(hwnd, &rect);

	hdc = GetDC(hwnd);

	// ע�� CreateCompatibleDC �е���һ�λ���
	// �����ȸ�DCѡ��λͼ��
	// Before an application can use a memory DC for drawing operations, 
	// it must select a bitmap of the correct width and height into the DC. 
	// To select a bitmap into a DC, use the CreateCompatibleBitmap function
	// ע�⣺
	// http://msdn.microsoft.com/en-us/library/windows/desktop/dd183488(v=vs.85).aspx
	hdcMem = CreateCompatibleDC(hdc);
	hBitmap = CreateCompatibleBitmap(hdc, // ������hdcMem��������ɺڰ�2ɫλͼ
		rect.right - rect.left, rect.bottom - rect.top);
	
	SelectObject(hdcMem, hBitmap);

	hdcBitmapSrc = CreateCompatibleDC(hdc);
	SelectObject(hdcBitmapSrc, hbmpFighter);

	GetObject(hbmpFighter, sizeof(BITMAP), &bmp);

	/*******************************************************************************
	* #############  ������  ################
	*
	*******************************************************************************/
	FillRect(hdcMem, &rect, (HBRUSH)GetStockObject(WHITE_BRUSH));

	// ���ɻ�

	StretchBlt(hdcMem,
		ptFighter.x - FIGHTER_WIDTH / 2, ptFighter.y,
		FIGHTER_WIDTH, FIGHTER_HEIGHT,
		hdcBitmapSrc,
		0, 0, bmp.bmWidth, bmp.bmHeight,
		SRCCOPY);


	// ���ӵ��͵л�
	hbrBullet = CreateSolidBrush(COLOR_BULLET);
	hbrEnemy = CreateSolidBrush(COLOR_ENEMY);
	bhrBomb = CreateSolidBrush(COLOR_BOMB);
	hpenBullet = CreatePen(PS_NULL, 0, 0);
	oldBursh = SelectObject(hdcMem, hbrBullet);
	oldPen = SelectObject(hdcMem, hpenBullet);
	num = get_flys_num();

	// ������һ���������
	hFont = CreateFont(20, 0, 0, 0, FW_DONTCARE, 0, FALSE, 0, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Consolas"));


	wsprintf(debug_info, "DEBUG_INFO: objects count: %d\n �÷֣�0x%p", num, get_sorce());
	SelectObject(hdcMem, hFont);
	SetTextColor(hdcMem, RGB(200, 0, 0));///255
	TextOut(hdcMem, 10, 10, debug_info, strlen(debug_info));

	for (i = 0; i < num; i++)
	{
		auto_fly = get_fly_at(i);
		if (auto_fly->type == FLY_TYPE_BULLET)
		{
			SelectObject(hdcMem, hbrBullet);
			Ellipse(hdcMem,
				get_fly_x(auto_fly) - 4,
				get_fly_y(auto_fly) - 6,
				get_fly_x(auto_fly) + 4,
				get_fly_y(auto_fly) + 6);
		}
		else if (auto_fly->type == FLY_TYPE_ENEMY)
		{

			if (auto_fly->state == FLY_HIT)
			{
				SelectObject(hdcMem, bhrBomb);
				Ellipse(hdcMem,
					get_fly_x(auto_fly) - 25,
					get_fly_y(auto_fly) - 25,
					get_fly_x(auto_fly) + 25,
					get_fly_y(auto_fly) + 25);
			}
			else
			{
				SelectObject(hdcMem, hbrEnemy);
				Ellipse(hdcMem,
					get_fly_x(auto_fly) - 20,
					get_fly_y(auto_fly) - 10,
					get_fly_x(auto_fly) + 20,
					get_fly_y(auto_fly) + 10);
			}
		}

	}

	oldBursh = SelectObject(hdcMem, oldBursh);
	oldPen = SelectObject(hdcMem, oldPen);


	// ������DC
	BitBlt(hdc,
		rect.left, rect.top,
		rect.right - rect.left, rect.bottom - rect.top,
		hdcMem,
		0, 0,
		SRCCOPY);

	DeleteObject(hpenBullet);
	DeleteObject(hbrBullet);
	DeleteObject(hbrEnemy); 
	DeleteObject(bhrBomb);
	DeleteObject(hFont);

	DeleteObject(hBitmap);
	DeleteDC(hdcBitmapSrc);
	DeleteDC(hdcMem);
	ReleaseDC(hwnd, hdc);
	//DeleteDC(hdc);
	return 0;
}

LONG CALLBACK FightWindowProc(
	HWND hwnd, //
	UINT msg, // ��Ϣ
	WPARAM wParam, // ��Ϣ��������ͬ����Ϣ�в�ͬ�����壬���MSDN��ÿ����Ϣ���ĵ�
	LPARAM lParam) // ��Ϣ��������ͬ����Ϣ�в�ͬ�����壬���MSDN��ÿ����Ϣ���ĵ�
{

	// ע�⣬��switch-case, ÿ��������������ã�ֻ�����뵽һ��case�С�
	switch (msg)
	{
		// �����ڱ�����ʱ���յ��ĵ�һ����Ϣ����WM_CREATE��
		// һ���յ������Ϣ��������У�������������һЩ��ʼ���Ĺ���
	case WM_CREATE:
		FighterCreate(hwnd);

	case WM_PAINT:
		FightWindowPaint(hwnd);
		break;

	case WM_KEYDOWN:
		break;

	case WM_LBUTTONDOWN:
		break;

	case WM_TIMER:
		FighterTimer(hwnd);
		FightWindowPaint(hwnd);
		break;

	case WM_DESTROY:
		ExitProcess(0);
		break;

	default:
		break;
	}
	return DefWindowProc(hwnd,
		msg,
		wParam,
		lParam);
}


HWND FightWindowCreate(HINSTANCE hinstance)
{
	HWND hwnd;
	hwnd = CreateWindowEx(
		WS_EX_LAYERED | WS_EX_TOPMOST | WS_EX_NOACTIVATE,
		CLASS_NAME_FIGHT,			// �����������������Ѿ�ע���˵Ĵ�����
		"",			// title-bar string 
		WS_POPUP,	// ���ڵ�style�������ʾΪtop-level window 
		CW_USEDEFAULT,			// ����ˮƽλ��default horizontal POINT 
		CW_USEDEFAULT,			// ���ڴ�ֱλ��default vertical POINT 
		CW_USEDEFAULT,			// ���ڿ�� default width 
		CW_USEDEFAULT,			// ���ڸ߶� default height 
		(HWND)NULL,				// �����ھ�� no owner window 
		(HMENU)NULL,			// ���ڲ˵��ľ�� use class menu 
		hinstance,				// Ӧ�ó���ʵ����� handle to application instance 
		(LPVOID)NULL);			// ָ�򸽼����ݵ�ָ�� no window-creation data 
	if (!hwnd)
	{
		GetLastError();
		// ���ڴ���ʧ�ܣ���Ϣ����ʾ�����˳���
		MessageBox(NULL, "��������ʧ��", "����", MB_ICONERROR | MB_OK);
		return NULL;
	}


	if (!SetLayeredWindowAttributes(
		hwnd, TRANS_BK_COLOR,
		255, LWA_COLORKEY | LWA_ALPHA))
	{
		DWORD dwError = GetLastError();
	}

	// ���ڴ����ɹ����������С�
	// ��ʾ���ڣ�WinMain������nCmdShow���������﷢�����ã�һ�㶼����ΪSW_SHOW
	ShowWindow(hwnd, SW_SHOW);
	// ˢ�´��ڣ��򴰿ڷ���һ��WM_PAINT��Ϣ��ʹ�ô��ڽ����ػ档
	UpdateWindow(hwnd);
	return hwnd;
}

BOOL FightWindowRegister(HINSTANCE hinstance)
{
	WNDCLASS wc;
	// ���ھ����hwnd�����������ڵľ�������������ֻ�õ���һ�����ڡ�

	// Fill in the window class structure with parameters 
	// that describe the main window. 
	// ���������ʽ���������õ���ʽ��ʾ�����ڴ�С�仯����Ҫ�ػ�
	wc.style = CS_HREDRAW | CS_VREDRAW;
	// һ������ָ�룬�������������������Ϣ�� ��� MainWndProc������ע�͡�
	wc.lpfnWndProc = FightWindowProc;
	// no extra class memory 
	wc.cbClsExtra = 0;
	// no extra window memory
	wc.cbWndExtra = 0;
	// handle to instance 
	wc.hInstance = hinstance;
	// hIcon��Ա����ָ�����ڵ�ͼ��
	// ����ֱ��ʹ��LoadIcon����������һ��ϵͳԤ�����ͼ�꣬������Ա��Ҳ�����Լ�����ͼ�ꡣ
	wc.hIcon = NULL;
	// Cursor������꣬�������趨����������ʽ��
	// ֱ��ʹ��LoadCursor API����������һ��ϵͳԤ����Ĺ����ʽ������IDC_CROSS,IDC_HAND����ʽ 
	wc.hCursor = LoadCursor(NULL, IDC_CROSS);
	// GetStockObject�Ĺ����Ǽ���һ��ϵͳԤ���壨��ջ�У���GDI����
	// ������ص���һ����ɫ�Ļ�ˢ���йػ�ˢ��GDI�������GDI˵����
	wc.hbrBackground = (HBRUSH)CreateSolidBrush(TRANS_BK_COLOR);
	// ���ڵĲ˵�����Դ����
	wc.lpszMenuName = NULL;
	// ����������һ�����֣��ڴ�������ʱ��Ҫ������֡�
	wc.lpszClassName = CLASS_NAME_FIGHT;
	// Register the window class. 

	if (!RegisterClass(&wc))
	{
		// ����ע��ʧ�ܣ���Ϣ����ʾ�����˳���
		MessageBox(NULL, "��������classʧ��", "����", MB_ICONERROR | MB_OK);
		return FALSE;
	}
	return TRUE;
}


LONG AutoflysPaint(HWND hwnd)
{
	HDC hdc, hdcMem;
	//PAINTSTRUCT ps;
	//RECT rect;
	int num, i;
	LPAUTO_FLY auto_fly;

	RECT rect;

	GetClientRect(hwnd, &rect);

	hdc = GetDC(hwnd);

	// ע�� CreateCompatibleDC �е���һ�λ���
	// Before an application can use a memory DC for drawing operations, 
	// it must select a bitmap of the correct width and height into the DC. 
	// To select a bitmap into a DC, use the CreateCompatibleBitmap function
	// ע�⣺
	// http://msdn.microsoft.com/en-us/library/windows/desktop/dd183488(v=vs.85).aspx
	hdcMem = CreateCompatibleDC(hdc);


	/*******************************************************************************
	* #############  ������  ################
	*
	*******************************************************************************/
	FillRect(hdcMem, &rect, (HBRUSH)GetStockObject(BLACK_BRUSH));


	SelectObject(hdcMem, GetStockObject(BLACK_BRUSH));
	SelectObject(hdcMem, GetStockObject(BLACK_PEN));

	num = get_flys_num();


	for (i = 0; i < num; i++)
	{
		auto_fly = get_fly_at(i);
		if (auto_fly->state == FLY_HIT)
		{
			// todo ��ը��
		}
		else
		{
			Ellipse(hdcMem,
				50,
				50,
				500,
				500);
			//Ellipse(hdcMem,
			//	get_fly_x(auto_fly) - 10,
			//	get_fly_y(auto_fly) - 10,
			//	get_fly_x(auto_fly) + 10,
			//	get_fly_y(auto_fly) + 10);
		}

	}


	//SelectObject(hdcMem, hbmpBackground);

	//GetObject(hbmpBackground, sizeof(BITMAP), &bmp);

	BitBlt(hdc,
		rect.left, rect.top,
		rect.right - rect.left, rect.bottom - rect.top,
		hdcMem,
		0, 0,
		SRCCOPY);

	//DeleteObject(hdcMem);
	DeleteDC(hdcMem);
	ReleaseDC(hwnd, hdc);
	DeleteDC(hdc);
	return 0;
}

//LONG CALLBACK AutoflyWindowProc(HWND hwnd, UINT msg, WPARAM wParam,LPARAM lParam)
//{
//	//PAINTSTRUCT ps;
//	//RECT rect;
//	// ע�⣬��switch-case, ÿ��������������ã�ֻ�����뵽һ��case�С�
//	switch (msg)
//	{
//		// �����ڱ�����ʱ���յ��ĵ�һ����Ϣ����WM_CREATE��
//		// һ���յ������Ϣ��������У�������������һЩ��ʼ���Ĺ���
//	case WM_CREATE:
//		AutoflysCreate(hwnd);
//		break;
//
//		// ��ϵͳ��Ϊ�����ϵ�GDI����Ӧ�ñ��ػ�ʱ�����򴰿ڷ���һ��WM_PAINT��Ϣ��
//		// ��ȻӦ�ó���Ҳ����ͨ������ UpateWindow�������򴰿ڷ���һ��WM_PAINT��Ϣ��
//		// ����ʹ��GDI�ڴ����ϻ���ͼ�εĳ��� �����롱 д�����
//		// ���������WM_PAINT��Ϣ�Ĵ�������л���GDIͼ�Σ���ô�ڴ���ˢ��ʱ�ͻᱻ�±�Ĩ���͸���
//	case WM_PAINT:
//		AutoflysPaint(hwnd);
//		break;
//
//	case WM_KEYDOWN:
//		break;
//
//	case WM_LBUTTONDOWN:
//		break;
//
//	case WM_TIMER:
//		AutoFlysTimer(hwnd);
//		break;
//
//	case WM_DESTROY:
//		ExitProcess(0);
//		break;
//
//	default:
//		break;
//	}
//	return DefWindowProc(hwnd,
//		msg,
//		wParam,
//		lParam);
//}


HWND AutoflyWindowCreate(HINSTANCE hinstance)
{
	HWND hwnd;
	hwnd = CreateWindowEx(
		WS_EX_LAYERED | WS_EX_TOPMOST | WS_EX_NOACTIVATE,
		CLASS_NAME_FLYS,			// �����������������Ѿ�ע���˵Ĵ�����
		"",			// title-bar string 
		WS_POPUP,	// ���ڵ�style�������ʾΪtop-level window 
		CW_USEDEFAULT,			// ����ˮƽλ��default horizontal POINT 
		CW_USEDEFAULT,			// ���ڴ�ֱλ��default vertical POINT 
		CW_USEDEFAULT,			// ���ڿ�� default width 
		CW_USEDEFAULT,			// ���ڸ߶� default height 
		(HWND)NULL,				// �����ھ�� no owner window 
		(HMENU)NULL,			// ���ڲ˵��ľ�� use class menu 
		hinstance,				// Ӧ�ó���ʵ����� handle to application instance 
		(LPVOID)NULL);			// ָ�򸽼����ݵ�ָ�� no window-creation data 
	if (!hwnd)
	{
		GetLastError();
		// ���ڴ���ʧ�ܣ���Ϣ����ʾ�����˳���
		MessageBox(NULL, "��������ʧ��", "����", MB_ICONERROR | MB_OK);
		return NULL;
	}

	if (!SetLayeredWindowAttributes(
		hwnd, TRANS_BK_COLOR,
		255, LWA_COLORKEY | LWA_ALPHA))
	{
		DWORD dwError = GetLastError();
	}

	// ���ڴ����ɹ����������С�
	// ��ʾ���ڣ�WinMain������nCmdShow���������﷢�����ã�һ�㶼����ΪSW_SHOW
	ShowWindow(hwnd, SW_SHOW);
	// ˢ�´��ڣ��򴰿ڷ���һ��WM_PAINT��Ϣ��ʹ�ô��ڽ����ػ档
	UpdateWindow(hwnd);
	return hwnd;
}

//BOOL AutoflysWindowRegister(HINSTANCE hinstance)
//{
//	WNDCLASS wc;
//	// ���ھ����hwnd�����������ڵľ�������������ֻ�õ���һ�����ڡ�
//	HWND hwnd;
//
//	// Fill in the window class structure with parameters 
//	// that describe the main window. 
//	// ���������ʽ���������õ���ʽ��ʾ�����ڴ�С�仯����Ҫ�ػ�
//	wc.style = CS_HREDRAW | CS_VREDRAW;
//	// һ������ָ�룬�������������������Ϣ�� ��� MainWndProc������ע�͡�
//	wc.lpfnWndProc = AutoflyWindowProc;
//	// no extra class memory 
//	wc.cbClsExtra = 0;
//	// no extra window memory
//	wc.cbWndExtra = 0;
//	// handle to instance 
//	wc.hInstance = hinst;
//	// hIcon��Ա����ָ�����ڵ�ͼ��
//	// ����ֱ��ʹ��LoadIcon����������һ��ϵͳԤ�����ͼ�꣬������Ա��Ҳ�����Լ�����ͼ�ꡣ
//	wc.hIcon = NULL;
//	// Cursor������꣬�������趨����������ʽ��
//	// ֱ��ʹ��LoadCursor API����������һ��ϵͳԤ����Ĺ����ʽ������IDC_CROSS,IDC_HAND����ʽ 
//	wc.hCursor = LoadCursor(NULL,
//		IDC_CROSS);
//	// GetStockObject�Ĺ����Ǽ���һ��ϵͳԤ���壨��ջ�У���GDI����
//	// ������ص���һ����ɫ�Ļ�ˢ���йػ�ˢ��GDI�������GDI˵����
//	wc.hbrBackground = (HBRUSH)CreateSolidBrush(TRANS_BK_COLOR);
//	// ���ڵĲ˵�����Դ����
//	wc.lpszMenuName = NULL;
//	// ����������һ�����֣��ڴ�������ʱ��Ҫ������֡�
//	wc.lpszClassName = CLASS_NAME_FLYS;
//	// Register the window class. 
//
//	if (!RegisterClass(&wc))
//	{
//		// ����ע��ʧ�ܣ���Ϣ����ʾ�����˳���
//		MessageBox(NULL, "��������classʧ��", "����", MB_ICONERROR | MB_OK);
//		return FALSE;
//	}
//	return TRUE;
//}



/*******************************************************************************
* ##########   ��ں���WinMain    ##########
*
* WindowsӦ�ó������ں�����WinMain���������λ���������Ʊ�׼C���Ե�main����
*
*******************************************************************************/

int WINAPI WinMain(
	HINSTANCE hinstance, // ����ʵ��������ڳ������У����̴������ɲ���ϵͳ��Ӧ�ó�����
	HINSTANCE hPrevInstance, // �����̵ĳ���ʵ�����
	LPSTR lpCmdLine,  // �����в�������λ����������C����main��������argc��argv,����û�а��ո�����з�
	int nCmdShow)   // ����ָ�������Ƿ���Ҫ��ʾ�Ĳ�����
{
	BOOL fGotMessage;
	MSG msg;

	/*******************************************************************************
	* ##########   ���� API ����   ##########
	*
	* API�� Application Programming Interface����д������Ӧ�ó����̽ӿڡ�
	* API��Windows����ϵͳ�ṩ��Ӧ�ó�����õ�һϵ�й��ܵĽӿں���������Ӧ�ó�����ò���ϵͳ�ĵײ㹦��
	*
	* API������ʹ�÷�������C���ԵĿ⺯������printf��fopen��fread�ȡ�
	* ��VS������ʹ��C����C++���б���ǣ�ֻ��#include <windows.h>���ɵ��ô󲿷�Windows API������
	*
	* ������һ�˴�����ʹ�õ��� LoadIcon LoadCursor GetStockObject RegisterClass CreateWindow�Ⱥ�������API
	*
	* WindowsӦ�ó��򿪷������е���Ҫ��������ʹ��API��
	*
	*******************************************************************************/

	/*******************************************************************************
	* ##########   ������   ##########
	*
	* �ڴ�������֮ǰ��������Ҫע��һ�������࣬������������Ϊͬһ����Ĵ��ڡ�
	* һ����������Դ���������ڣ�����ͬһ������Ĵ��ھ�����ͬ����Ϣ�����������Ƶ���ʽ��
	*
	* �������C++�е���Ӣ�Ķ���class���������ǲ���ͬһ���
	* C++��ʹ��class�ؼ��ֶ��壬����������ʹ��RegisterClass API������Windowsϵͳע�ᡣ
	*
	* ����� WNDCLASS wc ��ע�ᴰ����� API����RegisterClass�Ĳ�������һ���ṹ�����ͣ�
	* �����洢һ��������ĸ�������
	*
	*******************************************************************************/




	if (BackGroundWindwowRegister(hinstance))
		hwndBackground = BackgroundWindowCreate(hinstance);
	else
		return 0;


	/*******************************************************************************
	* ##########   MSG���ͺ���Ϣ    ##########
	*
	* Windows����Ӧ�ó�����һ����Ϣ�����ĳ����ܡ�
	* Windows����Ӧ�ó��������Ժ������߳̾�һֱ����
	* "�ȴ���Ϣ--��ȡ��Ϣ--ЧӦ��Ϣ" ��ѭ��֮�У�ֱ�������˳���
	*
	* ��ν��Ϣ��Windowsϵͳ���е�һ��ϵͳ����ͻ��ƣ�
	* �ǲ���ϵͳ��ĳЩϵͳ״̬����ʱ�ӣ����û����������������������ϵͳ�жϽ��з�װ�Ժ�
	* ���Է��͵�Ӧ�ó��򣬲���Ӧ�ó�����д�����û�̬����
	*
	* "MSG"����������ʾ"��Ϣ"���������͡� ���ﶨ����һ��MSG���͵ı�����������Ϊmsg
	*
	*******************************************************************************/
	//SetFocus(hwndBackground);

	// ���½�����Ϣѭ������ȡ��Ϣ--������Ϣ--������Ϣ���ɴ��ڵ���Ϣ��������������Ϣ��
	while ((fGotMessage = GetMessage(&msg, (HWND)NULL, 0, 0)) != 0
		&& fGotMessage != -1)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}




LONG BackgroundCreate(HWND hwnd)
{

	if (FightWindowRegister(hinst))
		hwndFighter = FightWindowCreate(hinst);

	//if (AutoflysWindowRegister(hinst))
	//	hwndAutoflys = AutoflyWindowCreate(hinst);

	//BITMAP bmp;
	hbmpBackground = LoadImage(NULL, BITMAP_FILE_BK,
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	if (hbmpBackground == NULL)
	{
		MessageBox(hwnd, "bmp file not find", "ERROR!",
			MB_OK | MB_ICONERROR);
		ExitProcess(0);
	}

	MoveWindow(hwnd, 100, 20, MAX_X, MAX_Y, TRUE);

	ptFighter.x = MAX_X / 2;
	ptFighter.y = MAX_Y - FIGHTER_HEIGHT;

	SetFocus(hwnd);

	return 0;
}

//LONG AutoflysCreate(HWND hwnd)
//{
//
//	flys_init();
//	SetTimer(hwnd, TIMER_ID, dwTimerElapse, NULL);
//	return 0;
//}

LONG BackgroundResizeAndMove(HWND hwnd, LPRECT lpRect)
{

	SetWindowPos(hwndFighter, HWND_TOPMOST, lpRect->left, lpRect->top,
		lpRect->right - lpRect->left, lpRect->bottom - lpRect->top, SWP_SHOWWINDOW);

	//SetWindowPos(hwndFighter, HWND_TOPMOST,
	//	(lpRect->left + lpRect->right - FIGHTER_WIDTH) / 2,
	//	lpRect->bottom - FIGHTER_HEIGHT,
	//	FIGHTER_WIDTH,
	//	FIGHTER_HEIGHT,
	//	SWP_SHOWWINDOW);
	
	//SetFocus(hwndBackground);

	return 0;
}

LONG BackgroundPaint(HWND hwnd)
{
	HDC hdc, hdcMem;
	//PAINTSTRUCT ps;
	RECT rect;

	BITMAP bmp;

	hdc = GetDC(hwnd);
	GetClientRect(hwnd, &rect);
	// Create a memory device compatible with the above DC variable
	hdcMem = CreateCompatibleDC(hdc);
	
	SelectObject(hdcMem, hbmpBackground);
	
	GetObject(hbmpBackground, sizeof(BITMAP), &bmp);
	 
	StretchBlt(hdc,
		rect.left,	rect.top,
		rect.right - rect.left, rect.bottom - rect.top,
		hdcMem,
		0, 0, 
		bmp.bmWidth, bmp.bmHeight,
		SRCCOPY);

	DeleteObject(hdcMem);
	DeleteDC(hdcMem);
	ReleaseDC(hwnd, hdc);
	DeleteDC(hdc);
	return 0;
}

LONG FighterCreate(HWND hwnd)
{
	//BITMAP bmp;
	hbmpFighter = LoadImage(NULL, "fight.bmp",
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	if (hbmpFighter == NULL)
	{
		MessageBox(hwnd, "bmp file not find", "ERROR!",
			MB_OK | MB_ICONERROR);
		ExitProcess(0);
	}

	flys_init();
	SetTimer(hwnd, TIMER_ID, dwTimerElapse, NULL);



	return 0;

	//SetFocus(hwndBackground);

	//MoveWindow(hwnd, 100, 100, MAX_X, MAX_Y, TRUE);
}

LONG OnKeydown(HWND hwnd, UINT vk)
{
	UINT key = vk;

	// ��������ͷ����ͬʱ����һ����ª͵����ʵ�ַ�ʽ��
	switch (key)
	{
	case VK_LEFT:
	case VK_RIGHT:
	case VK_UP:
	case VK_DOWN:
	case 'S':
		if (HIWORD(GetKeyState('S')))
		{
			gen_bullet(ptFighter.x, ptFighter.y);
		//PlaySound("C:\\Windows\\Media\\ir_end.wav", NULL, SND_FILENAME);
		}
		if (HIWORD(GetKeyState(VK_DOWN)))
		{
			ptFighter.y += FIGHTER_MOVE_STEP;
			if (ptFighter.y > MAX_Y)
				ptFighter.y = MAX_Y;
		}
		else if (HIWORD(GetKeyState(VK_UP)))
		{
			ptFighter.y -= FIGHTER_MOVE_STEP;
			if (ptFighter.y < 0)
				ptFighter.y = 0;
		}
		else if (HIWORD(GetKeyState(VK_LEFT)))
		{
			ptFighter.x -= FIGHTER_MOVE_STEP;
			if (ptFighter.x < 0)
				ptFighter.x = 0;
		}
		else if (HIWORD(GetKeyState(VK_RIGHT)))
		{
			ptFighter.x += FIGHTER_MOVE_STEP;
			if (ptFighter.x > MAX_X)
				ptFighter.x = MAX_X;
		}
		FightWindowPaint(hwndFighter);
		break;
	default:
		// ����������Ӧ
		break;
	}
	return 0;
}

LONG FighterTimer(HWND hwnd)
{

	destory_fly_by_state();
	
	flys_move_step();

	if (rand() % 1000 < 100) // 2%�ĸ��ʣ���������л���
	{
		gen_enemy();
	}

	return 0;
}
