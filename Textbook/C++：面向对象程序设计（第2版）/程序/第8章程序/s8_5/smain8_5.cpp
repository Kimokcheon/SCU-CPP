//�ļ�����s8_5\smain8_5.cpp
//�쳣ʾ��

#include <iostream>
#include <string>
using namespace std;

void MyFunc( void );

class CMyException 							//�����쳣��
{
public:
    CMyException(){ };
    ~CMyException(){ };
    const char *ShowExceptionReason() const	//��ʾ�쳣ԭ��
	{ 
		return "CMyException Exception."; 
	}
};

class CDemo				//����һ�������࣬������ʾ��ִ�����쳣�׳���˳��
{
public:
    CDemo();
    ~CDemo();
};

CDemo::CDemo()
{
    cout << "Constructing CDemo." << endl;
}

CDemo::~CDemo()
{
    cout << "Destructing CDemo." << endl;
}

//�쳣Ҳ���Զ���װ�����磺��MyFunC()�з�װthrow��try��catch����
//�����ﲶ������쳣��Ȼ��������ò��ٲ��񱾲㲻�ܲ�����쳣
//��ʵ������ֻ��main()�н������쳣������
void MyFunc()												
{
    CDemo D;
    cout << "\nIn MyFunc(). Throwing CMyException exception." << endl;
    throw CMyException();				//�׳��쳣
}

void main()
{
    try									//��try��װ���ܻ�����쳣�Ĵ���
    {
        cout << "In try block, calling MyFunc()." << endl;
        MyFunc();
    }
    catch( CMyException E )				//һ·���񲢴����쳣
    {
        cout << "Caught: ";
        cout << E.ShowExceptionReason() << endl;
    }
    catch( string str )					//��·���񲢴����쳣
    {
        cout << "Caught some other exception: " << str << endl;
    }

	cin.get();
}

