//类声明文件
//文件名：s4_2\sclass4_2_CShape.h 

//编译预处理语句：如果未定义__SCLASS4_2_CSHAPE_H__则定义它，
//直到遇到#endif结束。
#ifndef __SCLASS4_2_CSHAPE_H__ 
#define __SCLASS4_2_CSHAPE_H__ 

#include <iostream>					//包含头文件。使用iostream库

using namespace std;				//使用std命名空间

//声明CShape类      
class CShape  
{
public:
	CShape(double x,				//重心坐标
		double y,					//重心坐标
		double z					//重心坐标
		);
	void Show( ) const;				//显示重心坐标
	//void Output( ) const;			//输出面积
	//double CalculateArea( );		//计算面积

protected:
	double m_x;						//重心坐标
	double m_y;						//重心坐标
	double m_z;						//重心坐标
	double m_area;					//形状的面积
};  

//声明CCircle类   
class CCircle : public CShape		//CCircle类继承CShape类 
{
public:
	CCircle(double x,				//圆的重心坐标
		double y,					//圆的重心坐标
		double z,					//圆的重心坐标
		double radius				//圆的半径
		);
	void Show( ) const;				//显示圆的重心坐标和半径
	//void Output( ) const;			//输出远的面积
	//double CalculateArea( );		//计算圆的面积

protected:
	double m_radius;					//圆的半径
};

#endif								//结束编译预处理
 