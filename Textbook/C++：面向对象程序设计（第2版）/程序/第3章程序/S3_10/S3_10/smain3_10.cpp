//�ļ�����s3_10\smain3_10.cpp
#include <iostream>  
using namespace std; 

// �������Base1
class Base1
{
public:
	Base1( void )      //���캯��
	{
		cout <<"class Base1"<<endl;
	}
};

// �������Base2
class Base2
{
public:
	Base2( void )      //���캯��
	{ 
		cout <<"class Base2"<<endl;
	}
};

// ����������Level1��ʹ��ӵ����������Base1��Base2��
// ����ָ��Base1����̳�·����Ϊ�����
class Level1 : public Base2, virtual public Base1
{
public:
	Level1 ( void )      //���캯��
	{
		cout <<"class Level1"<<endl;
	}
};

// ����������Level2
// Level2��Level1ӵ�й�ͬ���������࣬���һ���Base1��Level2�ļ̳�·����ҲΪ�����
class Level2 : public Base2, virtual public Base1
{
public:
	Level2 ( void )      //���캯��
	{
		cout << "class Level2" <<endl;
	}
};

//����������Leaf
//������Level2��Level1��ͬ������Leaf�࣬������Level2Ϊ�����
class Leaf : public Level1, virtual public Level2
{
public:
	Leaf ( void )
	{
		cout << "class Leaf" <<endl;
	}
};

// ���Գ���
int main( void )
{
	Leaf obj;  //����һ��������Leaf�Ķ���
	return 0;
}
