
#include<iostream>
using namespace std;

//前向引用声明
class CStack;

//定义CNode（栈结点）类
class CNode
{           
public:
	CNode( int iData, CNode *preNode )
	{
		m_iData = iData;
		m_preNode = preNode;
	}
	//将CStack类声明为友元类，则CStack类的所有成员函数都成为本类的友元函数
	friend class CStack;    
private:
	int m_iData;            	//结点值
	CNode *m_preNode;      	//指向前一结点的指针
};

//定义CStack（栈）类
class CStack
{           
 public:
	CStack ( void )
	{
		m_pTop = 0;
	}
	void Push( int iData );    		//入栈操作
	int Pop( void );           		//出栈操作
private:
	CNode *m_pTop;             	//头指针
};

//入栈
void CStack::Push ( int iData )              
{
    	CNode *newNode = new CNode( iData, m_pTop ); 
	m_pTop = newNode;
}
//出栈
int CStack::Pop( void )
{
	CNode *tempNode = m_pTop;
	if ( m_pTop )
	{
		m_pTop = m_pTop -> m_preNode;
		int tempData = tempNode -> m_iData;
		delete tempNode;
		return tempData;
	}
	else
	{
		cout <<"栈已空！" << endl;
		return 0;
	}
}


int main( void )
{
	CStack stack;                  //建立一个栈类对象
	// 入栈操作
	stack.Push(1);
	stack.Push(2);
	stack.Push(3);
	// 出栈操作
	for ( int i = 0; i < 3; i++ )
	{
		cout << stack.Pop( ) << "  ";
	}
	cout << endl;
	return 0;
}
