#include<Windows.h>
#include"White.h"

#define TIMER_ID 12340
DWORD dwTimerElapse;

void OnTimer(HWND hwnd)
{
	ReInit();
}
void OnKeyDown(DWORD vk, HWND hwnd)//判断按下的块是否是白块，并将信息返回
{
	int flag = 0;
	switch (vk)
	{
	case'A':
		if (*(GetK()+16)==1)
			flag = 1;
		break;
	case'S':
		if (*(GetK() + 17) == 1)
			flag = 1;
		break;
	case'D':
		if (*(GetK() + 18) == 1)
			flag = 1;
		break;
	case'F':
		if (*(GetK() + 19) == 1)
			flag = 1;
		break;
	default:
		flag = 2;
		break;
	}
	if (flag == 1)
	{
		AddScore();
		if (GetScore() >= Score)//赢得游戏
		{
			KillTimer(hwnd, TIMER_ID);
			MessageBox(0, "You Win!", "You Win", 0);
			ExitProcess(0);
		}
	}
	else if (flag == 0)
	{
		KillTimer(hwnd, TIMER_ID);
		MessageBox(0, "Game Over", "Game Over", 0);
		ExitProcess(0);
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
