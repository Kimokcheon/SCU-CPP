//文件名：s3_5\smain3_5.cpp
#include "sclass3_5_vehicle.h"

int main( void )
{
	/*
	  创建一个派生类对象。创建时提供的第一个参数用于调用基类构造函数，
	  初始化基类数据成员wheels；第二个参数用于初始化对象新增数据成员passenger_load
	*/
	Car car(4,5000,5);  
	car.Show( );
	return 0;
}
