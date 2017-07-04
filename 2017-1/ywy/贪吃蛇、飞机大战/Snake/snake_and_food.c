/********************************************************************************
* ##########  ̸̸��װ ##########
* ����װ���ǳ��򲻻��ҵ���һ����Ҫ���ܡ�
* ����Ҫд���ṹ���������Ķ�������ά���Ĵ��롣���÷�װ�ǱȽ��������յķ�����
* 
* ������ԣ�
* 
* 1���ȿ��Ǻ����������߼���״̬��Ҫ������������ʾ��
* �������̰������Ϸ������ʹ����Щ���ݾͿ��Ա�ʾȫ����Ϸ״̬��
* // ʳ��
* GAME_COORD food;
* // �ߣ�����
* PLIST snake_list;
* // ���ƶ�����
* dirction snake_dir;
* // ��Ϸ�߽磨�������£�����Ϊ0,0��
* GAME_COORD boundary;
* 
* 2��д��һϵ�нӿں�����������Щ���ݡ���ν�ӿں���������һ�¼���������
* (1) ��Щ���ݳ��˽ӿں������⣬�������붼����ֱ�ӷ��ʡ�
* (2) �����������붼ֻ��ͨ��������Щ�ӿں������ı�����״̬������Ҫֱ��ȥ�������ݡ�
* �籾�ļ������ɺ������Ƕ��������ݵĲ�����

* ����ʵ���ˣ������ϲ���룬������Ҫ֪�����ݵĲ����߼���Ҳ����Ҫ֪�����ݽṹ����ֻ��Ҫ���ú������ɡ�
* ���ϴδ�����ԣ��߼����˺ܶࡣ
* ͬ����������ݽṹ���ڲ��߼������޸ģ���ô���������ӿں�����ԭ�Ͳ��䣬
* �ϲ���벻�䣬��ֻ��Ҫ�޸Ľӿں������ڲ�ʵ�ֹ��̼��ɡ�
* 
* ��ͳ�֮Ϊ����װ�������߳�֮Ϊ �����ݵķ�װ�ͽӿڻ���
*
*******************************************************************************/



/************** ͷ�ļ� ****************/
#include "snake.h"

/************* ȫ�ֱ��� ****************/
// ʳ��
GAME_COORD food;
// �ߣ�����
PLIST snake_list;
// ���ƶ�����
dirction snake_dir;
// ��Ϸ�߽磨�������£�����Ϊ0,0��
GAME_COORD boundary;

/*********** �ڲ��������� **************/
/// �ж����������Ƿ���ȡ�
int CoordEqual(PGAME_COORD one, PGAME_COORD two);
/// �ж����Ƿ�����
int IsSnakeDead();

/**************��������****************/


// �ж��������� GAME_COORD �Ƿ��غ�
int CoordEqual(PGAME_COORD one, PGAME_COORD two)
{
	if (one->x == two->x && one->y == two->y)
		return 1;
	return 0;
}

// ���ñ߽�����
void SetBoundary(int x, int y)
{
	boundary.x = x;
	boundary.y = y;
}

// ��ñ߽�����
PGAME_COORD GetBoundary()
{
	return &boundary;
}

// �����µ�ʳ�
int CreateFood()
{
	PGAME_COORD posbody;
	int i;
	int size = ListSize(snake_list);

new_food:

	// �������ʳ������ꡣ
	food.x = rand() % boundary.x;
	food.y = rand() % boundary.y;

	// �ж��Ƿ�����ص��ˣ�������������ʳ�����ֱ꣬�����ص���

	for (i = 0; i < size; i++)
	{
		posbody = (PGAME_COORD)ListGetAt(snake_list, i);
		if (CoordEqual(posbody, &(food)))
		{
			goto new_food;
		}
	}
	return 1;

}

// ���ʳ������ꡣ
PGAME_COORD GetFood()
{
	return &food;
}

// ������
void CreateSnake(dirction dir, int head_x, int head_y, int init_len)
{
	PGAME_COORD p;
	int i;

	SetDirction(dir);

	snake_list = ListCreate(NULL);

	p = (PGAME_COORD)malloc(sizeof(GAME_COORD));
	// ��ͷ���ĳ�ʼλ�ã�
	p->x = head_x;
	p->y = head_y;
	ListPushFront(snake_list, p);

	for (i = 1; i < init_len; i++)
	{
		//p = (PGAME_COORD)malloc(sizeof(GAME_COORD));
		SnakeGorwup();
	}
	return;
}

// �ж����Ƿ����ˡ�
// ����0 ��û���� else �����ˡ�
int IsSnakeDead()
{
	PGAME_COORD posBody;
	PGAME_COORD posHead;

	int i;
	int size = ListSize(snake_list);


	// �ж��Ƿ�����
	/// �ж��Ƿ�����ǽ
	posHead = (PGAME_COORD)ListGetAt(snake_list, 0);

	if (posHead->x < 0 || posHead->x > boundary.x ||
		posHead->y < 0 || posHead->y > boundary.y)
	{
		return SNAKE_DEAD;
	}
	/// �ж��Ƿ������Լ�
	//// �ӵڶ����ڵ㿪ʼ����һ��ͷ�ڵ�Ƚϡ�
	size = ListSize(snake_list);

	for (i = 1; i < size; i++)
	{
		posBody = (PGAME_COORD)ListGetAt(snake_list, i);
		if (CoordEqual(posHead, posBody))
		{
			return SNAKE_DEAD;
		}
	}
	return SNAKE_MOVED;
}

// �����ߣ��ͷ��ڴ���Դ��
void DistroySnake()
{
	ListDistoryAndFree(snake_list);
	return;
}

// �����ƶ�һ����
// �ƶ��Ժ�����Ե���ʳ���������
// ���������ǽ�����Լ������������������Ƿ�������״̬��
int SnakeMove()
{
	// ͷ��β������
	PGAME_COORD posHead;
	PGAME_COORD posTail;

	// ��β��������ȡ�������յ�ǰ������õ�ͷ��λ�á�
	posHead = (PGAME_COORD)ListGetAt(snake_list, 0);
	posTail = (PGAME_COORD)ListPopBack(snake_list);

	// ���ݵ�ǰ�������趨�µ�ͷ���ꡣ
	switch (snake_dir)
	{
	case SNAKE_UP:
		posTail->y = posHead->y - 1;
		posTail->x = posHead->x;
		break;
	case SNAKE_DOWN:
		posTail->y = posHead->y + 1;
		posTail->x = posHead->x;
		break;
	case SNAKE_LEFT:
		posTail->x = posHead->x - 1;
		posTail->y = posHead->y;
		break;
	case SNAKE_RIGHT:
		posTail->x = posHead->x + 1;
		posTail->y = posHead->y;
		break;
	}
	ListPushFront(snake_list, posTail);

	// �ж��Ƿ�Ե���ʳ��
	if (CoordEqual(posHead, &food))
	{
		return SNAKE_EATEN_FOOD;
	}

	// ���û�гԵ�ʳ���ж��Ƿ�ײ���ϰ���Ȼ�󷵻�״̬��
	return IsSnakeDead();
}

// ������
int SnakeGorwup()
{
	// ���µĽڵ�����ڴ�
	PGAME_COORD pNewTail;
	PGAME_COORD pTail;		// ������һ�ڵ�
	PGAME_COORD pLastButOne;	// �����ڶ��ڵ�
	int size = GetSnakeSize();

	if (size >= boundary.x*boundary.y-1) //������ˣ���Ϸ������~
		return SNAKE_COMPLETE;

	if (size == 0) // û��ͷ����֪�Ӻ����������ش���
		return SNAKE_ERROR;

	pNewTail = (PGAME_COORD)malloc(sizeof(GAME_COORD));
	if (size == 1) // ֻ��һ���ڵ㣬���յ�ǰ���ƶ�����������
	{
		
		pTail = (PGAME_COORD)GetSnakeTail();
		switch (snake_dir)
		{
		case SNAKE_LEFT:
			pNewTail->x = pTail->x + 1;
			pNewTail->y = pTail->y;
			break;
		case SNAKE_RIGHT:
			pNewTail->x = pTail->x - 1;
			pNewTail->y = pTail->y;
			break;
		case SNAKE_UP:
			pNewTail->x = pTail->x ;
			pNewTail->y = pTail->y + 1;
			break;
		case SNAKE_DOWN:
			pNewTail->x = pTail->x;
			pNewTail->y = pTail->y - 1;
			break;
		}

	}
	else // ���������Ͻڵ㣬ȡ������һ�͵����ڶ�������������
	{
		pTail = (PGAME_COORD)GetSnakeTail();
		pLastButOne = (PGAME_COORD)GetSnakeAt(size - 2);
		// ���ŵ����ڶ�->������һ�ķ������һ���µĽڵ㡣
		pNewTail->x = pTail->x + (pTail->x - pLastButOne->x);
		pNewTail->y = pTail->y + (pTail->y - pLastButOne->y);

	}

	// �½ڵ���뵽��β��λ��
	ListPushBack(snake_list, pNewTail);
	return SNAKE_GROWUP;

}

// ����ߵĳ���
int GetSnakeSize()
{
	return ListSize(snake_list);
}

// ����ߵĵ�һ���ڵ������
PGAME_COORD GetSnakeHead()
{
	return (PGAME_COORD)ListGetAt(snake_list, 0);
}

// ����ߵ����һ���ڵ������
PGAME_COORD GetSnakeTail()
{
	return (PGAME_COORD)ListGetAt(snake_list, GetSnakeSize() - 1);
}

// ������Ż���ߵĽڵ�����꣬���ܳ����ߵĳ��ȣ����򷵻�NULL
PGAME_COORD GetSnakeAt(int n)
{
	if (n < ListSize(snake_list))
		return (PGAME_COORD)ListGetAt(snake_list, n);
	else
		return NULL;

}

// �ı����ƶ��ķ���
void SetDirction(dirction dir)
{

	switch (snake_dir)
	{
	case SNAKE_UP:
		if (dir == SNAKE_DOWN)
			return;
		break;
	case SNAKE_DOWN:
		if (dir == SNAKE_UP)
			return;
		break;
	case SNAKE_LEFT:
		if (dir == SNAKE_RIGHT)
			return;
		break;
	case SNAKE_RIGHT:
		if (dir == SNAKE_LEFT)
			return;
		break;
	}
	snake_dir = dir;
}


// ��õ�ǰ�ߵķ���
dirction GetDirction()
{
	return snake_dir;
}