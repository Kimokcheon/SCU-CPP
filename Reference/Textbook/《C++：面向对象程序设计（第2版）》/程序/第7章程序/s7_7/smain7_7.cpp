// �ļ�·����:s7_7\smain7_7.cpp
#include <iostream>               	// ����Ԥ��������
#include <fstream>               	// ����Ԥ��������
using namespace std;				// ʹ�������ռ�std 

int main()							// ������main()
{
	int a[] = {1, 5, 8, 10, 18, 98}, n = 6, x;	// �������������ͱ���
	fstream f;						// �����ļ�����
	
	f.open("test.txt", ios::out);	// �������ʽ���ļ�
	if (f.fail())	
	{	// ���ļ�ʧ��
		cout << "���ļ�ʧ��!" << endl;
		exit(1);					// �˳�����
	}
	for (int i = 0; i < n; i++)
		f << a[i] << " ";			// ������ݵ��ļ���
	f.close();						// �ر��ļ�

	f.open("test.txt", ios::in);	// �����뷽ʽ���ļ�
	if (f.fail())	
	{	// ���ļ�ʧ��
		cout << "���ļ�ʧ��!" << endl;
		exit(2);					// �˳�����
	}
	while (!f.eof())
	{
		f >> x;						// ���ļ����������ݵ�x
		cout << x << " ";			// ���x����ʾ��
	}
	cout << endl;					// ����
	f.close();						// �ر��ļ�
	
	system("PAUSE");            	// ���ÿ⺯��system()�����ϵͳ��ʾ
	return 0;                    	// ����ֵ0, ���ز���ϵͳ
}


