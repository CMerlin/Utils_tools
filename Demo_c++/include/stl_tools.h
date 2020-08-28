#ifndef _PRINT_H_
#define _PRINT_H_
#if 1
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <iostream>
#include <vector>
using namespace std;
//using std::vector;

#endif

#if 1 /* 一个测试类 ************************************************************************/
class STLTest
{
public:
	~ STLTest(){
		printf("[%s][%d]:\n", __func__, __LINE__);
	};
	
	STLTest(){
		printf("[%s][%d]:\n", __func__, __LINE__);
	};
	
	STLTest(int ival, string strval);

	int setIntVal(int val);
	int setStrVal(string str);	
	int showVal();

private:
	int _ival;
	string _strval;
};
#endif /*************************************************************************/

#if 1 /* string 类的是实现 ************************************************************************/
class String
{
	// 重载 << 运算符
	friend ostream & operator<<(ostream & os, const String & str);

	// 重载 >> 运算符
	friend istream& operator >> (istream &is, String &str);
public:
	
	// 构造函数
	String(const char* str = NULL);

	// 拷贝构造函数
	String(const String &str);

	// 获得字符串长度
	int length() const;

	// 重载运算符 =
	String& operator=(const String &str);

	// 重载运算符 +
	String operator+(const String &str);

	// 重载运算符 ==
	bool operator==(const String &str);

	// 重载运算符 []
	char operator[](int n);

	// 析构函数
	~String();

private:
	char* data;		// 存放字符串内容
};
int test_myString();
#endif /*************************************************************************/

#endif
