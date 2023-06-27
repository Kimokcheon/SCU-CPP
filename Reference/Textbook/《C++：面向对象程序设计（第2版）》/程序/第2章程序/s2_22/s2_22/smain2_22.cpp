// 文件路径名: s2_22\smain2_22.cpp
#include<iostream>
using namespace std;
class Point
{
	int x, y;
public:
	Point(int a, int b)
	{
		x=a; 
		y=b;
	}
	void Move( int a, int b)
	{
		x+=a;
		y+=b;
	}
	void Print( )
	{
		cout<<"x="<<x<<"y="<<y<<endl;
	}
};
int main( )
{
	const Point point1( 10,10);  //声明并初始化常量对象
	point1.Move(2,2);         //常对象point1的数据不能被更改，所以错误
	point1.Print( );           //print函数的this指针不能指向常对象
	return 0;
}
