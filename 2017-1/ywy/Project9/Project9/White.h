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

void CreateKuai();//��ʼ���ڰ׿�λ��

void ReInit();//���һ�κ���ºڰ׿�λ��

			  //�жϵ����λ����׿��Ƿ��غ�
bool Equal(GAME_COORD t1, GAME_COORD t2);

int OnKeyDown(DWORD vk);//ÿ����һ�������жϺ󣬷��ذ�����Ϣ
int BlcOrWht(int);//���ذ�����Ϣ


				  //��ʱ����ʱ�󣬸��ݰ�����Ϣ������һ������
void OnTimer(HWND hwnd, DWORD vk);


void CreateGame(HWND hwnd,
	DWORD dwInitTimerElapse,
	int boundary_x, int boundary_y);


