// �ļ�·����: s2_6\smain 2_6.cpp
#include "sclass2_6_date.h"
int main( void )
{
    Date date1;              //��������û���ṩʵ�Σ�����ϵͳ�����޲ι��캯��
	Date date2( 2012, 10, 1);   //���ô��������캯��������ʵ��ֵ����ʼ�����ݳ�Ա
	date1.Print( );
	cout<<"�Ƿ������ꣿ"<<date1. IsLeapYear( )<<endl;
	date2.Print( );
	cout<<"�Ƿ������ꣿ"<<date2. IsLeapYear( )<<endl;
	return 0;
}
