// �ļ�·����:s2_15\main.cpp
#include "point.h"
int main( ) 
{ 
	Point* p1= new Point( 1, 1);    
	Point *p2= new Point( 1, 3);
    Point* p3= new Point( 3, 3);
   	cout <<"�Ѵ����ĵ����ǣ�"<<Point::getCounter() <<endl; 
    return 0; 
}
