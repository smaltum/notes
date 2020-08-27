
//尖括号 表示 系统自带的头文件
#include <iostream>
#include <ostream>
#include <istream>

//引号表示 自定的头文件
#include "student.h"

Student::Student()
{
    std::cout << "Student()  " << this << std::endl;
}

//拷贝构造
Student::Student(const Student &obj)
{
    std::cout << "Student(const Student &obj)  " << this << std::endl;
}

Student::Student(float score, int age)
{
    _score = score;
    _age = age;
    std::cout << "Student(float score, int age)  " << this << std::endl;
}

Student::~Student()
{
    std::cout << "~Student()   " << this << std::endl;
}

Student Student::operator+(const Student &stu)
{
    std::cout << "operator+  before   " << &stu << std::endl;
    //测试写法
    Student temp;
    std::cout << "operator+  after   " << &stu << std::endl;

    temp._score = _score + stu.score();
    temp._age = _age + stu.age();
    return temp;

    //优化写法
    // _score += stu.score();
    // _age += stu.age();
    // return *this;
}

Student Student::operator-(Student stu)
{
    std::cout << "operator-  before   " << std::endl;
    //测试写法
    Student temp;
    std::cout << "operator-  after   " << std::endl;
    temp._age = _age - stu.age();
    temp._score = _score - stu.score();
    return temp;
}

Student &Student::operator=(const Student &stu)
{
    cout << "operator=  " << &stu << endl;
    if (this != &stu)
    {
        _score = stu.score();
        _age = stu.age();
    }
    return *this;
}

Student &Student::operator++()
{
    _age++;
    _score++;
    //直接返回引用
    return *this;
}

Student Student::operator++(int)
{
    Student temp;
    temp._age = _age++;
    temp._score = _score++;
    return temp;
}

//友元函数

ostream &operator<<(ostream &os, const Student &stu)
{
    return os << stu.age() << "  " << stu.score();
}
