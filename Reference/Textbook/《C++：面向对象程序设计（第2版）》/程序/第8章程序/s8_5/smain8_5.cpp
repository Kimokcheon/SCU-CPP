//文件名：s8_5\smain8_5.cpp
//异常示例

#include <iostream>
#include <string>
using namespace std;

void MyFunc( void );

class CMyException 							//定义异常类
{
public:
    CMyException(){ };
    ~CMyException(){ };
    const char *ShowExceptionReason() const	//显示异常原因
	{ 
		return "CMyException Exception."; 
	}
};

class CDemo				//定义一个工作类，用以显示其执行与异常抛出的顺序
{
public:
    CDemo();
    ~CDemo();
};

CDemo::CDemo()
{
    cout << "Constructing CDemo." << endl;
}

CDemo::~CDemo()
{
    cout << "Destructing CDemo." << endl;
}

//异常也可以多层封装，例如：在MyFunC()中封装throw、try、catch机制
//在这里捕获相关异常，然后在其调用层再捕获本层不能捕获的异常
//本实例程序，只在main()中进行了异常捕获处理
void MyFunc()												
{
    CDemo D;
    cout << "\nIn MyFunc(). Throwing CMyException exception." << endl;
    throw CMyException();				//抛出异常
}

void main()
{
    try									//用try封装可能会出现异常的代码
    {
        cout << "In try block, calling MyFunc()." << endl;
        MyFunc();
    }
    catch( CMyException E )				//一路捕获并处理异常
    {
        cout << "Caught: ";
        cout << E.ShowExceptionReason() << endl;
    }
    catch( string str )					//二路捕获并处理异常
    {
        cout << "Caught some other exception: " << str << endl;
    }

	cin.get();
}

