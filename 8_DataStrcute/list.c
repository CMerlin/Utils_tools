#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _listNode
{
	void *next;
	int data;
} *PNODE, NODE;
PNODE listHead;

int headInsertData2(PNODE head, PNODE node)
{
	printf("\n");
	if(head == NULL || node == NULL)
		return -1;
	if(head->next == NULL)
		printf("func:%s head->next is null\n", __func__);
	printf("func:%s node->data:%d \n", __func__, node->data);

	node->next = head->next;
	head->next = node;

	return 0;

#if 0
	printf("\n");
	if(head == NULL || node == NULL)
		return -1;
	if(head->next == NULL)
		printf("func:%s head->next is null\n", __func__);
	printf("func:%s node->data:%d \n", __func__, node->data);

	PNODE tNode = head, tmp = NULL;
	if(tNode->next == NULL)
		printf("func:%s tNode->next is null\n", __func__);
	if(tNode->next != NULL)
	{
		tmp = tNode->next;
		printf("func:%s tNode->data:%d\n", __func__, tmp->data);
	}
	while(tNode->next!= NULL)
	{
		//tmp = tNode->next;
		//printf("tNode->next.data:%d\n",  tmp->data);
		tNode = tNode->next;
	}

	node->next = tNode->next;
	tNode->next = node;

	return 0;
#endif
}

int headInsertData(PNODE head, PNODE node)
{
	if(head == NULL || node == NULL)
		return -1;
	if(head->next == NULL)
		printf("func:%s error head->next is null\n", __func__);

	printf("func:%s node.data:%d head->data:%d\n", __func__, node->data, head->data);
	//PNODE tNode = head;
	node->next = head;
	head = node;

	return 0;
}

int tailInsertData(PNODE head, PNODE node)
{
#if 1
	if(head->next == NULL)
	{
		printf("func:%s head->next is null\n", __func__);
		return 0;
	}
	PNODE p = head, q = head->next; 
	while(q != NULL)
	{
		p = p->next;
		q = q->next;
	}
	
	p->next = node;
	node->next = q;
	return 0;	
#endif	
}

PNODE findNode(PNODE head, PNODE node)
{
	PNODE p = head, q = head->next;

	if(p->next == NULL)
		return NULL;
	while(q!= NULL)
	{
		if(p->data == node->data)
		{
			return p;
		}
		p = p->next;
		q = q->next;
	}

	return NULL; 
}

PNODE findNode2(PNODE head, PNODE node)
{
	if(head->next == NULL)
	{
		printf("func:%s p->next is null\n", __func__);
		return NULL;
	}

	PNODE p = head, q = head->next;
	
	while(p != NULL)
	{
		if(p->data == node->data)
			return p;
		if(q != NULL)
		q = p->next;
		p = p->next;
	}

	return NULL;
}

int printList(PNODE head)
{
	if(head == NULL)
	{
		printf("func:%s head is NULL\n", __func__);
		return -1;
	}
	int num = 0;
	PNODE tNode = head;

	printf("func:%s ", __func__);
	//while(tNode->next != NULL)
	while(tNode != NULL)
	{
		num++;
		printf("node%d:%d ",num, tNode->data);
		tNode = tNode->next;
		if(num == 10)
			break;
	}
	printf("\n");

	return 0;
}

PNODE creatListHead()
{
	PNODE head = NULL;

	head = (PNODE)malloc(sizeof(NODE));
	if(head == NULL)
		perror("malloc");

	head->data = 100;
	head->next = NULL;
	
	return head;
}

/*
 * 在链表中的某一个节点的后面插入一个节点
 * */
int insertNodeCmd(PNODE src, PNODE node)
{
	if(src == NULL || node == NULL)
	{
		printf("func:%s src or node is null\n", __func__);
		return -1;
	}

	PNODE tmp;
	tmp = (PNODE)(src->next);
	printf("func:%s tmp.data:%d\n", __func__, tmp->data);
	node->next = src->next;
	src->next = node;

	return 0;
}

int insertNodePosNext(PNODE head, int pos, PNODE node)
{
	PNODE p = head, q = head->next;
	while(p != NULL)
	{
		if(p->data == pos)
		{
			printf("func:%s p->data:%d\n", __func__, p->data);
			//node->next = p->next;
			node->next = q;
			p->next = node;
			return 0;
		}
		p = p->next;
		if(q != NULL)
			q = q->next;
	}

	return 0;
}

int main(int argc, const char *argv[])
{
	int i = 0;
	/*init list head*/
	listHead = creatListHead();
	//listHead = &head;

	/*insert data*/
	PNODE node;
	for(i = 10; i < 12; i++)
	{
		node = (PNODE)malloc(sizeof(NODE));
		node->data = i;
		//node->next = NULL;
		//headInsertData(&listHead, node);
		headInsertData2(listHead, node);
	}
	for(i = 30; i < 33; i++)
	{
		node = (PNODE)malloc(sizeof(NODE));
		node->data = i;
		tailInsertData(listHead, node);
	}

	/*find target node*/
	NODE srcNode;
	srcNode.data = 31;
	PNODE destNode = NULL;
	destNode = findNode(listHead, &srcNode);
	printf("destNode->data:%d\n", destNode->data);	

	srcNode.data = 100;
	destNode = NULL;
	destNode = findNode2(listHead, &srcNode);
	if(destNode != NULL)
	printf("destNode->data:%d\n", destNode->data);
	printList(listHead);

	/*insert node cmd*/
	NODE tttnode;
	tttnode.data = destNode->data;
	tttnode.next = destNode->next;
	srcNode.data = 1000;
	insertNodeCmd(destNode, &srcNode);
	printList(listHead);
	node = (PNODE)malloc(sizeof(NODE));
	node->data = 9999;
	insertNodePosNext(listHead, 1000, node);
	/*print list*/
	printList(listHead);
	
	return 0;
}
