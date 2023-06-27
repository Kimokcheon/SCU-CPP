// �ļ�·����: s2_15\sclass2_15_cpoint.h

#ifndef  _SCLASS2_15_CPOINT_H_
#define __SCLASS2_15_CPOINT_H_

#include <iostream>
using namespace std;

class Point 
{ 
public:
    Point()
	{
		x=0;
		y=0;
		counter++;  //������������ù��캯��ʱ����������ֵ����һ��
	}    	 
    Point( float x, float y )
   	{
        this->x=x;
		this->y=y;
		counter++;    //������������ù��캯��ʱ����������ֵ����һ��
   	}   
	~Point()
	{
		counter--;    //���������������������ʱ����������ֵ�ݼ�һ��
	}  
    void move(float x, float y)
    {       
       	this->x=x;
		this->y=y;
    }
	float getX()
	{
		return x;
	}
	float getY()
	{
		return y;
	}
	static int getCounter()
	{
		return counter;
	}
private:
	float x;  
	float y;
	static int counter;
}; 
int Point::counter=0;    //�������ʼ����̬���ݳ�Աcounter
#endif
