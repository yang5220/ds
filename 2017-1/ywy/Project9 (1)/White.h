#pragma once
#pragma once
#include<Windows.h>
#pragma comment(lib,"winmm.lib")
#define ROW         4
#define COL         5
#define Click_B     0
#define Click_W     1
#define Click_Error 2
#define Score       21
typedef struct _GAME_COORD
{
	int x;
	int y;
}GAME_COORD, *PGAME_COORD;


void AddScore();
int GetScore();
void SetBoundary(int x, int y);
PGAME_COORD GetBoundary();

int* GetK();
POINT GetPosit(int, int);

void CreateKuai();//初始化黑白块位置

void ReInit();//点击一次后更新黑白块位置

			 
void OnKeyDown(DWORD vk, HWND hwnd);//每按下一个键并判断后
//int BlcOrWht(int);//返回按键信息


				  //计时器到时后，根据按键信息进行下一步处理
void OnTimer(HWND hwnd);


void CreateGame(HWND hwnd,
	DWORD dwInitTimerElapse,
	int boundary_x, int boundary_y);


