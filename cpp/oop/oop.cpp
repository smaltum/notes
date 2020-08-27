#include <iostream>

//测试类
#include "student.h"

//测试深浅拷贝
#include "String.h"

//测试文件
#include <fstream>

using namespace std;

//测试 class 的基本用法
int testClassBasic();

//测试缓冲区
int testIOBuffer();

//测试文件的io
int testFileIO();

//测试复制文件
int testCopyFile();

//测试浅拷贝
int testLightCopy();

//测试深拷贝
int testDeepCopy();

int main()
{
    return testDeepCopy();
}

//*********** c++面向对象 **************
/**
 * struct 和 class 的区别
 * 
 * struct：
 *  默认所有权限都是 public
 * 
 * class:
 *  默认所有权限都是 private
 */

/**
 * 对象是对现实世界的抽象 并不能完全映射
 */

//测试类的基本用法
int testClassBasic()
{
    {
        // Student *s = new Student();
        // Student s();//在栈中分配
        // auto w = shared_ptr<Student>(new Student(11, 21));
        // cout << w->score() << "  " << w->age() << endl;

        Student s1(10, 22);
        // Student s2(11, 22);
        // Student s3; //先定义  如果直接写 Student s3=s1+s2; 这种是直接赋值
        // s3 = s1 - s2;
        // cout << endl;
        // cout << s3.score() << " " << s3.age() << endl;
        // Student s4 = s3++;
        // cout << s4.score() << " " << s4.age() << endl;
        // ++s3;
        // cout << s3.score() << " " << s3.age() << endl;
        // cout << s3 << endl;

        Student s3(s1); //调用拷贝构造函数

        // Student s4=s1;
        Student s5;
        s5 = s1; //调用赋值运算符

        /**
         * 
         * 拷贝构造函数：在对象被创建的时候调用
         * 
         * 赋值运算符：只能被已存在的对象调用
         * 
         * 
         */
    }

    return 1;
}

//测试缓冲区
int testIOBuffer()
{
    int a;
    int index = 0;
    while (cin >> a)
    {
        cout << " int " << a << endl;
        index++;
        if (index == 5)
        {
            break;
        }
    }

    /**
     * 典型的按行缓存 所以在回车 '\n' 之后 cout才会响应   cin 也是 \n 结束
     * 
     * 在第一次输入的数据之后 不清楚缓冲区 则 下一次输入的时候 会直接从缓冲区里获取数据
     * 
     */
    //清空输入缓存区
    //numeric_limits<std::streamsize>::max() 缓存区的最大范围 可按需设置
    cin.ignore(numeric_limits<std::streamsize>::max(), '\n');

    char ch = 0;
    cin >> ch;
    cout << "char " << ch << endl;
    return 1;
}

//测试文件的io
int testFileIO()
{
    /**
     * 输入流的起点和输出流的终点 都可以是磁盘上的文件
     * 
     * c++把每个文件都看成是一个有序的字节序列 每个文件都以文件结束标志 结尾 EOF end of file
     * 
     * 按文件中的数据组织形式 可分为
     *  1. 文本文件: 文件中信息形式为 assic 码  每个字符占一个字节
     *  2. 二进制文件: 文件中信息的形式与其在内存中的存在形式一样 
     *
     */

    /**
     * 文件操作用到的头文件 fstream
     * 
     * 文件操作de常用步骤:
     * 1. 打开文件
     * 2. 判断是否打开成功
     * 3. 读 或者 写
     * 4. 检查是否读完 EOF
     * 5. 关闭文件
     */

    string fileName = "file_01.txt";

    //向文件中写入
    ofstream ofile;
    ofile.open(fileName, ios::trunc);
    if (ofile.fail()) //!ofile
    {
        cout << "create or open file failed" << endl;
        return 0;
    }
    int wIdx = 0;
    char ch[1024]; //单次输入最大值
    /**
     * cin>>ch 表示将cin缓存的数据 按空格分组 别分写入到ch数组中 
     * 当 cin 从缓存区读取数据并写入到 ch 时 写入的数据会被清空 如果存在其他数据 则不会影响其他数据
     */
    while (cin >> ch)
    {
        ofile << ch << " ";
        if ((++wIdx) >= 2)
            break;
    }

    //清空 cin 缓存区
    cin.ignore(numeric_limits<std::streamsize>::max(), '\n');

    int wInt = 0;
    cout << "please input a int " << endl;
    cin >> wInt;
    ofile << wInt;

    // ofile.flush();
    ofile.close();

    cout << endl;
    cout << "start read from file " << endl;

    //读取文件
    /**
     * 在一次打开文件的过程中  ifile >> 每读取一次 读取的索引会往后移1 直到读取到 std::char_traists<char>::eof()
     */
    ifstream ifile;
    ifile.open(fileName, ios::binary);
    if (ifile.fail()) //!ifile
    {
        cout << "open file failed" << endl;
        return 0;
    }

    char buffer[1024] = {};
    // ifile >> buffer;
    // ifile.read(buffer);

    // std::char_traits<char>::eof()  避免eof 中 字面量 -1
    //char_traits
    while (!ifile.eof())
    {
        // ifile >> buffer;
        // cout << buffer << "  " << ifile.gcount() << "  ";
        ifile.read(buffer, 1024);
        streamsize rSize = ifile.gcount();
        cout << rSize << endl;
    }

    cout << endl;
    cout << "再次读取" << endl;

    while (!ifile.eof())
    {
        ifile >> buffer;
        cout << buffer << "  " << ifile.gcount() << "  ";
    }

    ifile.close();

    return 1;
}

//测试复制文件
int testCopyFile()
{
    string oriFileName = "1.mp3";
    string aimFileName = "2.mp3";

    ofstream ofile;
    ifstream ifile;

    //ios:: 表示打开文件的模式
    ifile.open(oriFileName, ios::in | ios::binary);
    if (!ifile)
    {
        cout << "aim file open failed" << endl;
        return 0;
    }
    //写入文件
    ofile.open(aimFileName, ios::trunc);
    if (!ofile)
    {
        cout << "ori file open failed" << endl;
        return 0;
    }

    char cArr[1024];

    while (!ifile.eof())
    {
        ifile.read(cArr, 1024);
        streamsize rSize = ifile.gcount(); //获取 ifile 实际读取的字节数
        cout << rSize << endl;
        ofile.write(cArr, rSize);
    }

    ofile.close();
    ifile.close();

    return 1;
}

/**
 * 参考链接 : https://blog.csdn.net/weixin_41143631/article/details/81486817
 */

//测试浅拷贝
int testLightCopy()
{
    /**
     * 浅拷贝（位拷贝）: 只拷贝指针地址 c++ 默认的拷贝构造和赋值运算符 都是浅拷贝
     * 优点: 节省空间
     * 缺点: 由于多个指针指向同一个地址 则很有可能触发 多次释放
     * 
     * 
     * 缺省拷贝构造函数在拷贝构造的过程中是按照字节来复制的 对于指针型成员变量只复制指针的值 而不复制指针所指向的目标
     * 
     */
    string str1 = "hello";
    string str2 = str1;

    cout << &str1 << " " << &str2 << endl;
    str1 = "hello world";
    cout << str1 << " " << str2 << endl;

    return 1;
}

//测试深拷贝
int testDeepCopy()
{
    /**
     * 深拷贝：重新分配内存 指针指向内容
     * 优点：不会导致多次释放
     * 缺点：浪费空间
     * 
     * 如何优化:
     * 1.采用引用计数 （会产生额外的开销）
     * 2.c++11 支持的新标准 move 语义
     */
    String s1("hello");
    cout << s1 << endl;

    String s2(s1); //触发 拷贝构造
    cout << s2 << endl;

    String s3(std::move(s1)); //move 语义

    String s4;
    s4 = std::move(s2); //复制运算符的move语义

    return 1;
}