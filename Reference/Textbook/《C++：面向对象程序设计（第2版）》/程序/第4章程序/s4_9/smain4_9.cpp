//主文件
//文件名：s4_9\smain4_9.cpp

#include "sclass4_9_circle.h"	//包含类声明头文件

//主测试程序
void main()    
{
	CCircle oCC;				//调缺省构造函数创建oCC对象
	Reference( );				//调用全局重载函数Reference()
	Reference(oCC);				//调用全局重载函数Reference(CCircle &roCC)
	oCC.Reference( );			//调用oCC的成员函数

	cin.get();  
}

