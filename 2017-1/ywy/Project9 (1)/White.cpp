#include<Windows.h>
#include"White.h"

int K[COL][ROW];

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

int*GetK()
{
	return *K;
}
POINT GetPosit(int i,int j)
{
	POINT P;
	P.x = j;
	P.y = i;
	return P;
}

int score = 0;
int GetScore()
{
	return score;
}

void AddScore()
{
	score += 3;
}


void CreateKuai()
{
	int i, j, r;
	for (i = 0; i < COL; i++)
	{
		r = rand() % ROW;
		for (j = 0; j < ROW; j++)
		{
			if (r == j)
				K[i][j] = 1;//�׿�
			else
				K[i][j] = 0;//�ڿ�
		}
	}
	
}
void ReInit()
{
	int i, j, r;
	////��һ�ű���һ�Ÿ���
	for (i = COL - 1; i > 0; i--)
	{
		for (j = 0; j < ROW; j++)
		{
			K[i][j] = K[i - 1][j];
		}
	}
	r = rand() % ROW;
	for (j = 0; j < ROW; j++)
	{
		if (j == r)
		{
			K[0][j] = 1;
		}
		else
			K[0][j] = 0;
	}
}
	

