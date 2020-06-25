/*********************************************************************************************
 * Description:一些笔试中会编写的测试程序
 * name:merlin time:2017-11-30
 * *******************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*brif:删除字符串中的空格，返回空格的数目*/
int strDBlank(char*pStr) 
{
	int count = 0;
	char *ptemp = pStr; 

	while (*pStr != '\0') 
	{ 
		if (*pStr != ' '){ 
			*ptemp++ = *pStr; 
		}
		else{
			count++;
		}
		++pStr;
	} 
	*ptemp = '\0'; 
	return count;
} 

 /* brief:冒泡排序(一次比较两个相邻的元素，如果他们的顺序错误就将它们交换过来 n2) */
int bubble_sort(int *data, int n){
	int i = 0, j = 0, temp = 0;
	for(i=0; i<n-1; i++){
		for(j=0; j<n-1-i; j++){
			if(data[j]>data[j+1]){
				temp = data[j];
				data[j] = data[j+1];
				data[j+1] = temp;
			}
		}	
	}
	return 0;
}
/* brief:选择排序(从等待排序数据中找到最大或是最小的的那个数放到首位 n2) */
int select_sort(int *data, int n){
	int i = 0, j = 0, min = 0, temp = 0;

	for(i=0; i<n-1; i++){
		min = i;
		for(j=i+1; j<n; j++){
			if(data[min]>data[j]){ /*升序*/
				//if(data[min]<data[j]){ /*降序*/
				min = j;
			}
		}
		if(min!= i){
			temp = data[min];
			data[min] = data[i];
			data[i] = temp;
		}
	}
	return 0;
}

/*brif:快速排序*/
void first_sort(int *a, int left, int right)
{
    if(left >= right){
        return ;
    }
    int i = left;
    int j = right;
    int key = a[left];
     
    while(i < j)                               /*控制在当组内寻找一遍*/
    {
        while(i < j && key <= a[j]){
            j--;
        }
        a[i] = a[j];
        while(i < j && key >= a[i]){
            i++;
        }
        a[j] = a[i];
    }
     
    a[i] = key;
    first_sort(a, left, i - 1);
    first_sort(a, i + 1, right);
}

/*brief:比较两个字符串,0-相等 1-str1>str2 -1-str1<str2*/
int mystrcmp(unsigned char *str1, unsigned char *str2){
	int ret = 0;
	while(!(ret = (*str1) - (*str2)) && (*str2)){
		++str1;
		++str2;
	}
	if(0<ret)
		return 1;
	else if(0>ret)
		return -1;
	else
		return 0;
	return 0;
}

/*brief:找出两个字符串中的公共子串*/
//int getComStr(char *s1, char *s2, char **r1, char **r2){
int getComStr(char *s1, char *s2, char *dest){
	int len1 = strlen(s1);
	int len2 = strlen(s2);
	int maxlen = 0, i = 0, j  = 0;
	char temp[64] = {0};

	printf("len1=%d len2=%d\n", len1, len2);

	for(i=0; i<len1; i++){
		for(j=0; j<len2; j++){
			if((s1[i]) == (s2[j])){
				int as = i, bs = j, count = 1;
				while((as+1<len1) && (bs+1<len2) && (s1[++as]==s2[++bs])){	
					count++;
				}
				if(count>maxlen){
					maxlen = count;
					memcpy(temp, &s1[i], count);
					printf("s1=%s s2=%s temp=%s count=%d \n", s1, s2, temp, count);
					//*r1 = s1 + i;
					//*r2 = s2 + j;
				}
			}
		}
	}

	return 0;
}

/*brief:或是一段数据 (二级指针的使用)*/
int getMemmory(char **pDest, int num){
	*pDest = (char *)malloc(num*sizeof(char));
	if(NULL == (*pDest)){
		return -1;
	}
	
	sprintf((*pDest), "%s", "hello world");

	return 0;
}

int main(int argc, const char *argv[])
{
#if 1
	char *pstr = NULL;
	int ret = getMemmory(&pstr, 64);
	printf("ret=%d pstr=%s\n", ret, pstr);
	free(pstr);
	sprintf(pstr, "%s", "kkkkkkk");
	printf("ret=%d pstr=%s\n", ret, pstr);
#endif

#if 0
	char str1[32] = {"helloAhhhhhhhhhbsdsg"}, str2[32] = {"helloBhhhhhhhhhh"};
	char dstr1[32] = {0}, dstr2[32] = {0};
	char *p1 = NULL, *p2 = NULL;
	getComStr(str2, str1, dstr1);
	printf("str1=%s str2=%s p1=%s p2=%s\n", str1, str2, p1, p2);
	//printf("ret=%d\n", mystrcmp(str1, str2));
#endif

#if 0
	int ret = 0;
	char str[] = {"1 2 3 4 5 6 7"};
	printf("[%s]:str=%s line:%d\n", __func__, str, __LINE__);
	ret = strDBlank(str);
	printf("[%s]:ret=%d str=%s line:%d\n", __func__, ret, str, __LINE__);
#endif

#if 0
	int i = 0;
	int data[6] = {6, 1, 5, 3, 1, 2};
	//bubble_sort(data, 6);
	//select_sort(data, 6);
	first_sort(data, 0, 5);
	for(i=0; i<6; i++){
		printf("%d ", data[i]);
	}
	printf("\n");
	return 0;
#endif
	return 0;
}
