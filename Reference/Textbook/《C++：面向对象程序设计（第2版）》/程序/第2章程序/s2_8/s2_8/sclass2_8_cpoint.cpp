//�ļ�·������s2_8\sclass2_8_cpoint.cpp 
#include "sclass2_8_cpoint.h"
CPoint::CPoint( int x1, int y1 )      
{
	x = x1;
	y = y1;
}
CPoint::CPoint( CPoint &obj )   //�������캯��
{
	x = obj.x;
	y = obj.y;
}
int CPoint::GetX( void )        //ͨ���ӿڼ�ӷ���x����
{
	return x;
}
int CPoint::GetY( void )        //ͨ���ӿڼ�ӷ���y����
{
	return y;
}
