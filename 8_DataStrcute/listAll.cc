//linklist.c
//linklist.h
//#ifndef LINKLIST_H_
//#define LINKLIST_H_
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int datatype;

typedef struct node
{
    datatype data;
    struct node *next;
}listnode, *linklist;

//int linklist linklist_create();
int linklist_insert(linklist L, datatype x, int pos);
int linklist_order_insert(linklist L, datatype x);
int linklist_delete(linklist L, int pos);
int linklist_delete(linklist L, datatype data);
int linklist_show(linklist L);
int linklist_reverse(linklist L);
int linklist_clear(linklist L);
int linklist_is_empty(linklist L);
//bool linklist_Exist(linklist L, datatype data);

//#endif
//#include "linklist.h"

//新建一个空链表
linklist linklist_create()
{
    linklist L;
    if ((L = (linklist)malloc(sizeof(listnode))) == NULL)
    {
        printf("malloc error\n");
        return NULL;
    }
    L->next = NULL;
	L->data = 100;

    return L;
}

//链表在指定位置插入
int linklist_insert(linklist L, datatype x, int pos)
{
    linklist p = NULL, q = NULL;

    while (pos--)
    {
        q = q->next;
        if (q == NULL)
        {
            printf("insert position invalid\n");
            return -1;
        }
    }

    p = (linklist)malloc(sizeof(listnode));
    p->data = x;
    p->next = q->next;
    q->next = p;

    return 0;
}

//链表按顺序插入
int linklist_order_insert(linklist L, datatype x)
{
#if 1
    linklist p, q;
    p = L;
    while (p -> next != NULL && p->next->data < x)
        p = p->next;

    q = (linklist)malloc(sizeof(listnode));
    q->data=x;
    q->next = p->next;
    p->next = q;
#endif

    return 0;
}

/*
 * description:从链表的头部插入一个节点
 * */
int headInsert(linklist head, int data)
{
	//printf("%s\n", __func__);
	linklist last = head, node;
	//linklist last = head->next, node;

	while(last->next != NULL)
		last = last->next;
#if 1
	if(last->next == NULL)
		printf("head->data:%d\n", last->data);
#endif

	node = (linklist)malloc(sizeof(listnode));
	//memset(&node, "\0", sizeof(listnode));
	node->data = data;
	node->next = last->next;
	last->next = node;

	return 0;
}

int tailInsert(linklist head, int data)
{
	return 0;
}

int insertNode(linklist head, linklist node)
{
	linklist last = head;

	while(last->next != NULL)
		last = last->next;
		
	node->next = last->next;
	last->next =  node;
	
	return 0;
}

/*
 * description:打印链表中所有的节点
 * */
int printList(linklist head)
{
	int num = 0;
	printf("%s\n", __func__);
	linklist node = head->next;
	while(node != NULL)
	{
		//++num;
		num++;
		if(num == 10)
			break;
		printf("node%d:%d ", num, node->data);
		node = node->next;
	}
	printf(" num:%d\n", num);

	return 0;
}

/*
 * description:在链表中找到某一个节点
 * */
listnode findNode(linklist head, int data)
{
	printf("%s:", __func__);
	listnode node;
	linklist Pnode = head;

	while(Pnode->next != NULL)
	{
		if(Pnode->data == data)
			break;
	}
	node = *Pnode;

	return node;
}

linklist PFindNode(linklist head, int data)
{
	int num = 0;
	printf("func:%s\n", __func__);
	//linklist Pnode = head->next;
	linklist Pnode = head;
	while(Pnode != NULL)
	{
		num++;
		printf("%d", num);
		if(num == 10)
		{
			break;
		}
		if(Pnode->data == data)
			return Pnode;
		Pnode= Pnode->next;
	}

	return NULL;
	
}

//链表删除指定位置的节点
int linklist_delete(linklist L, int pos)
{
    linklist p, q;
    p = L;
    while (--pos)
    {
    
        p=p->next;
        if (p->next == NULL)
        {
        
            printf("delete position is invalid.\n");
            return -1;
        }
    }
    q = p->next;
    p->next = p->next->next;
    free(q);
    q = NULL;

    return 0;
}

#if 0
//链表删除等于特定值的节点
int linklist_delete(linklist L, datatype data)
{
    linklist p, q;
    p = L;
	
    while (p->next != NULL)
    {
		if (p->data == data)
		{
			q = p->next;
			p->next = p->next->next;
			free(q);
			q = NULL;
			
			//break;
		}
		
        p = p->next;
    }
    

    return 0;
}
#endif

//打印链表
int linklist_show(linklist L)
{
    linklist p = L->next;
    while (p != NULL)
    {
        printf("%d  ", p->data);
        p = p->next;
    }
    printf("\n");

    return 0;
}

/*
 * description:删除链表中的所有节点
 * */
int deleteAllNode(linklist head)
{
	
	return 0;
}

//链表逆序
int linklist_reverse(linklist L)
{
    linklist p, q;
    p = L->next;
    L->next = NULL;

    while (p)
    {
        q = p;
        p = p->next;
        q->next = L->next;
        L->next = q;

    }

    return 0;
}

//删除链表
int linklist_clear(linklist L)
{
    linklist p = L, q;

    while (L->next)
    {
        p = L->next;
        L->next = p->next;
        //free(q);
        free(q);
        q = NULL;

    }

    return 0;
}

//判断链表是否为空
int linklist_is_empty(linklist L)
{
    if (L->next != NULL)
        return 0;
    else
        return 1;
}

//查找链表（除头节点外）是否存在特定值得节点

bool linklist_Exist(linklist L, datatype data)
{
	//linklist p = NULL,  q = NULL;
	linklist p = NULL;
	p = L->next;
	//bool flag = fase;
	bool flag = -1;
	
	while (p != NULL)
	{
		if (p->data == data)
		{
			flag = true;
			break;
		}
		
		p = p->next;
	}
	
	return flag;
}

#if 0
//int linklist linklist_create();
int linklist_insert(linklist L, datatype x, int pos);
int linklist_order_insert(linklist L, datatype x);
int linklist_delete(linklist L, int pos);
int linklist_delete(linklist L, datatype data);
int linklist_show(linklist L);
int linklist_reverse(linklist L);
int linklist_clear(linklist L);
int linklist_is_empty(linklist L);
//bool linklist_Exist(linklist L, datatype data);

#endif

int main(int argc, const char *argv[])
{
	int i = 0;
	linklist head = NULL;
	printf("Hello func:%s line:%d **************\n", __FILE__, __LINE__);
	head = linklist_create();
	for(i = 0; i < 10; i++)
	{ 
		linklist_order_insert(head, i);
	}

	linklist_show(head);
	linklist_delete(head, 3);
	linklist_show(head);
	printf("Hello func:%s line:%d **************\n", __FILE__, __LINE__);

	linklist Pnode = NULL;
	listnode node;
	linklist head2 = linklist_create();
	for(i = 0; i < 6; i++)
		headInsert(head2, i);
		//insertTail(head2, i);
	printList(head2);
	linklist_show(head2);
	Pnode = PFindNode(head2, 3);
	printf("Tager node:%d\n", Pnode->data);

	printf("Hello func:%s line:%d **************\n", __FILE__, __LINE__);
	
	printf("Hello func:%s line:%d **************\n", __FILE__, __LINE__);


	return 0;
}
