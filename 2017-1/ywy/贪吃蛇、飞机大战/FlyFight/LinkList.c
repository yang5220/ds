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
ListGetNodeAt		- ������Ż�ýڵ㡣
ListDeleteNodeAt		- �������ɾ���ڵ㡣
ListDestroy			- ɾ����������
ListDestroyAndFree	- ɾ�������������ͷ����ݡ�
ListClear			- ɾ�������е����нڵ㡣
ListClearAndFree		- ��������е����нڵ㣬���ͷ����ݡ�
ListGetSize			- ��õ�ǰ�����С���ڵ���������


************************************************************************/
#include <stdlib.h> // ʹ�õ���malloc(), free()�Ⱥ�����
#include "LinkList.h"



#ifdef _LIST_DEBUG
#include <stdio.h>
void ListPrint(PLIST list)
{
	int i;
	int n = ListSize(list);
	printf("size: %d\n", ListSize(list));
	for (i = 0; i < n; i++)
	{
		printf("data: %p", ListGetAt(list, i));
	}
}

int test_case()
{
	PLIST test = ListCreate(0);
	ListPrint(test);

	ListPushBack(test, 0);
	ListPrint(test);

	ListPushBack(test, 1);
	ListPushBack(test, 2);
	ListPushBack(test, 3);
	ListPrint(test);

	ListPushBack(test, 4);
	ListPushBack(test, 5);
	ListPushBack(test, 6);
	ListPrint(test);

	ListDeleteAt(test, 4);
	ListPrint(test);

	ListDeleteAt(test, 0);
	ListPrint(test);

	ListDeleteAt(test, 5);
	ListPrint(test);

	ListInsertAt(test, 3, 7);
	ListPrint(test);

	ListInsertAt(test, 0, 8);
	ListPrint(test);

	ListInsertAt(test, ListSize(test) - 1, 9);
	ListPrint(test);

	ListDistory(test);
}

#endif


// ����һ������ڵ�
PNODE NodeCreate(void* data)
{
	PNODE pnode = (PNODE) malloc(sizeof(NODE));
	pnode->data = data; 
	pnode->next = 0;
	return pnode;
}

// ��������ڵ㼰�����ݡ�
void NodeDistory(PNODE node)
{
	free(node->data);
	free(node);
}

// �������Ĵ�С���ڵ���������
int ListSize(PLIST list)
{
	int  cnt;
	PNODE node = list->first;

	cnt = 0;
	while (node)
	{
		cnt++;
		node = node->next;
	}
	return (cnt);
}

// ɾ���������ض�λ�õĽڵ㣬���������ݡ�
// ���� -1 ��ʾ����
// ���� >= ��ʾ�����λ�á�
int ListInsertAt(PLIST list, unsigned int n, void* data)
{
	unsigned int  i;
	PNODE tmp;
	PNODE prev;
	PNODE new_node;

	if (n < 0)
		return -1;
	if (n == 0)
	{
		ListPushFront(list, data);
		return 0;
	}
	i = 1;
	tmp = list->first;
	prev = tmp;
	while (i <= n)
	{
		prev = tmp;
		tmp = tmp->next;
		if (!tmp)
			return -1;
		++i;
	}
	new_node = NodeCreate(data);
	prev->next = new_node;
	new_node->next = tmp;
	return i;
}


// ɾ���������ض�λ�õĽڵ㣬���������ݡ�
void* ListDeleteAt(PLIST list, int n)
{
	int  i;
	PNODE tmp;
	PNODE prev;
	void* data;

	tmp = list->first;
	prev = tmp;
	if (n < 0)
		return (NULL);
	if (n == 0)
	{
		return ListPopFront(list);
	}
	i = 1;
	
	while (i <= n)
	{
		prev = tmp;
		tmp = tmp->next;
		if (!tmp)
			return (NULL);
		++i;
	}
	prev->next = tmp->next;
	data = tmp->data;
	free(tmp);
	return data;
}


// ���ָ��λ���Ͻڵ��е����ݡ�
void* ListGetAt(PLIST list, unsigned int n)
{
	unsigned int   i;
	PNODE node = list->first;

	if (!node)
		return (NULL);
	
	for (i = 1; i <= n; i++)
	{
		node = node->next;
		if (!node)
			return (NULL);
	}
	return (node->data);
}

// ��������
PLIST ListCreate(void* list_data)
{
	PLIST new_list;

	new_list = NULL;
	new_list = (PLIST)malloc(sizeof(LIST));
	if (new_list != NULL)
	{
		new_list->list_data = list_data;
		new_list->first = NULL;
	}
	return (new_list);
}

// ֻ�ͷ�����ͷ�������ͷ�������
void ListDistory(PLIST list)
{
	if (list != NULL)
	{
		if (list->list_data != NULL)
			free(list->list_data);
		free(list);
	}
}

// �ͷ��������������нڵ������
void ListDistoryAndFree(PLIST list)
{
	if (list != NULL)
	{
		ListClearAndFree(list);
		if (list->list_data != NULL)
			free(list->list_data);
		free(list);
	}
}

// ��ȡ����ͷ�����ݣ�����������ɾ����
void* ListPopFront(PLIST list)
{
	PNODE tmp;
	void*  data = NULL;
	if (list != NULL)
	{
		if (list->first != NULL)
		{
			tmp = list->first;
			data = tmp->data;
			list->first = tmp->next;
			free(tmp);
		}
	}
	return (data); 
}

// ��ȡ����β�����ݣ�����������ɾ����
void* ListPopBack(PLIST list)
{
	PNODE prev;
	PNODE current;
	PNODE node = list->first;
	void* data;

	if (!node)
		return (NULL);
	if (!(node)->next)
	{
		data = (node)->data;
		free(node);
		node = NULL;
		return (data);
	}
	prev = node;
	current = (node)->next;
	while (current->next)
	{
		prev = current;
		current = current->next;
	}
	data = current->data;
	free(current);
	prev->next = NULL;
	return (data);
}

// �������ݵ�����β����
void ListPushBack(PLIST list, void* data)
{
	PNODE tmp;
	PNODE new_node = NodeCreate(data);

	if (new_node)
	{
		if (list)
		{
			if (list->first)
			{
				tmp = list->first;
				while (tmp->next)
					tmp = tmp->next;
				tmp->next = new_node;
			}
			else
				list->first = new_node;
		}
	}
}

// �������ݵ�����ͷ����
void ListPushFront(PLIST list, void* data)
{
	PNODE new_node;

	if (list != NULL)
	{
		new_node = NodeCreate(data);
		if (new_node != NULL)
		{
			new_node->next = list->first;
			list->first = new_node;
		}
	}
}


// ɾ���������нڵ㣬free���ݡ�
void ListClearAndFree(PLIST list)
{
	PNODE tmp;
	PNODE node;

	if (list != NULL)
	{
		node = list->first;
		while (node)
		{
			tmp = node->next;
			NodeDistory(node);
			node = tmp;
		}
		list->first = 0;
	}
}