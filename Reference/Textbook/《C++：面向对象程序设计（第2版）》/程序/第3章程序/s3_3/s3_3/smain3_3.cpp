//测试程序
//主文件：s3_3\smain3_3.cpp
#include "sclass3_3_cbase.h"
int main( void )
{	
	CDerived d;        //创建派生类对象d
	//派生类对象d调用基类的外部接口SetValue( )，为基类的数据成员m和n赋初值
	d.SetValue(10,20);	
	//对象d调用基类的外部接口CalcuValue( )，将计算结果显示在屏幕上
	d.CalcuValue( );  
	d.SetJ( );           //对象d调用本类的外部接口SetJ( )，为同类的数据成员j赋初值
	d.SetK( );          //对象d调用本类的外部接口SetK( )，为同类的数据成员k赋初值
	//对象d调用本类的外部接口DisplayVal( )，将同类中j和k的值显示在屏幕上
	d.DisplayVal( ); 
	return 0;
}
