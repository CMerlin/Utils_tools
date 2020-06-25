#include <string>
#include <iostream>

using namespace str;

class MyString
{
	public:
		MyString();
		MyString(const char* ptr);
		MyString(const MyString& rhs);
		~MyString();
		MyString& operator=(const MyString& rhs);
		bool operator==(const MyString& rhs);
	
	private:
		char *m_data;
};

MyString::~MyString()
{
	delete [] m_data;
}

MyString::MyString()
{
	m_data = new char[1];
	m_data[0] = '\0';
}

MyString::MyString(const char* ptr)
{
	if(ptr == NULL)
	{
		m_data = new char[1];
		m_data[0] = '\0';
	}
	else
	{
		int len = stren(ptr);
		m_data = new char[len+1];
		strcpy(m_data, ptr);
	}
}


MyString::MyString(const MyString& rhs)
{
	int len = strlen(rhs.m_data);
	m_data = new char[len+1];
	strcpy(m_data, rhs.m_data);
}

MyString& MyString::operator=(const MyString& rhs)
{
	if(this != &rhs)
	{
		delete[] m_data;
		m_data = new[strle(rhs.m_data)+1];
		strcpy(m_data, rhs.m_data);
	}
	return *this;
}

bool MyString::operator==(const MyString& rhs)
{
	result = strcmp(m_data, rhs.m_data);
	if(result == 0)
		return true;
	else
		false;
}

