//文件路径名:s2_1\smain2_1.cpp
#include "sclass2_1_date.h." 
int main( void )
{
	Date d1;
	d1.SetDate(2012,11,11);
	d1.Print();
	cout<<"此年是闰年吗："<<d1.IsLeapYear()<<endl;
	return 0;
}