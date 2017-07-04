/************************************************************************

������

FUNCTIONS :
ListCreate			- ����һ���µ�����
ListInsertAt			- ����ڵ㵽����
ListPushFront		- ������ͷ������ڵ㡣
ListPushBack			- ������β������ڵ㡣
ListPopFront			- ɾ������ͷ���ڵ㡣
ListPopBack			- ɾ������β���ڵ㡣
ListGetFront			- ��õ�һ���ڵ�
ListGetBack			- ������һ���ڵ㡣
ListGetAt			- ������Ż�ýڵ㡣
ListDeleteAt			- �������ɾ���ڵ㡣
ListClear			- ɾ�������е����нڵ㡣
ListClearAndFree		- ��������е����нڵ㣬���ͷ����ݡ�
ListDestroy			- ɾ����������
ListDestroyAndFree	- ɾ�����������������е�ȫ���ͷš�
ListSize				- ��õ�ǰ�����С���ڵ���������


************************************************************************/

#ifndef LIST_H
#define LIST_H

typedef struct _NODE
{
	void* data;
	struct _NODE* next;
}NODE, *PNODE;

typedef struct _LIST
{
	void* list_data;
	PNODE first;
}LIST, *PLIST;


/***  ����һ���µ�����  ***/
PLIST ListCreate(void* list_data);

/***  ����ڵ㵽����   ***/
int ListInsertAt(PLIST list, unsigned int n, void* data);

/***  ������ͷ������ڵ�   ***/
void ListPushFront(PLIST list, void* data);

/***  ������β������ڵ�   ***/
void ListPushBack(PLIST list, void* data);

/***  ɾ������ͷ���ڵ�   ***/
void* ListPopFront(PLIST list);

/***  ɾ������β���ڵ�   ***/
void* ListPopBack(PLIST list);

/***  ������Ż�ýڵ�   ***/
void* ListGetAt(PLIST list, unsigned int n);

/***  �������ɾ���ڵ�   ***/
void* ListDeleteAt(PLIST list, int n);

/***  ɾ�������е����нڵ�   ***/
void ListClearAndFree(PLIST list);

/***  ɾ����������   ***/
void ListDistory(PLIST list);

/***  ɾ�����������������е�ȫ���ͷ�   ***/
void ListDistoryAndFree(PLIST list);

/***  ��õ�ǰ�����С���ڵ�������   ***/
int ListSize(PLIST list);


#endif