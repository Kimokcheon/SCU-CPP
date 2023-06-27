// 文件路径名: s2_8\smain 2_8.cpp
#include "sclass2_8_cpoint.h"
int main( void )
{
	CPoint a( 20,50 );        //系统调用构造函数，创建了一个坐标为( 20,50 )的点a
	CPoint b( a );            //系统调用拷贝构造函数，利用点a克隆点b
	CPoint c = a;             //系统调用拷贝构造函数，利用点a克隆点c
	cout << "点a的坐标是（" << a.GetX( ) << "," << a.GetY( ) << "）" << endl;
	cout << "点b的坐标是（" << b.GetX( ) << "," << b.GetY( ) << "）" << endl;
	cout << "点c的坐标是（" << c.GetX( ) << "," << c.GetY( ) << "）" << endl;
	return 0;
}
