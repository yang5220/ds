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

void CreateKuai();//��ʼ���ڰ׿�λ��

void ReInit();//���һ�κ���ºڰ׿�λ��

			 
void OnKeyDown(DWORD vk, HWND hwnd);//ÿ����һ�������жϺ�
//int BlcOrWht(int);//���ذ�����Ϣ


				  //��ʱ����ʱ�󣬸��ݰ�����Ϣ������һ������
void OnTimer(HWND hwnd);


void CreateGame(HWND hwnd,
	DWORD dwInitTimerElapse,
	int boundary_x, int boundary_y);


