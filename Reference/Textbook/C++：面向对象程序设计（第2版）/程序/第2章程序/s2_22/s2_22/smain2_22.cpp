// �ļ�·����: s2_22\smain2_22.cpp
#include<iostream>
using namespace std;
class Point
{
	int x, y;
public:
	Point(int a, int b)
	{
		x=a; 
		y=b;
	}
	void Move( int a, int b)
	{
		x+=a;
		y+=b;
	}
	void Print( )
	{
		cout<<"x="<<x<<"y="<<y<<endl;
	}
};
int main( )
{
	const Point point1( 10,10);  //��������ʼ����������
	point1.Move(2,2);         //������point1�����ݲ��ܱ����ģ����Դ���
	point1.Print( );           //print������thisָ�벻��ָ�򳣶���
	return 0;
}
