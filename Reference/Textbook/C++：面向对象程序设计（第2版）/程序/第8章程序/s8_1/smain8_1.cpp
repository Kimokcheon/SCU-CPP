//�ļ�����s8_1\smain8_1.cpp
//new��delete��ʹ��

#include <iostream>
#include <string>
using namespace std;
const int LEN = 5;					//����һ������

class CNode							//����CNode��
{
public:
	CNode( int value=0 );			//���캯����ȱʡ����value=0
	void Print( ) const;

private:
	int m_value;					//�ڵ�ֵ
};

CNode::CNode( int value ) : m_value( value )	//���캯��
{
	;
}

void CNode::Print( ) const			//��ʾ������Ա����
{ 
	cout<< "CNode value : " << m_value << endl; 
}

//���Ժ�����
void main( )
{
	CNode *poCN1 = new CNode[LEN];	//�����������飬�Զ�����ȱʡ���޲ι��캯��
	if ( poCN1 == NULL )				//�ж϶�̬�ڴ������Ƿ�ɹ���
	{
		exit(0);					//�ڴ����벻�ɹ�,���˳�
	}
	delete [ ]poCN1;					//�ͷŶ������飬ȥ��[ ]���齫�ͷŲ���ȫ
	poCN1 = NULL;					//��poCNָ��ָ��NULL����������Ȼָ��ԭ��̬�ռ�

	CNode *poCN2 = new CNode( 5 );
	if ( poCN2 == NULL )				//�ж϶�̬�ڴ������Ƿ�ɹ�
	{
		exit(0);
	}
	delete poCN2;					//�ͷŵ�������
	poCN2 = NULL;


	int *p1, *p2,(*p3)[3];			//p1��p2һ������ָ�룬p3��ָ��
	p1 = new int;					//newһ������
	p2 = new int (200);				//newһ�����������ֵΪ200.
	p3 = new int[2][3];	//newһ������һά��������飨Ԫ�ؾ�����������Ԫ�ص�һά���飩
	delete p1;						//�ͷ�һ��int����
	delete p2;						//�ͷ�һ��int����
	delete []p3;					//�ͷ�һ������һά���������
	p1 = NULL;
	p2 = NULL;
	p3 = NULL;
	//......

	//oCP1, oCP2Ϊ�ڶ�ջ��ע�ⲻ�Ƕѣ��з���Ķ�������delete��ϵͳ�Զ��ͷš�
	CNode oCP1( 1 );		//����һ����󣬾��Ƕ����������ֵ���Ըı�
	const CNode oCP2( 3);	//����һ�������󡣶���������ֵ���ɸı�
}
