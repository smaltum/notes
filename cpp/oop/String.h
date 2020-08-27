#ifndef String_h
#define String_h

#include <ostream>

using namespace std;

class String
{
public:
    String(const char *str = NULL); //普通构造函数
    String(const String &other);    //拷贝构造函数
    //两个引用表示 右值引用
    //我们一般说的 都是左值引用 如 &obj
    String(String &&str); //移动构造函数
    ~String(void);        //析构函数

    String &operator=(const String &str);     //复制运算符
    String &operator=(String &&rhs) noexcept; //移动赋值运算符

    //重载io cout
    friend ostream &operator<<(ostream &os, String &str);
    
    char *m_data;
};

#endif