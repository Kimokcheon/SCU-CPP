// �ļ�·����: s2_18\smain2_18.cpp
#include<iostream>
using namespace std;
class CSample
{           
 public:	
	CSample( void ){ };                    //�չ��캯��
	void MemberFunc( int a )               //��Ա����
	{
		i=a;
	}
	friend void FriendFunc ( CSample *, int ) ;  //����һ����Ԫ����
private:	
	int i;
};
//��Ԫ����FriendFunc��ʵ��
void FriendFunc ( CSample *p, int a ) 
{
	p->i = a;  
	cout<<"i="<< p->i<<endl;                
}
int main( void )
{
    	CSample *p=new CSample;
	FriendFunc(p , 3); 
    delete p;    
	return 0;   
}
