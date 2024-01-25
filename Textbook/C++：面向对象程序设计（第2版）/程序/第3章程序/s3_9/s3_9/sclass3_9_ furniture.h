//�������ļ���s3_9\sclass3_9_ furniture.h
#ifndef _SCLASS_3_9_FURNITURE_H
#define _SCLASS_3_9_FURNITURE _H
#include <iostream>  
using namespace std; 

// ������������
class Furniture 
{
public:
	Furniture ( float w ) ;            
	void SetWeight( float w) ;            //��������
protected:
	float weight;                         //����
};

class Bed : virtual public Furniture      //��������������Ϊ�����
{
public:
	Bed ( float w ): Furniture( w ) {}    //һ�������๹�캯���������ʼ��������������ݳ�Ա
	void Sleep( void ) const;              //˯��		
};

class Sofa:  virtual public Furniture     //�ڶ���һ��������ʱ���뽫������������Ϊ�����
{
public:
	Sofa ( float w ): Furniture( w ) {}   //һ�������๹�캯���������ʼ��������������ݳ�Ա
	void WatchTV( void ) const;           //������		
};

class SofaBed : public Sofa, public Bed  
{
public:
//�����๹�캯����һ������������ʼ��3����������ݳ�Ա
	SofaBed ( float w ): Furniture(w), Sofa(w), Bed(w) {}    
	void FoldOut( void )  ;                //�۵�
};
#endif
