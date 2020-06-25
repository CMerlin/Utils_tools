#ifndef __LIST__
#define __LIST__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
//#include <bool.h>

typedef struct _node
{
	int data;
	void *next;

} NODE, *P_NODE;

extern P_NODE createHead();
extern int insertNode(P_NODE head, int value);
extern int printData(P_NODE head);
extern P_NODE findNode(P_NODE head, int flag);
extern int deleteNode(P_NODE head, int flag);
extern P_NODE deleteListHead(P_NODE head);
extern int rankList(P_NODE head);
extern P_NODE sort(P_NODE head); 
extern int insertNodeOnTail(NODE* p_head, int data);
extern int ascend_sort(NODE *phead);
#endif
