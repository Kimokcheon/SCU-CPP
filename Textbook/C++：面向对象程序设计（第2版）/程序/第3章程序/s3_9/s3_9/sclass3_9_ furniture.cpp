//��ʵ���ļ���s3_9\sclass3_9.cpp
#include "sclass3_9_ furniture.h"
Furniture::Furniture ( float w )          //���๹�캯��
{
	weight=w;
}
void Furniture::SetWeight( float w)      //��������
{
	weight=w;
	cout<<"�˼Ҿ���"<<weight<<"ǧ��"<<endl;
}
void Bed::Sleep( void ) const           //˯��	
{
	cout<<"��ʼ˯����"<<endl;
}
void Sofa::WatchTV( void ) const              //������	
{
	cout<<"���ڿ����ӡ�"<<endl;
}
void SofaBed::FoldOut( void )             //�۵�
{
	cout<<"�����۵��ʹ򿪡�"<<endl;
}
