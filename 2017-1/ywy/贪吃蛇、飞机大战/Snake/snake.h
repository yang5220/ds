
#include <Windows.h>
#include "LinkList.h"

// �ߵ�״̬
#define SNAKE_MOVED			0
#define SNAKE_DEAD			1
#define SNAKE_COMPLETE		2
#define SNAKE_EATEN_FOOD	3
#define SNAKE_GROWUP		4
#define SNAKE_ERROR			5

// �ߵķ���
typedef enum _dirction
{
	SNAKE_UP,
	SNAKE_DOWN,
	SNAKE_LEFT,
	SNAKE_RIGHT,
}dirction;

// ��Ϸ����
typedef struct _GAME_COORD
{
	short x;
	short y;
}GAME_COORD, *PGAME_COORD;

// ��������

/// snake_and_food.c�еĽӿں���

// ���ñ߽�����
void SetBoundary(int x, int y);

// ��ñ߽�����
PGAME_COORD GetBoundary();

// �����µ�ʳ�
int CreateFood();

// ���ʳ������ꡣ
PGAME_COORD GetFood();

// ������
void CreateSnake(dirction dir, int head_x, int head_y, int init_len);

// �����ߣ��ͷ��ڴ���Դ��
void DistroySnake();

// �����ƶ�һ����
// �ƶ��Ժ�����Ե���ʳ���������
// ���������ǽ�����Լ������������������Ƿ�������״̬��
int SnakeMove();

// ������
int SnakeGorwup();

// ����ߵĳ���
int GetSnakeSize();

// ����ߵĵ�һ���ڵ������
PGAME_COORD GetSnakeHead();

// ����ߵ����һ���ڵ������
PGAME_COORD GetSnakeTail();

// ������Ż���ߵĽڵ�����꣬���ܳ����ߵĳ��ȣ����򷵻�NULL
PGAME_COORD GetSnakeAt(int n);

// �ı����ƶ��ķ���
void SetDirction(dirction dir);

// ��õ�ǰ�ߵķ���
dirction GetDirction();




/// game_opration.c �еĽӿں���

int GetScore();
int GetLevel();
void CreateGame(HWND hwnd,
	DWORD dwInitTimerElapse,
	unsigned int one_level_scores,
	DOUBLE level_speedup_ratio,
	int boundary_x, int boundary_y,
	int init_x, int init_y,
	int init_len,
	dirction init_dir);
void OnTimer(HWND hwnd);
void OnKeyDown(DWORD vk);