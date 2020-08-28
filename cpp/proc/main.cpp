#include <iostream>
using namespace std;

//断言
#include <assert.h>

//动态数组
#include <vector>

#include <string>

//auto_ptr unique_ptr
#include <memory>

//线程头文件∏
#include <thread>
#include <mutex>
mutex g_mutex;

/***
 *函数声明 
 */

//二进制转无符号int
unsigned int B2U(unsigned int iB);
//二进制转有符号int
int B2T(unsigned int iB);
//测试二进制转换
int testSignedUnsigned();

//测试ASCII char
int testChar();

//测试数组
int testArr();

//测试动态数组
int testVector();

//测试字符串
int testCharArr();

//测试string
int testString();

//测试Unicode编码
int testUnicode();

//测试字符串
int testArrayName();

//测试指针
int testPointer();

//测试const
int testConst();

//指向指针的指针
int testPointer2Pointer();

//野指针
int testUnInitPointer();

//指针的基本运算
int testPointerAction();

//测试 指针 ++ --
int testPointer_();

//测试内存分布
int testMemoryInit();

//资源管理方案 resource acquisition is initialization
int testRAII();

//测试AutoPtr
int testAutoPtr();

//测试 unique ptr
int testUniquePtr();

//测试share_ptr
int testSharePtr();

struct SA;
struct SB;

struct SAW;
struct SBW;

//测试引用
int testReference();

//线程
int testThread();

/**
 * fileBasenameNoExtension
 * preLaunch
 */

int main()
{
    return testReference();
}

//*********** c++ 面向过程 **************

/**
 * 所有测试方法
 */

int testSignedUnsigned()
{
    cout << endl;

    cout << B2U(0x0000000) << endl;
    cout << B2U(0x7FFFFFFF) << endl;
    cout << B2U(0x80000000) << endl;
    cout << B2U(0xFFFFFFFF) << endl;

    cout << endl;

    cout << B2T(0x0000000) << endl;
    cout << B2T(0x7FFFFFFF) << endl;
    cout << B2T(0x80000000) << endl;
    cout << B2T(0xFFFFFFFF) << endl;

    return 1;
}

//二进制转无符号int
unsigned int B2U(unsigned int iB)
{
    return (unsigned int)iB;
}

//二进制转有符号int
int B2T(unsigned int iB)
{
    return (int)iB;
}

int testChar()
{
    //char 并非是把char存储到存储单元上 而是将ascii存储到存储单元上
    char cA = 'a';
    cout << cA << endl;
    cout << (int)cA << endl;
    return 1;
}

int testFloat()
{
    int iA = 1;
    // float* fB=&iA;
    return 1;
}

int testArr()
{
    //数组名的作用:
    //1.获取数组的首地址
    //2.获取数组的长度
    int iArr[] = {31, 12, 53, 49};
    cout << iArr << endl;
    cout << sizeof(iArr) << endl;

    char cArr[] = {'H', 'e', 'l', 'l', 'o'};
    cout << cArr << endl;
    cout << sizeof(cArr) << endl;
    //strlen 会计算末尾的'\0'
    cout << strlen(cArr) << endl;
    cout << cArr[1] << endl;

    return 1;
}

int testVector()
{
    //动态数组 vector<T> 指定模板类型
    vector<int> vInt1(6); //默认5个元素  无初始值
    // vector<int> vInt1(5, 2); //默认5个元素 各元素初始化为2

    vector<int> vInt2; //
    // vector<int> vInt2(vInt1); //使用vInt1初始化vInt2
    // vector<int> vInt2(vInt1.begin(),vInt1.begin()+4); //使用vInt1部分元素初始化vInt2
    // vInt2.assign(5,3);//给 vInt2 重新赋值5 个 3

    cout << vInt1.capacity() << "  " << vInt1.size() << "  " << endl;

    for (int i = 0; i < vInt1.size(); i++)
    {
        cout << vInt1[i] << endl;
    }

    cout << endl;

    vInt2.clear();
    vInt2.push_back(1);
    vInt2.push_back(2);
    vInt2.push_back(3);
    vInt2.push_back(4);
    vInt2.push_back(5);

    for (int i = 0; i < vInt2.size(); i++)
    {
        cout << vInt2[i] << endl;
    }

    cout << endl;

    //删除最后一个
    // vInt2.erase(vInt2.end()); //删除指定位置的元素
    vInt2.erase(vInt2.begin() + 2, vInt2.end()); //删除指定区间的元素

    for (int i = 0; i < vInt2.size(); i++)
    {
        cout << vInt2[i] << endl;
    }

    cout << endl;

    vInt2.resize(15);

    cout << vInt2.size() << "  " << vInt2.capacity() << endl;

    return 1;
}

//测试字符串
int testCharArr()
{
    //字符串 以空字符 '\0' 结尾的字符数组
    //在声明时 应为 ‘\0’ 预留一个 位置  char str[2]={"a"}

    char cStr[3] = {"ab"}; //ab 后面 有个 '\0'
    char cStr1[2] = {'a', 'b'};

    char c1 = 0;
    char c2 = '\0';
    char c3 = '0';

    cout << endl;

    /**
     * char [] 相关操作
    */

    char cArr[] = "hello";
    char cArr1[] = "world";

    cout << strlen(cArr) << "  " << sizeof(cArr) << endl;
    //将c2连接到c1 并返回c1
    cout << strcat(cArr, cArr1) << endl;

    cout << cArr << endl;
    //将c2中的前2位 连接到c1 并返回c1
    cout << strncat(cArr, cArr1, 2) << endl;

    cout << cArr << endl;
    // cout<< strchr(cArr,'c')<<endl;

    cout << endl;
    char cArr3[100];

    //将c1 复制到 c3中
    // strcpy(cArr3, cArr);
    // cout << cArr3 << endl;

    // cArr[2] = 'w';

    cout << cArr << endl;
    // cout << cArr3 << endl;

    strncpy(cArr3, cArr, 2);

    cout << cArr << endl;
    cout << cArr3 << endl;

    cout << strlen(cArr3) << "   " << sizeof(cArr3) << endl;

    /**
     * strcat这种存在隐患 推荐使用 _s 的 api
    */

    return 1;
}

//测试str <string> 库
int testString()
{
    string str = "hello";

    cout << str.length() << " " << str.capacity() << "  " << str.size() << endl;
    cout << str[1] << "  " << &str << endl;

    cout << endl;

    string str1 = str;

    cout << str1[1] << "  " << &str1 << endl;

    cout << endl;

    //转换成c风格的 char 数组
    const char *cpArr = str.c_str();
    cout << &cpArr << endl;

    return 1;
}

//测试Unicode编码
int testUnicode()
{
    return 1;
}

//测试char arr 指针表示
int testArrayName()
{
    /**
     * 数组名就是一个空间
     * 数组本身的指向 不可改变
     * 数组指向空间内的值可以改变
     * 
     * 指针是否可以变 取决于 指针指向的区域 是否可以改变
    */

    // char *cp1 = 'c';
    // cout << cp1 << endl;

    cout << endl;

    char cArr[] = {"helloworld"};
    cout << &cArr << endl;

    // cArr[] = {"redefine"}; //数组的指向不可发生改变

    //数组的值可以发生改变
    for (int i = 0; i < 10; i++)
    {
        cArr[i] += 1;
        cout << cArr[i];
    }

    cout << endl;

    char *cpStr = "helloworld"; //指向常量区

    cout << &cpStr << endl;
    for (int i = 0; i < 10; i++)
    {
        // cpStr[i] += 1;
        cout << cpStr[i];
    }
    cout << endl;

    cpStr = cArr; //指针的指向可以发生改变
    // cpStr = &("reDefine");

    for (int i = 0; i < 8; i++)
    {
        cout << cpStr[i];
    }

    return 1;
}

//测试指针
int testPointer()
{
    //变量名可以定位到地址
    int iA = 11;

    //记录某个变量的地址
    int *piA = &iA;

    int **ppiA = &piA;
    cout << piA << "  " << *piA << "  " << *ppiA << "  " << ppiA << endl;

    cout << endl;

    // 左值 右值
    /**
     * 左值:编译器为 其 单独分配了一块空间 编译器可以取其地址 左值可以放到 赋值预算赋 的左边
     *      常见的 函数 成员变量的名字
     * 右值:数据本身 编译器不能取到其地址 只能放在 赋值预算赋 的右边
     *      没有标识符 、不可取地址的表达式、临时变量、数组名
     *      如： a=b+c  &a可以取到地址  &(b+c) 是临时变量  无法取到地址 
    */

    //指针的类型  (int char float doule *)指针的类型所占空间 都是4个字节的十六进制的整型数来表示
    /**
    * 这两处*号的意义不同
    * int* iA; //表明是指针变量
    * cout<<*iA; //表示取指针iA所在地址的值
    */

    //数组的指针（array of pointer ） 和 指针的数组 (a pointer of array)
    /**
     * 数组的指针（array of pointer ） T* t[]; 表示 t中存储多个T类型的指针
     * 指针的数组 (a pointer of array) T(*t) [] 表示指向数组的指针
     * 
     * []的优先级 比 * 高
     * 
     * int* iA[4]; //表示
     */

    unsigned int iArr[4] = {0x0000, 0x7FFF, 0x8000, 0xFFFF};

    for (int i = 0; i < 4; i++)
    {
        cout << iArr[i] << endl;
    }

    //指针数组
    unsigned int *pi[4];

    for (int i = 0; i < 4; i++)
    {
        pi[i] = &iArr[i];
        cout << pi[i] << "  " << *pi[i] << endl;
    }

    cout << endl;

    //数组的指针  指向4个int大小的数组
    unsigned int(*b)[4];
    b = &iArr; //*b 取出对应位置的数组

    cout << (*b)[2] << "   " << *b[2] << endl;

    return 1;
}

//测试常量
int testConst()
{
    /**
     * const 修饰的变量 在编译期间是不允许改变的
     * 看左侧
     * 左侧没有就看右侧
     */

    //定义数组 \\末尾存在 \0
    char cArr[] = {"helloworld"};

    char cArr1[] = {"helloworld1"};

    //pStr1的指向可以发生改变  但是指向地址所在内容的值不可发生改变
    char const *pStr1 = "helloworld";

    //const 修饰 char *  pStr2指针的指向 不可发生改变 此时报错 必须要是可以修改的左值
    char *const pStr2 = cArr;

    //一个const修饰char  一个修改指针  表示指针的指向 和 指向地址所在内容都不可改变
    char const *const pStr3 = cArr;

    for (unsigned int i = 0; i < 10; i++)
    {
        cArr[i] += 1;
        cout << cArr[i];
    }

    cout << endl;

    cout << pStr1 << endl;

    pStr1 = cArr;

    cout << pStr1 << endl;

    // pStr2=cArr1;//必须要是可以修改的左值

    // pStr3 = cArr1;

    return 1;
}

//指向指针的指针
int testPointer2Pointer()
{
    //定义int 4 字节
    int iA = 123;

    //定义int指针  指向 iA的地址
    int *piA = &iA;

    //定义二级指针 指向 piA的地址
    int **ppiA = &piA;

    return 1;
}

//野指针
int testUnInitPointer()
{
    /**
     * 当指针iA未被初始化的时候,指针iA可能被指向一个未使用的系统安全区 也有可能被指向一个可访问的区域 
     * 这时来修改指针指向的值的时候  可能导致一个完全不相干的值被修改 这样的错误 几乎无法排查
     * 因此在使用指针进行间接访问的时候 一定要确保这个指针已经被正确的初始化 并赋予恰当的值
     */

    int iA = 12;
    // int *iA; //未被初始化  此时可能被指向一个未使用的系统安全区 也可能指向一个可访问区
    int *piA = NULL; //NULL是一个特殊的指针 不指向任何东西 此时表示iA未指向任何地址
    piA = &iA;       //在使用iA间接引用的时候 一定要判断iA是否未 NULL

    if (iA != NULL)
        cout << *piA << endl;

    piA = NULL; //不用的时候 置未NULL

    /**
     * 野指针: 指向垃圾内存的指针  if判断对野指针不起作用  因为没有被置为 NULL
     * 常见产生野指针的情况
     * 1. 指针没有被初始化
     * 2. 已经释放不用的指针没有被置为 NULL、比如free delete之后的指针
     * 3. 指针超越了本身的作用范围 比如在作用域{}中引用过的指针 出了作用域 没有被置为 NULL
     * 
     * 3是难点 因为在实际应用中 很难确定一个指针的作用域范围
     * 
     * 因此不用的指针 一定要置为 NULL
     */

    return 1;
}

//指针的基本运算
int testPointerAction()
{
    char cA = 'a';
    char *pcA = &cA; //&地址符号 是个 右值操作
    // pcA=&cA;

    char cA1 = *pcA; //右值操作 此时表示取出 pcA所指向的地址上所存储的值
    *pcA = 'b';      //左值操作 此时表示 将pcA所指向地址上存储的值 变成 'b'

    cout << *pcA << endl;

    cout << *pcA + 1 << endl;

    cout << *(pcA + 1) << endl; //

    *(pcA + 1) = 'e';           //此时pcA 在栈空间中 pcA+1 地址存在 表示往后移 4个字节的空间
    cout << *(pcA + 1) << endl; //

    *(pcA++) = 'd';

    cout << *(pcA++) << endl;

    // int iB = 1;
    // (iB + 1) = 5;  //此处 iB+1 在内存中并非一个 可知的内存未知

    return 1;
}

//测试 指针 ++ --  没看太明白
int testPointer_()
{
    /**
     * 前置 ++iA  先将 iA 的值++ 然后返回
     * 后置 iA++  先将 iA 的值返回 再+1
     * 
     */
    int iA = 10;
    cout << iA++ << endl;

    int iB = 10;
    cout << ++iB << endl;

    // int *piA = NULL;

    // piA = &iA;

    // iA++=11;// 此时左值是非法的
    // ++iA = 33;  //？？？？
    // cout<<iA<<endl;

    /**
     * 贪心法
     * 
     */
    char ch = 'a';
    char *pc1 = &ch;

    char *pc2 = pc1++;
    char *pc3 = ++pc1;

    char *pc4 = pc1--;
    char *pc5 = --pc1;

    // ++pc2=&ch;
    // pc2++=&ch;

    *++pc2 = 98;

    return 1;
}

//+========================//

class A
{
private:
    int A;
};

int iA = 0;      //GVAR 全局初始化区
int *piA = NULL; //bss 全局未初始化区

//测试内存分布
int testMemoryInit() //text 代码区
{

    /**
     * 内存分布 地址从代码区到栈  从低到高分配
     * 栈 stack  由系统分配与回收
     * 未使用的内存区 unused memoery
     * 堆 heap 可由程序员自己动态分配 new 需要手动 delete 否则会造成内存泄漏
     * 常量区 
     * 全局 BSS 区 存放未初始化的全局变量
     * 全局 GVAR 区 存放初始化的全局变量
     * 代码区 TEXT  存放二进制代码
     */

    /**
     * 栈中 地址分布 是从高到低分配 也就是说先分配的 地址位高  后分配的地址为低  栈中未初始化 一般是 cc
     * 堆中 地址分布 是从低到高分配  也就是说先分配的 地址位低 后分配的地址位高  堆中未初始化 一般是 cd
     */
    int iB;
    char cA[] = {"abc"};  //栈 stack 中
    int *piB = NULL;      //栈 stack 中
    char *pcB = "123456"; //pcB 栈 stack 中  123456在常量区
    static int iC = 0;    //全局初始化区 GVAR 区
    piA = new int(11);    //piA 本身在全局未初始化区 指向的地址在 heap 中
    piB = new int(12);    //piB 在栈中  指向的地址 在 heap 中

    char *pcC = new char[7]; //pcC 本身在栈中 指向的地址在 heap 中

    A a;             //在栈上分配
    A *aA = new A(); //在堆上分配

    strcpy(pcC, "1222"); //text 代码区

    /**
     * 动态内存分配带来的不确定性:
     *  1.内存分配要多久
     *  2.分配失败怎么办
     * 在堆上分配内存时,需要使用 new 关键字 c++中释放内存用 delete
     * 
     * 程序内存管理涉及三个方面:
     *  1.分配某个大小的内存
     *  2.释放指定不用的内存
     *  3.垃圾收集操作:寻找不用的内存块并予以释放
     * 
     * 回收的策略需要实现 性能 实时性 额外开销之间的平衡  很难有一个统计 高效的做法
     * 
     * c++ 实现了 1 2
     * java 实现了 1 3
     */

    return 1; //text 代码区
}

//资源管理方案 resource acquisition is initialization
int testRAII()
{
    /**
     * c++ 所特有的资源管理方式 （rust 也采用了 raii） 但主流语言 只有 c++使用raii
     * 
     * raii 依托于 栈 与 析构  对所有的资源 包括 堆 中的资源进行管理
     * raii 使得c++不需要类似java的垃圾回收机制 也能对内存有效的进行管理 因此在c++ 垃圾回收机制理论上可行 但是并没有流行起来
     * 
     * raii 比较成熟的智能指针代表:
     *  1.std::auto_ptr
     *  2.boost::share_ptr
     *  3.
     */

    return 1;
}

//测试AutoPtr
int testAutoPtr()
{
    //多加一层大括号 确定auto_ptr的失效范围
    {
        /**
         * c++17中 已废除
         * auto_ptr 拥有严格对象所有权寓意的指针
         * auto_ptr 原理 在拷贝/赋值的过程中 直接剥夺原对象指针对内存的所有权 然后将原对象指针置为 nullptr (早期 为 NULL) 这种写法也叫管理权转移
         * 缺点：当再次通过原对象指针 访问 原对象时  程序就会报错
         * 
         * 很多企业 不允许使用 auto_ptr
         * 
         * auto_ptr 实际上是 模版类 实现
         * 
         */
        //auto_ptr 的类型 int
        // auto_ptr<int> api1(new int(19));

        // auto_ptr<string> apsArr[5] = {
        //     auto_ptr<string>(new string("C")),
        //     auto_ptr<string>(new string("C++")),
        //     auto_ptr<string>(new string("Java")),
        //     auto_ptr<string>(new string("Golang")),
        //     auto_ptr<string>(new string("Rust"))};

        // for (unsigned int i = 0; i < 5; i++)
        // {
        //     cout << (*apsArr[i]) << endl;
        // }

        //使用 auto_ptr 来剥夺 原对象的所有权
        // auto_ptr<string> aps = apsArr[3];

        // for (unsigned int i = 0; i < 5; i++)
        // {
        //     if(apsArr[i] == nullptr){
        //     }
        //     cout << ((apsArr[i] == nullptr) ? "" : *apsArr[i]) << endl;
        // }

        /**
         * 在 auto_ptr 对象被释放的时候 它所管理的对象也会自动被 delete 掉
         * 
        */
    }

    return 1;
}

//测试 unique ptr
int testUniquePtr()
{
    /**
     * c++11 中 没有 unique_ptr 
     * 
     * unique+ptr 是专属所有权 unique_ptr 管理的对象 不能被复制和赋值
     * 
     */
    //auto 自动检测数据类型
    auto w = make_unique<int>(11);

    cout << *(w.get()) << endl;

    //unique_ptr 禁止拷贝语义
    // auto w2=w;

    //unique_ptr 使用 std::move 语义 来代替所有权的转移
    auto w2 = move(w);

    cout << (w.get() != nullptr) << endl;
    cout << (w2.get() != nullptr) << endl;

    //测试 unique_ptr 会自动释放堆内存
    {
        while (true)
        {
            auto aw = unique_ptr<int>(new int(10));
            cout << *aw.get() << endl;

            // int *pi = new int(10);
            // cout << (*pi) << endl;
        }
    }

    return 1;
}

//测试share_ptr
//===测试循环引用

struct SA
{
    shared_ptr<SB> spB;

    ~SA()
    {
        cout << "~SA" << endl;
    };
};

struct SB
{
    shared_ptr<SA> spA;

    ~SB()
    {
        cout << "~SB" << endl;
    };
};

//==测试 weak_ptr
struct SAW
{
    shared_ptr<SBW> spBW;

    ~SAW()
    {
        cout << "~SAW" << endl;
    };
};

struct SBW
{
    weak_ptr<SAW> spAW;

    ~SBW()
    {
        cout << "~SBW" << endl;
    };
};

int testSharePtr()
{
    /**
     * 通过引用计数来共享一个对象
     * share_ptr 解决了 auto_ptr 在对象所有权上的局限性
     * 利用 引用计数的机制（需要额外的开销） 实现了 共享内存的智能指针
     * 
     * 当引用计数为0 也就是 use_count = 0; 时 对象被析构
     */

    shared_ptr<int> spi1(new int(10));

    {
        shared_ptr<int> spi2 = spi1; //两个指针 指向 同一片地址
        cout << *spi1.get() << "  " << spi1.use_count() << endl;
        cout << *spi2.get() << "  " << spi2.use_count() << endl;
    }
    //当 spi2 失效 时 引用计数自动减 1
    cout << *spi1.get() << "  " << spi1.use_count() << endl;

    /**
     * 引用计数的副作用： 循环引用
     * A 中 有指向B的引用  B中也有指向A的引用  当A释放的时候 发现含有B的引用 于是要去释放B 让释放B的时候 发现含有A的引用  于是释放A 产生了循环
     */

    //在堆中分配两个struct
    {
        shared_ptr<SA> spA(new SA());
        shared_ptr<SB> spB(new SB());

        cout << spA.use_count() << endl;
        cout << spB.use_count() << endl;

        //循环引用之后 堆内存将无法释放 造成内存泄漏
        spA->spB = spB;
        spB->spA = spA;
    }
    cout << "test weak_ptr" << endl;
    //测试weak_ptr
    {
        shared_ptr<SAW> spAW(new SAW());
        shared_ptr<SBW> spBW(new SBW());

        cout << spAW.use_count() << endl;
        cout << spBW.use_count() << endl;

        //循环引用之后 堆内存将无法释放 造成内存泄漏
        spAW->spBW = spBW;
        spBW->spAW = spAW;
    }

    return 1;
}

//传递引用
void swapReference(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

//传递指针
void swapPointer(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

//测试引用
int testReference()
{
    /**
     * 引用是什么?
     *      引用是一种特殊的指针,不允许修改的指针
     * 
     * 使用指针的坑：
     *  1.空指针
     *  2.野指针
     *  3.不知觉中改变了指针的值 却还在继续使用
     * 
     * 使用引用：
     *  1.不存在空引用
     *  2.必须初始化
     *  3.永远指向初始化它的那个对象
     * 
     */

    //引用就可以看作某个变量的 别名 其实还是那个对象自己
    int iA = 1, iB = 2;
    int &rA = iA; //rA 存储 iA的引用
    cout << iA << " " << rA << endl;
    // rA = iB;
    // cout << iA << " " << rA << endl;

    swapReference(iA, iB);
    cout << iA << " " << iB << endl;
    // assert(iA == 2 && iB == 1);

    swapPointer(&iA, &iB);
    cout << iA << " " << iB << endl;
    // assert(iA == 1 && iB == 2);

    /**
     * 
     * 有指针为什么还要有引用？
     *  Java中完全用引用 而c语言完全用指针
     *  c++之父 -->  为了支持函数的运算法重载
     * 
     * 有引用为什么还要用指针？
     *  c++之父 -->  c++为了兼容c的语法和编译器
     */

    /**
     * 什么时候传值  什么时候传引用
     * 
     * 对于函数而言 基础类型  传值效率更高
     * 
     * 对于自定义类型而言  传引用更高效
     * 
     */

    

    return 1;
}


//*********** c++ stl **************

//线程方法1
void tf1()
{
    g_mutex.lock();
    cout << "T1"
         << "    running ..." << endl;
    g_mutex.unlock();
}

//线程方法2
void tf2(const char *tName)
{
    g_mutex.lock();
    cout << tName
         << "    running ..." << endl;
    g_mutex.unlock();
}

int testThread()
{
    thread t1(tf1);
    thread t2(tf2, "T2");
    t1.join();
    t2.join();
    return 1;
}
