//���ʵ���ļ���s3_3\sclass3_3_cbase.cpp
#include "sclass3_3_cbase.h"

void CBase::SetValue( int a, int b ) //Ϊ���ݳ�Աm��n��ֵ
{
	n = a;
	m = b;
	cout << "�����Աn �� " << n << endl; 
	cout << "�����Աm �� " << m << endl; 
}
void CBase::CalcuValue( void )  //���ڼ���Ľӿڣ�������������ʾ����Ļ��   
{ 
	cout << "n��m �� " << m*n << endl; 
}

void CDerived::SetJ( void )
{
	j = 2 * m;          //�������Ա���Է��ʻ���ı�������m
}
void CDerived::SetK( void )
{
	//k = n;       �Ƿ����������Ա���ܷ��ʻ����˽������n
	k = 0;
}
void CDerived:: DisplayVal( void )
{
	cout << "�������Աj �� " << j << endl;
	cout << "�������Աk �� " << k << endl;
}

