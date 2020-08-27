
#include "String.h"

#include <ostream>

//普通的构造函数
String::String(const char *str)
{
    if (str == NULL)
    {
        m_data = new char[1];
        if (m_data != NULL)
        {
            m_data = 0;
        }
        else
        {
            exit(-1);
        }
    }
    else
    {
        int len = strlen(str);
        m_data = new char[len + 1]; //开辟一个新的空间
        if (m_data != NULL)
        {
            strcpy(m_data, str); //向新开辟的空间中存入 原数据的值
        }
        else
        {
            exit(-1);
        }
    }
}

//普通的拷贝构造函数
String::String(const String &other)
{
    int len = strlen(other.m_data);
    m_data = new char[len + 1];
    if (m_data != NULL)
    {
        strcpy(m_data, other.m_data);
    }
    else
    {
        exit(-1);
    }
}

//普通的析构函数
String::~String(void)
{
    if (m_data != NULL)
        delete[] m_data;
}

//移动构造函数
String::String(String &&other)
{
    if (other.m_data != NULL)
    {
        m_data = other.m_data;
        other.m_data = NULL; //切断原指针与之前资源的联系
    }
}

//重载赋予运算符
String &String::operator=(const String &other)
{
    if (this == &other)
    {
        return *this;
    }
    //赋值运算符是以前已经有了 重新赋值 因此要先删掉以前的信息
    delete[] m_data; //关键点 释放掉原先内存 否则会造成资源泄漏
    int len = strlen(other.m_data);
    m_data = new char[len + 1];
    if (m_data != NULL)
    {
        strcpy(m_data, other.m_data);
    }
    else
    {
        exit(-1);
    }
    return *this;
}

//重载移动赋值运算符
String &String::operator=(String &&rhs) noexcept
{
    if (this != &rhs)
    {
        delete[] m_data; //释放掉原先的垃圾资源
        m_data = rhs.m_data;
        rhs.m_data = NULL;
    }
    return *this;
}

//友元函数 重载 io
ostream &operator<<(ostream &os, const String &str)
{
    return os << str.m_data;
}