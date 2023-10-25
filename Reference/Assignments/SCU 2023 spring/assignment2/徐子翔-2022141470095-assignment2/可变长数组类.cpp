#include <bits/stdc++.h>
using namespace std;
class carray
{
    int size;                                   //数组元素的个数
    int * ptr;                                  //指向动态数组的指针
    public:
        carray(int s = 0);                   // 构造函数，s:数组元素个数，缺省时默认为0，对应实现数组特性1
        carray(carray & a);                // 复制构造函数
        ~ carray();                            //析构函数
        
        //建立构造该类特性的成员函数
        void push_back(int v);                                   //在尾部添加一个整型元素v，无返回值
        carray & operator = (const carray & a);          //用于数组对象间的赋值，该函数的返回类型为该类的引用
        int length() const {return size;}                      //返回数组元素个数
        //上一行中的const关键字表示：length()是只读函数，不能修改类中的成员变量的值，只能引用。此写法只能用于成员函数
        
        int & operator [] (int i)             //重载运算符[]，操作对象是i，使得该类支持根据下标访问数组元素
        {
            return ptr[i];                       //利用数组指针的性质
        }
};

carray :: carray(int s) : size(s)           //在此位置，不能将缺省使得默认值=0写上
{
    if(s == 0)
        ptr = NULL;                           //若s为0，则指针为空指针
    else
        ptr = new int[s];                     //若s不为0，则指针指向新开辟的int[s]的动态内存空间
}
carray :: carray(carray & a)
{
    if(!a.ptr)
    {
        ptr = NULL;                            //若a.ptr为空，则使新初始化对象中的ptr为空，size为0，且结束该函数
        size = 0;
        return;                                   //不带返回值的return语句，用于void函数，运行至此即不再继续此函数
    }
    ptr = new int[a.size];                   //若a.ptr不为空，则为ptr开辟一个与a.ptr同样大小的动态空间
    memcpy(ptr, a.ptr, sizeof(int) * a.size);       
    //memcpy函数用于将a.ptr中的内容逐字节拷贝到ptr中，拷贝的字节数为sizeof(int)*a.size
    //存放于<cstring>头文件中，与strcpy不同之处在于，不是遇到“\0”结束，而是一定会拷贝完给定的字节数
    size = a.size;
}
carray :: ~ carray()                          //析构函数在对象消亡时释放掉ptr指向的内存空间，防止其变为内存垃圾
{
    if(ptr)
        delete [] ptr;
}
carray & carray :: operator = (const carray & a)
{
    //重载后“=”可以使左边对象中存放的数组大小和内容与右边对象一样
    if(ptr == a.ptr)                            //当出现“a=a"这样的错误赋值时，结束函数并且返回指向对象a的this指针
        return * this;
    if(a.ptr == NULL)                        //当a.ptr为空时，ptr同样应为空
    {                                               
        if(ptr)                                    //ptr如果已有内容，应当将该片内存空间释放
            delete [] ptr;
        ptr = NULL;
        size = 0;
        return * this;                              
    }
    if(size < a.size)                          //若原内存空间不够大，需分配新的空间（释放掉之前的内存空间）
    {
        if(ptr)
            delete [] ptr;
        ptr = new int[a.size];              //分配的新内存空间应当和右边对象一致
    }
    memcpy(ptr, a.ptr, sizeof(int) * a.size);       
    size = a.size;
    return * this;
}
void carray :: push_back(int v)                              //数组尾部添加一个元素v
{
    if(ptr)                                                            //若ptr不为空
    {
        int * tempptr = new int[size + 1];                  //重新分配空间
        memcpy(tempptr, ptr, sizeof(int) * size);       //复制原数组内容到临时tempptr数组中
        delete [] ptr;                                             //释放ptr指向的空间
        ptr = tempptr;                                           //ptr指向新的内存空间
    }
    else                                                            //数组本来为空
        ptr = new int[1];
    ptr[size ++] = v;                                           //加入新的数组元素
}

int main()
{
    carray a;
    for(int i=0; i<5; ++i)
        a.push_back(i);
    carray a2, a3;
    a2 = a;
    for (int i=0; i< a.length(); ++i)
        cout << a2[i] << " ";
    a2 = a3;
    for(int i=0; i<a2.length(); ++i)
        cout << a2[i] << " ";
    cout << endl;
    a[3] = 100;
    carray a4(a);
    for(int i=0; i < a4.length(); ++i)
        cout << a4[i] <<" ";
    cout << endl;
    return 0;
}