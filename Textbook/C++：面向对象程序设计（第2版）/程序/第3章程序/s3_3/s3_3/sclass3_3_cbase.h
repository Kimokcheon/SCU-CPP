//��������ļ���s3_3\sclass3_3_cbase.h
#ifndef _SCLASS_3_3_CBASE_H
#define _SCLASS_3_3_CBASE_H
#include <iostream>  
using namespace std;  

// �������ࣺCBase
class CBase
{
public:
   	CBase( void ){ };               //���캯��
	void SetValue( int a, int b );  //Ϊ���ݳ�Աm��n��ֵ		
	void CalcuValue( void ) ;    //���ڼ���Ľӿڣ�������������ʾ����Ļ��   		
protected:
	int m;                   //������Ա
private: 
	int n;                    //˽�г�Ա 
};

//���������ࣺCDerived��Ϊ��ָ������CBase���̳з�ʽpublic��
class CDerived : public CBase 
{
public:
	CDerived( void ){ };
	void SetJ( void );		
	void SetK( void );
	void DisplayVal( void );
private:
	int j;
	int k;
};
#endif
