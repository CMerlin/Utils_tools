#include "list.h"

/*
 *description:create list head
 * */
P_NODE createHead()
{
	P_NODE head = NULL;
	head = (P_NODE)malloc(sizeof(NODE));
	if(head == NULL)
	{
		perror("malloc");
	}
	head->data = 100;
	head->next = NULL;
	return head;
}

/*
 *description:insert data to list
 * */
int insertNode(P_NODE head, int value)
{
	if(head == NULL)
	{
		printf("func:%s line:%d error, head is empty!\n", __func__, __LINE__);
		return -1;
	}

	P_NODE node = (P_NODE)malloc(sizeof(NODE));
	if(node == NULL)
	{
		printf("func:%s line:%d ", __func__, __LINE__);
		perror("malloc");
		return -1;
	}
	node->data = value;
	node->next = head->next;
	head->next = node;

	return 0;
}

/*
 * description:print list
 * */
int printData(P_NODE head)
{
	if(head == NULL)
	{
		printf("func:%s line:%d error, head is empty!\n", __func__, __LINE__);
		return -1;
	}
	P_NODE currendNode = head;
	printf("LIST:");
	while(currendNode != NULL)
	{
		printf("%d ", currendNode->data);
		currendNode = currendNode->next;
	}
	printf("\n");
	return 0;
}

/*
 *description:find tagert node
 * */
P_NODE findNode(P_NODE head, int flag)
{
	if(head == NULL)
		return NULL;
	P_NODE node = head;
	while(node != NULL)
	{
		if(node->data == flag)
			return node;
		node = node->next;
	}
	return NULL;
}

/*
 *description:delete node from in the list
 * */
int deleteNode(P_NODE head, int flag)
{
	if(head == NULL)
	{
		printf("func:%s line:%d head is empty\n", __func__, __LINE__);
		return -1;
	}
	//P_NODE deleteNode = NULL;
	P_NODE currendNode = head->next, lastNode = head;
	while(currendNode != NULL)
	{
		if(currendNode->data == flag)
		{
			lastNode->next = currendNode->next;
			free(currendNode);
			//deleteNode = currendNode;
		}
		currendNode = currendNode->next;
		lastNode = lastNode->next;
	}
	
	return 0;
}

/***************************************************************
 * Description:在链表的尾部插入数据
 * *************************************************************/
int insertNodeOnTail(NODE *p_head, int value){
	NODE *pCurNode = p_head;

	while(NULL != (pCurNode->next)){
		pCurNode = pCurNode->next;
	}

	NODE *pNode = (NODE*)malloc(sizeof(NODE));
	pNode->data = value;
	pCurNode->next = pNode;

	printf("[%s]:cNode.data=%d line:%d\n", __func__, (pCurNode->data), __LINE__);

	return 0;
}

/*
 * description:delete list head
 * */
P_NODE deleteListHead(P_NODE head)
{
	P_NODE node = NULL;
	node = head->next;
	free(head);
	return node;
}

/*
 *description:list rank
 * */
int rankList(P_NODE head)
{
#if 1
	if(head == NULL)
	{
		printf("func:%s line:%d head is empty!\n", __func__, __LINE__);
		return -1;
	}
	printf("func:%s line:%d\n", __func__, __LINE__);
	int i = 0;
	NODE tmpNode;
	for(i = 0; i < 6; i++)
	{
		P_NODE currendNode = head, nextNode = head->next;
		while(nextNode != NULL)
		{
			if(currendNode->data > nextNode->data)
			{
				tmpNode.data =  nextNode->data;
				nextNode->data = currendNode->data;
				currendNode->data = tmpNode.data;
			}
			//printf("currendNode.data:%d nextNode.data:%d\n", currendNode->data, nextNode->data);
			currendNode = currendNode->next;
			nextNode = nextNode->next;
		}
	}
#endif
#if 0
	if(head == NULL)
	{
		printf("func:%s line:%d head is empty!\n", __func__, __LINE__);
		return -1;
	}
	int i = 0;
	printf("func:%s line:%d\n", __func__, __LINE__);
	NODE tmpNode;
	printf("func:%s line:%d\n", __func__, __LINE__);
	P_NODE currendNode = head, nextNode = head->next;
	printf("func:%s line:%d\n", __func__, __LINE__);

	while(nextNode != NULL)
	{
	printf("func:%s line:%d\n", __func__, __LINE__);
		i++;
		printf("i :%d ", i);
		if(currendNode->data > nextNode->data)
		{
	printf("func:%s line:%d\n", __func__, __LINE__);
			tmpNode.next = nextNode->next;
	printf("func:%s line:%d\n", __func__, __LINE__);
			nextNode->next = currendNode;
	printf("func:%s line:%d\n", __func__, __LINE__);
			currendNode->next = tmpNode.next;
	printf("func:%s line:%d\n", __func__, __LINE__);
		}
		currendNode = currendNode->next;
	printf("func:%s line:%d\n", __func__, __LINE__);
		nextNode = nextNode->next;	
	printf("func:%s line:%d\n", __func__, __LINE__);
	}
	printf("\n");
#endif
	return 0;
}

/*
 *description:sort 快速排序，小的数据往前排，后的数据往后排  
 * */
P_NODE sort(P_NODE head)  
{  
    if (head == NULL)  
        return NULL;  
    P_NODE p = head->next;  
    P_NODE p_pre = p;  
    bool flag = false;   //用于标记是否有交换，当数组有序的时候，提高判断效率  
  
    while(p_pre->next != NULL)  
    {  
        long temp = p_pre->data;  
        p = p->next;  
        while (p)  
        {      
            if(temp <= (p->data))  
            {  
                p = p->next;  
                continue;  
            }  
            else  
            {  
                long temp_change;  
                temp_change = p->data;  
                p->data = p_pre->data;  
                p_pre->data = temp_change;  
                p = p->next;  
                flag = true;  
            }  
            if (flag == false)  
            {  
                return head;  
            }  
        }         
        p_pre = p_pre->next;  
        p = p_pre;  
    }  
    return head;   
} 

/*升序排序*/
int ascend_sort(NODE *phead){
	int count = 0, i = 0, temp = 0;
	NODE *cNode = phead, *lNode = NULL;

	while(NULL != cNode){
		cNode = cNode->next;
		count++;
	}
	for(i=0; i<count; i++){
		cNode = phead->next;
		lNode = phead;
		while(NULL != cNode){
			if((lNode->data) > (cNode->data))
			{
				temp = lNode->data;
				lNode->data = cNode->data;
				cNode->data = temp;
			}
			lNode = lNode->next;
			cNode = cNode->next;
		}
	}

	return 0;
}

#if 0
int mppx(P_NODE head)
{
	if(head == NULL)
	{
		printf("func:%s line:%d head is empty!\n", __func__, __LINE__);
		return -1;
	}
	printf("func:%s line:%d\n", __func__, __LINE__);
	NODE tmpNode;
	P_NODE currendNode = head, nextNode = head->next;
	while(nextNode != NULL)
	{
		if(currendNode->data > nextNode->data)
		{
			tmpNode.data =  nextNode->data;
			nextNode->data = currendNode->data;
			currendNode->data = tmpNode.data;
		}
		printf("currendNode.data:%d nextNode.data:%d\n", currendNode->data, nextNode->data);
		currendNode = currendNode->next;
		nextNode = nextNode->next;
	}

	return 0;
}
#endif
