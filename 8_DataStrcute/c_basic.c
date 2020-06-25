#include <stdio.h>
#include <string.h>

/*
 *description:计算C中各种数据类型的大小
 * */
int dataSize()
{
	int intData = 0;
	long int lintData = 0;
	long long llData = 0;
	float floatData = 0;
	double doubleData = 0;

	char *p = NULL;
	int array[] = {1, 2, 3, 4, 5};
	int *pointter = array;

	printf("\e[32m[%s:%d]\e[0m: int=%d long_int=%d long_long=%d float=%d double=%d\n", __func__, __LINE__, 
			sizeof(intData), sizeof(lintData), sizeof(llData), sizeof(floatData), sizeof(doubleData));
	printf("\e[32m[%s:%d]\e[0m: pointer->null=%d, array=%d pointer->array=%d *pointter=%d *array=%d &array=%d\n", __func__, __LINE__,
			sizeof(p), sizeof(array), sizeof(pointter), sizeof(*pointter), sizeof(*array), sizeof(&array));
	return 0;
}

#if 1
/*
 *description:strcpy的C代码实现
 * */
char *myStrcpy(char *dest, char *src)
{
#if 0
	if((src==NULL) || (dest==NULL))
		return NULL;
	char *destData = dest;
	while((*destData++ = *src++) != '\0')
		NULL;
	return destData;
#endif
#if 1
	int i = 0;
	if((src==NULL) || (dest==NULL))
		return NULL;
	for(i = 0; src[i] != '\0'; i++)
	{
		dest[i] = src[i];
	}
	dest[i] = '\0';
	return dest;
#endif

}
#endif

int main(int argc, const char *argv[])
{
	dataSize();	/*C中各种类型的数据的长度*/
	char srcArray[] = "hello world";
	char destString[64] = {0},  *p = NULL;

	p = myStrcpy(destString, srcArray);
	printf("destString:%s p:%s\n", destString, p);

	return 0;
}
