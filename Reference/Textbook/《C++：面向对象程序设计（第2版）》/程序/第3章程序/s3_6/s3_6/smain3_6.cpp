//�ļ�����s3_6\smain3_6.cpp
#include <iostream>  
using namespace std;  

// ������ࣺA
class A
{
public:	 
	A( void ) 
	{ 
		cout << "������A�Ĺ��캯��" << endl;
	}
	~ A( void )
	{ 
	 	cout << "������A����������" << endl;
	}	
};
class B : public A     //����������B��Ϊ��ָ�����༰�̳з�ʽ
{
public:	 
	B( void ) 
	{ 
		cout << "������B�Ĺ��캯��" << endl;
	}
	~ B( void )
	{ 
		cout << "������B����������" << endl;
	}	
};
int main( void )
{
	B b;   //ͨ�����������b�Ĵ������۲�����������๹�캯���ĵ���˳��
	   	   //ͨ������b���������۲�ϵͳ���û���������������������˳��
	return 0;
}
