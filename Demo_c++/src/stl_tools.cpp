/******************************************************************************************
* Brif:
*
*******************************************************************************************/

//#include <stdio.h>
//#include <string.h>
#include "stl_tools.h"

#if 1 /*************************************************************************/
int STLTest::setIntVal(int val){
	_ival = val;
	return 0;
}

int STLTest::setStrVal(string str){
	_strval = str;
	return 0;
}

int STLTest::showVal(){
	//printf("[%s][%d]:ival=%d\n", __func__, __LINE__, _ival);
	std::cout<<"["<<__func__<<"]"<<"["<<__LINE__<<"]:"<<"ival="<<_ival<<" strval="<<_strval<<std::endl;
	return 0;
}
STLTest::STLTest(int ival, string strval){
	printf("[%s][%d]:\n", __func__, __LINE__);
	_ival = ival;
	_strval = strval;
}
#endif /*************************************************************************/


#if 1 /* string 类的是实现 ************************************************************************/
String::String(const char * str): data(NULL)
{
	if(str != NULL)
	{
		this->data = new char[strlen(str) + 1];
		if (this->data == NULL)
		{
			cout << "new error!" << endl;
			exit(-1);
		}
		strcpy(this->data, str);
	}
}

String::String(const String & str)
{
	if (str.data == NULL)
	{
		this->data = NULL;
	}
	else
	{
		this->data = new char[strlen(str.data) + 1];
		if (this->data == NULL)
		{
			cout << "new error!" << endl;
			exit(-1);
		}
		strcpy(this->data, str.data);
	}
}

int String::length() const
{
	return strlen(this->data);
}

String & String::operator=(const String & str)
{
	if (this->data != str.data)
	{
		delete this->data;
		this->data = NULL;

		if (str.data != NULL)
		{
			this->data = new char[strlen(str.data) + 1];
			if (this->data == NULL)
			{
				cout << "new error!" << endl;
				exit(-1);
			}
			strcpy(this->data, str.data);
		}
	}

	return *this;
}

String String::operator+(const String & str)
{
	String* newString = new String;
	if (str.data == NULL)
	{
		*newString = *this;
	}
	else if (this->data == NULL)
	{
		*newString = str;
	}
	else
	{
		newString->data = new char[strlen(this->data) + strlen(str.data) + 1];
		strcpy(newString->data, this->data);
		strcat(newString->data, str.data);
	}
	return *newString;
	delete newString;
}

bool String::operator==(const String & str)
{
	if (this->length() != str.length())
	{
		return false;
	}
	return strcmp(this->data, str.data) ? false : true;
}

char String::operator[](int n)
{
	if (n < 0 || n > this->length())
	{
		cout << "argument error!" << endl;
		exit(-1);
	}
	else
	{
		return this->data[n];
	}
}

String::~String()
{
	if (this->data != NULL)
	{
		delete this->data;
		this->data = NULL;
	}
}

ostream & operator<<(ostream & os, const String & str)
{
	os << str.data;
	return os;
}

istream & operator >> (istream & is, String & str)
{
	char temp[255] = { 0 };
	is >> temp;
	str.data = new char[strlen(temp) + 1];
	strcpy(str.data, temp);
	return is;
}

#if 1
int test_myString()
{
	String str1 = "Hello";
	cout << str1 << endl;
	cout << "str1的长度为: " << str1.length() << endl;
	cout << str1[4] << endl;

	String str2("World!");
	cout << str2 << endl;

	String str3;
	str3 = str1;
	cout << str3 << endl;
	
	String str4 = str1 + str2;
	cout << "str4: " << str4 << endl;
	
	system("pause");
	return EXIT_SUCCESS;
}
#endif
#endif /*************************************************************************/


