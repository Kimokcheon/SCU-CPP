//���ļ�
//�ļ�����s4_2\smain4_2.h

#include "sclass4_2_CShape.h"				//����������ͷ�ļ�

//�������ò���
void Reference(const CShape &roCS)			//�����������Ϊ�β�  
{
	roCS.Show();  
}

//�����Գ���
void main()    
{
	CShape oCS(1.1, 2.0, 3.0);				//����һ��CShape��Ķ���
	CCircle oCC(10.0, 20.1, 30.0, 100.0);	//����һ��CCircle��Ķ���
	Reference(oCS);							//�Ի�����������ò���
	Reference(oCC);							//����������������ò���
	cin.get();								//�ȴ�����������ʵ����ͣ
}
