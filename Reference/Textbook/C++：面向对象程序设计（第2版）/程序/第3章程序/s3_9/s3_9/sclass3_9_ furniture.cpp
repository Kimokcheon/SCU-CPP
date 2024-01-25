//类实现文件：s3_9\sclass3_9.cpp
#include "sclass3_9_ furniture.h"
Furniture::Furniture ( float w )          //基类构造函数
{
	weight=w;
}
void Furniture::SetWeight( float w)      //设置重量
{
	weight=w;
	cout<<"此家具重"<<weight<<"千克"<<endl;
}
void Bed::Sleep( void ) const           //睡觉	
{
	cout<<"开始睡觉。"<<endl;
}
void Sofa::WatchTV( void ) const              //看电视	
{
	cout<<"正在看电视。"<<endl;
}
void SofaBed::FoldOut( void )             //折叠
{
	cout<<"可以折叠和打开。"<<endl;
}
