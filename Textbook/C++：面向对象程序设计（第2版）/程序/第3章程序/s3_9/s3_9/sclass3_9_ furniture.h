//类声明文件：s3_9\sclass3_9_ furniture.h
#ifndef _SCLASS_3_9_FURNITURE_H
#define _SCLASS_3_9_FURNITURE _H
#include <iostream>  
using namespace std; 

// 声明公共基类
class Furniture 
{
public:
	Furniture ( float w ) ;            
	void SetWeight( float w) ;            //设置重量
protected:
	float weight;                         //重量
};

class Bed : virtual public Furniture      //将公共基类声明为虚基类
{
public:
	Bed ( float w ): Furniture( w ) {}    //一级派生类构造函数，负责初始化公共基类的数据成员
	void Sleep( void ) const;              //睡觉		
};

class Sofa:  virtual public Furniture     //在定义一级派生类时必须将公共基类声明为虚基类
{
public:
	Sofa ( float w ): Furniture( w ) {}   //一级派生类构造函数，负责初始化公共基类的数据成员
	void WatchTV( void ) const;           //看电视		
};

class SofaBed : public Sofa, public Bed  
{
public:
//派生类构造函数的一个参数用来初始化3个基类的数据成员
	SofaBed ( float w ): Furniture(w), Sofa(w), Bed(w) {}    
	void FoldOut( void )  ;                //折叠
};
#endif
