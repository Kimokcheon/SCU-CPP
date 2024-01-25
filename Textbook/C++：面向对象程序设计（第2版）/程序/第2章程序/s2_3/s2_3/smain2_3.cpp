// 文件路径名: s2_3\smain2_3.cpp
#include "sclass2_3_date.h"
int main( void )
{
	//创建对象newDate时，系统调用构造函数进行初始化，使该对象的初始状态为2000年1月1日
	Date newDate; 
	//对象 newDate调用Print（）成员函数，输出newDate的状态，即各个数据成员的值
	newDate.Print( );
	return 0;
}
