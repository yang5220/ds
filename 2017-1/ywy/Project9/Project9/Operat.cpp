#include<Windows.h>
#include"White.h"

#define TIMER_ID 12340
DWORD dwTimerElapse;

void OnTimer(HWND hwnd, DWORD vk)
{

	switch (OnKeyDown(vk))
	{
	case Click_B://点到黑块，游戏结束
		KillTimer(hwnd, TIMER_ID);
		MessageBox(0, "Game Over", "Game Over", 0);
		ExitProcess(0);
		break;
	case Click_W:
		AddScore();
		ReInit();
		if (GetScore() >= Score)//赢得游戏
		{
			KillTimer(hwnd, TIMER_ID);
			MessageBox(0, "You Win!", "You Win", 0);
			ExitProcess(0);
		}
		break;
	case Click_Error:
		KillTimer(hwnd, TIMER_ID);
		MessageBox(hwnd, "Error!!", "Error!1", MB_OK);
		ExitProcess(0);
		break;
	default:
		break;
	}
}
void CreateGame(HWND hwnd,
	DWORD dwInitTimerElapse,
	int boundary_x, int boundary_y)
{
	FILETIME ft;
	GetSystemTimeAsFileTime(&ft);
	srand(ft.dwLowDateTime);

	dwTimerElapse = dwInitTimerElapse;
	SetBoundary(boundary_x, boundary_y);
	CreateKuai();
	SetTimer(hwnd, TIMER_ID, dwTimerElapse, NULL);
}
