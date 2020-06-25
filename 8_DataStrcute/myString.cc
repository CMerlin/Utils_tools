#include <stdio.h>
#include <string>
#include <memory>
#include <iostream>
#include <cstring>

using namespace  std;

#if 1
class MyString
{
	public:
		MyString();
		MyString(const char *ptr);
		MyString(const MyString &rhs);
		~MyString();
		MyString& operator=(const MyString& rhs);
		//MyString operator+(const MyString& rhs);
		//char operator[](const unsigned int index);
		bool operator == (const MyString &rhs);
		friend ostream& operator<<(ostream& output, const MyString &rhs); 
	private:
		char *m_data;
};
#endif

MyString::MyString()
{
	m_data = new char[1];
	//*m_data = '\0';
	m_data[0] = '\0';
}

MyString::MyString(const char* ptr)
{
	if(ptr == NULL)
	{
		m_data = new char[1];
		*m_data = '\0';
		//m_data[0] = '\0';
	}
	else
	{
		int len = strlen(ptr);
		m_data = new char[len+1];
		strcpy(m_data, ptr);
	}	
}

MyString::MyString(const MyString & rhs)
{
	int len = strlen(rhs.m_data);
	m_data = new char[len+1];
	strcpy(m_data, rhs.m_data);
}

bool MyString::operator == (const MyString &rhs)
{
	int result = strcmp(m_data, rhs.m_data);
	if(result == 0)
		return  true;
	else
		return false;
}

MyString &MyString::operator = (const MyString &rhs)
{
	if(this != &rhs)
	{
		delete[] m_data;
		m_data = new char[strlen(rhs.m_data) + 1];
		strcpy(m_data, rhs.m_data);
	}
	return *this;
}

MyString::~MyString()
{
	delete [] m_data;
}

ostream& operator<<(ostream& output, const MyString &rhs) {  
	output << rhs.m_data;  
	return output;  
}  

int main(int argc, const char *argv[])
{
	MyString strData;
	
	strData = "Hello";

	cout<<"strData:"<<strData<<endl;
	//cout<<"strData:"<<endl;

	return 0;
}
