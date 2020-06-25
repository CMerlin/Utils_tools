#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**************************************************
 * description： 链表的创建和增删查改
 * ***********************************************/
typedef struct _node
{
	int data;
	void *next;
} NODE, *P_NODE;

/*
 *description:创建链表头
 * */
P_NODE createHead()
{
	P_NODE head = NULL;
	head = (P_NODE)malloc(sizeof(NODE));
	if(head == NULL)
	{
		perror("malloc");
		return head;
	}
	head->data = 100;
	head->next = NULL;
	
	return head;
}

/*
 * description:打印链表
 * */
int printData(P_NODE head)
{
	if(head == NULL)
		return -1;
	int size = 0;
	P_NODE currentNode = head;
	printf("LIST:");
	while(currentNode != NULL)
	{
		//printf("size:%d ", size);
		size++;
		//printf("size:%d ", size);
		printf("%d ", currentNode->data);
		currentNode = currentNode->next;
	}
	printf(" size:%d\n", size);

	return 0;
}

/*
 * description:向链表中插入节点
 * */
int insertData(P_NODE head, int data)
{
	if(head == NULL)
		return -1;
	P_NODE pnode = NULL;
	pnode = (P_NODE)malloc(sizeof(NODE));
	if(pnode == NULL)
	{
		perror("malloc");
		return -1;
	}
	pnode->data = data;
	pnode->next = head->next;
	head->next = pnode;
	//printf("func:%s line:%d\n", __func__, __LINE__);
	
	return 0;
}

/*
 *description:轮询链表，找到目标节点
 * */
P_NODE findTagerNode(P_NODE head, int flag)
{
	//printf("func:%s line:%d\n", __func__, __LINE__);
	if(head == NULL)
		return NULL;
	P_NODE currentNode = head->next, lastNode = head;
	/*检测是不是头节点*/
	if(lastNode->data == flag)
		return head;

	while(currentNode != NULL)
	{
		if(currentNode->data == flag)
			return lastNode->next;
		lastNode = lastNode->next;
		if(currentNode != NULL)
			currentNode = currentNode->next;
	}

	return NULL;
}

/*
 *description:删除一个节点,返回的是头节点的地址
 * */
P_NODE deleteTagertNode(P_NODE head, int data)
{
	printf("[%s:%d] targetNode->data=%d\n", __func__, __LINE__, data);
	P_NODE lastNode = head, currentNode = head->next;
	/*check head node*/
	if(lastNode->data == data)
	{
		free(head);
		return lastNode->next;
	}
	/*check other node*/
	while(currentNode != NULL)
	{
		if(currentNode->data == data)
		{
			lastNode->next = currentNode->next;
			free(currentNode);
			return head;
		}
		lastNode = lastNode->next;
		currentNode = currentNode->next;
	}

	return head;
}

/******************************************************
 * description:快速排序
 * ***************************************************/
int main(int argc, const char *argv[])
{
	int i = 0;
	P_NODE listHead = NULL;
	listHead = createHead();
	for(i = 0; i < 6; i++)
		insertData(listHead, i);
	printData(listHead);
	/*查找头节点(data=100)和data=3的节点, data=0的节点*/
	printf("find target node  ***************************************\n");
	P_NODE tagerNode = NULL;
	tagerNode = findTagerNode(listHead, 100);
	if(tagerNode != NULL)
		printf("tagerNode->data:%d\n", tagerNode->data);
	tagerNode = findTagerNode(listHead, 3);
	if(tagerNode != NULL)
		printf("tagerNode->data:%d\n", tagerNode->data);
	tagerNode = findTagerNode(listHead, 0);
	if(tagerNode != NULL)
	{
		tagerNode->data = 11;
		printf("tagerNode->data:%d\n", tagerNode->data);
	}
	printData(listHead);
	/*delete node is data=11 and data=100*/
	printf("delete target node  ***************************************\n");
	tagerNode = deleteTagertNode(listHead, 11);
	if(tagerNode != NULL)
		printData(tagerNode);
	printData(listHead);
	tagerNode = deleteTagertNode(listHead, 100);
	if(tagerNode != NULL)
		printData(tagerNode);
	printData(listHead);

	return 0;
}
