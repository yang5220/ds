#pragma once
#pragma once
#include<Windows.h>
#pragma comment(lib,"winmm.lib")
#define ROW         5
#define COL         4
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
PGAME_COORD GetW();
PGAME_COORD GetK();

void CreateKuai();//初始化黑白块位置

void ReInit();//点击一次后更新黑白块位置

			  //判断点击的位置与白块是否重合
bool Equal(GAME_COORD t1, GAME_COORD t2);

int OnKeyDown(DWORD vk);//每按下一个键并判断后，返回按键信息
int BlcOrWht(int);//返回按键信息


				  //计时器到时后，根据按键信息进行下一步处理
void OnTimer(HWND hwnd, DWORD vk);


void CreateGame(HWND hwnd,
	DWORD dwInitTimerElapse,
	int boundary_x, int boundary_y);


