// 文件路径名: s2_6\smain 2_6.cpp
#include "sclass2_6_date.h"
int main( void )
{
    Date date1;              //创建对象没有提供实参，所以系统调用无参构造函数
	Date date2( 2012, 10, 1);   //调用带参数构造函数，采用实参值来初始化数据成员
	date1.Print( );
	cout<<"是否是闰年？"<<date1. IsLeapYear( )<<endl;
	date2.Print( );
	cout<<"是否是闰年？"<<date2. IsLeapYear( )<<endl;
	return 0;
}
