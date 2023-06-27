//���ļ����ļ�����ch5_3\smain5_3.cpp

#include <iostream>			//����ͷ�ļ���ʹ��iostream��
#include <string>			//����ͷ�ļ���ʹ��string��
using namespace std;		//ʹ��std���ֿռ�

//����Integer��
class CInteger				
{
public:
	CInteger(int);
	void SetItem(int);
	int GetItem( );

private:
	int m_item;
};

//����CFloat��
class CFloat					 
{
public:
	CFloat(double);
	void SetItem(double);
	double GetItem( );

private:
	double m_item;
};

//����CInteger���캯��
CInteger::CInteger(int item)		
{
	m_item = item;
}

//����CInteger��Ա����
void CInteger::SetItem(int item)
{
	m_item = item;
}

//����CInteger��Ա����
int CInteger::GetItem()				
{
	return m_item;
}

//����CFloat���캯��
CFloat::CFloat(double item)
{
	m_item = item;
}

//����CFloat��Ա����
void CFloat::SetItem(double item)
{
	m_item = item;
}

//����CFloat��Ա����
double CFloat::GetItem()
{
	return m_item;
}

//���Գ���
void main( )  
{
	CInteger Obj1(128);					//����һ��CInteger����
	cout << Obj1.GetItem( ) << endl;
	Obj1.SetItem(218);
	cout << Obj1.GetItem( ) << endl;

	CFloat Obj2(0.128);					//����һ��CFloat����
	cout << Obj2.GetItem( ) << endl;
	Obj2.SetItem(0.218);
	cout << Obj2.GetItem( ) << endl;

	cin.get();  
}

