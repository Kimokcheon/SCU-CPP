//���ļ�
//�ļ�����ch4_1\smain4_1.h

#include "sclass4_1_CShape.h"				//����������ͷ�ļ�

//�����Գ���
void main()    
{
	CShape oCS(1.1, 2.0, 3.0);				//����һ��CShape��Ķ���
	CShape *poCS;							//�������CShape��ָ�����
	CCircle oCC(10.0, 20.1, 30.0, 100.0);	//����һ��CCircle��Ķ���
	poCS = & oCS;							//����ָ��ָ��������
	poCS -> Show();							//ͨ������ָ����û����Show( )����
	poCS = & oCC;							//�������ָ��ָ�����������
	poCS -> Show();							//ͨ������ָ������������Show( )����
	cin.get();								//�ȴ�����������ʵ����ͣ  
}