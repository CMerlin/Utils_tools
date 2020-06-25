#if 0
#include <stdio.h>
#include <string.h>
#endif
#include "list.h"

int main(int argc, const char *argv[])
{
	int i = 0;
	NODE  node;
	node.data  = 10;
	printf("[%s]:Hello node.data:%d line:%d\n", __func__, node.data, __LINE__);
	P_NODE listHead = NULL;
	listHead = createHead(); /*创建头节点*/

	for(i=6; i>0; i--){
		insertNodeOnTail(listHead, i);
	}
	printData(listHead);
	ascend_sort(listHead);
	//sort(listHead);
	printData(listHead);
#if 0
	for(i = 0; i < 6; i++)
		insertNode(listHead, i); 
	printData(listHead);
	deleteNode(listHead, 3);
	printData(listHead);
	/*rank list*/
	rankList(listHead);
	//listHead = sort(listHead);
	printData(listHead);

	P_NODE targetNode = NULL;
	for(i = 0; i < 20; i++)
	{
		targetNode = findNode(listHead, i);
		if(targetNode != NULL)
			printf("targetNode%d->data:%d ", i, targetNode->data);
	}
	printf("\n");

	listHead = deleteListHead(listHead);
	printData(listHead);
	for(i = 0; i < 9; i++)
		deleteNode(listHead, i);
	printData(listHead);

	return 0;
#endif	
}
