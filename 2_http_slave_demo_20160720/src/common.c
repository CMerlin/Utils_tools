/****************************************************************
 * FileName:common.c
 * Author:merlin
 * Version:v1
 * Time:20160613
 * Description:里面会实现一些公共函数，如字符串处理函数
 * *************************************************************/
#include "common.h"

/******************************************************************************
 * Description：strtok_r函数的实现，使用方法和标准的 strtok_r相同
 * Input src：
 * Output dest：
 * Input dest_size：
 * Return：指针
 * *****************************************************************************/
char* lstrtok_r(char *s, const char *delim, char **save_ptr) 
{  
	char *token;  

	if (s == NULL) s = *save_ptr;  

	/* Scan leading delimiters.  */  
	s += strspn(s, delim);  
	if (*s == '\0')   
		return NULL;  

	/* Find the end of the token.  */  
	token = s;  
	s = strpbrk(token, delim);  
	if (s == NULL)  
		/* This token finishes the string.
		 * */  
		*save_ptr = strchr(token, '\0');  
	else {  
		/* Terminate the token and make
		 * *SAVE_PTR point past it.  */  
		*s = '\0';  
		*save_ptr = s + 1;  
	}  

	return token;  
}  

