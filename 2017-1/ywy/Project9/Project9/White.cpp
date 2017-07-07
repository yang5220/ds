#include<Windows.h>
#include"White.h"
int score = 0;
GAME_COORD K[5][4];//保存黑白块的坐标
GAME_COORD W[5];//保存白块的坐标
GAME_COORD boundary;

void SetBoundary(int x, int y)
{
	boundary.x = x;
	boundary.y = y;
}
PGAME_COORD GetBoundary()
{
	return &boundary;
}
PGAME_COORD GetW()
{
	return W;
}
PGAME_COORD GetK()
{
	return *K;
}
void AddScore()
{
	score += 3;
}
int GetScore()
{
	return score;
}

void CreateKuai()
{
	int i, j, r;
	for (i = 0; i < COL; i++)
	{
		r = rand() % ROW;
		for (j = 0; j<ROW; j++)
		{
			K[i][j].x = i;
			K[i][j].y = j;
			if (r == j)
			{
				W[i].x = i;
				W[i].y = j;
			}
		}
	}
}
void ReInit()
{
	int i, j, r, l;
	//下一排被上一排覆盖
	for (i = COL - 1; i > 0; i--)
	{
		for (j = 0; j < ROW; j++)
		{
			K[i][j].x = K[i - 1][j].x + 1;
			K[i][j].y = K[i - 1][j].y;
		}
	}
	for (i = COL - 1; i > 0; i--)
	{
		W[i].x = W[i - 1].x + 1;
		W[i].y = W[i - 1].y;
	}
	//重新生成最上排
	r = rand() % ROW;
	for (l = 0; l < ROW; l++)
	{
		K[0][l].x = 0;
		K[0][l].y = l;
		if (r == l)
		{
			W[0].x = 0;
			W[0].y = l;
		}
	}
}
bool Equal(GAME_COORD t1, GAME_COORD t2)
{
	if (t1.x == t2.x&&t2.x == t2.y)
		return true;
	return false;
}
int OnKeyDown(DWORD vk)//判断按下的块是否是白块，并将信息返回
{
	int flag = 0;
	switch (vk)
	{
	case'a':
		if (Equal(K[COL-1][0], W[COL-1]))
			flag = 1;
		break;
	case's':
		if (Equal(K[COL-1][1], W[COL-1]))
			flag = 1;
		break;
	case'd':
		if (Equal(K[COL-1][1], W[COL-1]))
			flag = 1;
		break;
	case'f':
		if (Equal(K[COL-1][1], W[COL-1]))
			flag = 1;
		break;
	default:
		flag = 2;
		break;
	}
	//return flag;
	return BlcOrWht(flag);
}
int BlcOrWht(int n)
{
	if (n == 1)
		return Click_W;
	else if (n == 0)
		return Click_B;
	else if (n == 2)
		return Click_Error;
}

//}
