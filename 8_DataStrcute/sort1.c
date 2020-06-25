#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN 6

/*
 * desctription:print data
 * */

int printData(int *dest, int len)
{
	int i = 0;
	for(i = 0; i < len; i++)
	{
		printf("%d ", (int)(dest[i]));
	}
	printf("\n");

	return 0;
}

/*
 *desctription:快速排序
 * */
int quickSort()
{
	int i = 0, j = 0,  n = 6;
	int array[n], temp = 0;

	for(i = 0; i < n; i++)
	{
		array[i] = i;
	}
	array[0] = 33;
	array[3] = 15;
	array[4] = 4;

	printf("******************************\n");
	printData((array), n);
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n-i; j++)
		{
			if(array[j] > array[j+1])
			{
				temp = array[j];
				array[j] = array[j+1];
				array[j+1] = temp;
			}
		}
	}

	printf("func:%s:", __func__);
	printData((array), n);
	
	return 0;
}

/*
 * description:selection sort
 * */
int selectionSort(int array, int len)
{
	int temp = 0;
	int i = 0, j = 0, minIndex = 0;

	for()
	
	return 0;
}


int main(int argc, const char *argv[])
{
	quickSort();
	return 0;
}
