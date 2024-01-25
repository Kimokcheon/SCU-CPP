//主文件，文件名：ch5_3\smain5_3.cpp

#include <iostream>			//包含头文件，使用iostream库
#include <string>			//包含头文件，使用string库
using namespace std;		//使用std名字空间

//声明Integer类
class CInteger				
{
public:
	CInteger(int);
	void SetItem(int);
	int GetItem( );

private:
	int m_item;
};

//声明CFloat类
class CFloat					 
{
public:
	CFloat(double);
	void SetItem(double);
	double GetItem( );

private:
	double m_item;
};

//定义CInteger构造函数
CInteger::CInteger(int item)		
{
	m_item = item;
}

//定义CInteger成员函数
void CInteger::SetItem(int item)
{
	m_item = item;
}

//定义CInteger成员函数
int CInteger::GetItem()				
{
	return m_item;
}

//定义CFloat构造函数
CFloat::CFloat(double item)
{
	m_item = item;
}

//定义CFloat成员函数
void CFloat::SetItem(double item)
{
	m_item = item;
}

//定义CFloat成员函数
double CFloat::GetItem()
{
	return m_item;
}

//测试程序
void main( )  
{
	CInteger Obj1(128);					//定义一个CInteger对象
	cout << Obj1.GetItem( ) << endl;
	Obj1.SetItem(218);
	cout << Obj1.GetItem( ) << endl;

	CFloat Obj2(0.128);					//定义一个CFloat对象
	cout << Obj2.GetItem( ) << endl;
	Obj2.SetItem(0.218);
	cout << Obj2.GetItem( ) << endl;

	cin.get();  
}

