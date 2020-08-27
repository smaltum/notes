#ifndef Student_h
#define Student_h

#include <ostream>
#include <istream>

using namespace std;

class Student
{
public:
    Student();                     //默认构造函数  不手动创建时 c++ 会默认创建
    /**
     * 拷贝构造函数的触发：
     *  1. 一个对象以值传递的方式 传入 函数体
     *  2. 一个对象以值传递的方式 在函数体中被返回
     *  3. 一个对象需要通过另外一个对象初始化
     */ 
    Student(const Student &obl);   //拷贝构造
    Student(float score, int age); //当创建带参数的构造函数之后  无参构造函数 必须手动创建
    ~Student();
    //const 修饰的是函数  表示在函数体内部 成员变量的值不允许发生改变
    float score() const
    {
        return _score;
    }

    int age() const
    {
        return _age;
    }

    //运算符 + 重载
    //此处如果不传引用 将会在函数传值的时候 产生一次 拷贝构造
    Student operator+(const Student &stu);

    //不传递引用
    //测试拷贝构造函数
    //当对象作为值传递的时候 会引发拷贝构造
    Student operator-(Student stu);

    //运算符 = 重载 将当前对象的引用返回
    Student &operator=(const Student &stu);

    /**
     * 后置++ 产生了一个新的对象
     */

    //前置++
    Student &operator++();
    //后置++
    Student operator++(int);

    //友元函数 重载输入输出
    /**
     *传统 C 中 IO有 printf  scanf  getch gets 等 他们的问题是：
     *  1. 不可编程 只能识别固有的数据类型
     *  2. 代码的移植性差 
     */

    /**
     * C++中的 ostream istream 等
     *  1. 可编程
     *  2. 简化编程 
     * 
     */

    /**
     * 
     * ios -> istream ->  ifstream
     * ios -> ostream ->  ofstream 
     *        ostream -> cout cerr clog
     * iOS -> iostream
     */

    /**
     * 标准的 io 模式提供三种标准的缓存区：
     * 1.按块缓存: 如文件系统
     * 2.按行缓存: \n
     * 3.不缓存
     */
protected:
    friend ostream &operator<<(ostream &os, const Student &stu);
    friend istream &operator>>(istream &is, Student &stu);

private:
    float _score; //分数
    int _age;     //年纪
};

#endif