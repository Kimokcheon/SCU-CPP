// 文件路径名:s2_15\point.h
#include <iostream>
using namespace std;

class Point 
{ 
public:
    Point()
	{
		x=0;
		y=0;
		counter++;  //当创建对象调用构造函数时，计数器的值递增一个
	}    	 
    Point( float x, float y )
   	{
        this->x=x;
		this->y=y;
		counter++;    //当创建对象调用构造函数时，计数器的值递增一个
   	}   
	~Point()
	{
		counter--;    //当析构对象调用析构函数时，计数器的值递减一个
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

int Point::counter=0;    //在类外初始化静态数据成员counter