#include<iostream>
#include<cstring>
using namespace std;

class A
{
private:
	friend class B;
	char *name;
	int age;
public:
	A( char *str, int n )
	{
		name=new char[strlen(str)+1];
		strcpy( name, str );
		age=n;
	}
};
class B
{
public: 
	void show( A x )
	{
		cout<<"ÐÕÃû"<<x.name<<endl;
		cout<<"ÄêÁä "<<x.age<<endl;
	}
};
int main( )	
{
	A a( "×óÁ¦", 19 );
	B b;
	b.show( a );
	return 0;
}

