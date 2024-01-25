
#include<iostream>
using namespace std;

//ǰ����������
class CStack;

//����CNode��ջ��㣩��
class CNode
{           
public:
	CNode( int iData, CNode *preNode )
	{
		m_iData = iData;
		m_preNode = preNode;
	}
	//��CStack������Ϊ��Ԫ�࣬��CStack������г�Ա��������Ϊ�������Ԫ����
	friend class CStack;    
private:
	int m_iData;            	//���ֵ
	CNode *m_preNode;      	//ָ��ǰһ����ָ��
};

//����CStack��ջ����
class CStack
{           
 public:
	CStack ( void )
	{
		m_pTop = 0;
	}
	void Push( int iData );    		//��ջ����
	int Pop( void );           		//��ջ����
private:
	CNode *m_pTop;             	//ͷָ��
};

//��ջ
void CStack::Push ( int iData )              
{
    	CNode *newNode = new CNode( iData, m_pTop ); 
	m_pTop = newNode;
}
//��ջ
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
		cout <<"ջ�ѿգ�" << endl;
		return 0;
	}
}


int main( void )
{
	CStack stack;                  //����һ��ջ�����
	// ��ջ����
	stack.Push(1);
	stack.Push(2);
	stack.Push(3);
	// ��ջ����
	for ( int i = 0; i < 3; i++ )
	{
		cout << stack.Pop( ) << "  ";
	}
	cout << endl;
	return 0;
}
