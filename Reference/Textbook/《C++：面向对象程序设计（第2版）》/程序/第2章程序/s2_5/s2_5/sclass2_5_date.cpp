//文件路径名：s2_5\sclass2_5_date.cpp
#include "sclass2_5_date.h"
Date::Date( )              //定义一个无参数的构造函数
{
	year=2000;  
	month=1;   
	day=1;  
} 
Date::Date(int y, int m, int d)  //定义一个带三个参数的构造函数
{
	year=y;  
	month=m;   
	day=d;  
} 
void Date::SetDate(int y, int m, int d) 
{
	year=y;  
	month=m;   
	day=d;  
} 
int Date::IsLeapYear( )
{
	return (year%4==0 && year%100!=0) || (year%400==0);
} 
void Date::Print( )
{
	cout<<year<<"年"<<month<<"月"<<day<<"日"<<endl;
}
