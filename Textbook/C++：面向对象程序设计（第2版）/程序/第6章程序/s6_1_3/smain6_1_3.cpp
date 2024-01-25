// �ļ�·����:s6_1_3\smain6_1_3.cpp
#include <iostream>            				// ����Ԥ��������
using namespace std;						// ʹ�������ռ�std 

// ��������ģ��
template <class Type>
struct Node 
{
// ���ݳ�Ա:
	Type data;								// ����
	Node<Type> *next;						// ָ��
};

// ����������ģ��
template <class Type>
class Link
{
private:
// ���ݳ�Ա:
	Node<Type> *head;						// ��ͷ
	Node<Type> *tail;						// ��β(Ϊ�˺���ʵ�ֵ���������Ҫ������ָ�����һ��Ԫ
											// �أ����Ǵ�Ԫ�صĺ��棬�˴�����β����ΪNULL)
	Node<Type> *prev;						// ��βǰ��(prev->next == tail), ʵ��ָ�����һ��Ԫ��

public:
// ���к���ģ��:	
	Link()									// ���캯��ģ��
	{ 
		head = prev = tail = NULL;			// ��ʼ��������
	}
	virtual ~Link()							// ��������ģ��
	{ 
		while (head->next != NULL)
		{	// ����ǿ�
			Node<Type> *p = head->next;		// pָ���һ������Ԫ�ؽ��
			head->next = p->next;			// ɾ��p��ָ���
			delete p;						// �ͷ�p��ָ�洢�ռ�
		}
	}				
	void Append(const Type &e)				// ��ĩβ׷��Ԫ��
	{
		Node<Type> *p = new Node<Type>;		// ����洢�ռ�
		p->data = e;						// ����Ԫ��ֵΪe
		p->next = NULL;						// �¼���Ľ����Ϊ��
		if (head == NULL)
		{	// ������
			head = prev = p;				// head��prev�����½��
			tail = p->next;					// tailΪprev�ĺ��(NULL)
		}
		else
		{	// �ǿ�����
			prev->next = p;					// �½��׷����ĩβ
			prev = p;						// pΪ�±�β
			tail = p->next;					// tailΪprev�ĺ��(NULL)
		}
	}
	Node<Type> *Begin()						// ���ؿ�ʼ
	{
		return head;	
	}
	Node<Type> *End()						// ���ؽ���
	{
		return tail;	
	}
};

// ���������������ģ��
template <class Type>
class LinkIterator
{
private:
// ���ݳ�Ա:
	Type *itPtr;							// �����������Ƕ�Type *�ķ�װ
	
public:
// ���к���ģ��:
	LinkIterator(Type *p): itPtr(p) { } 			// ���캯��ģ��
	bool operator != (const LinkIterator &it) const	// ����"!="��ϵ�����
	{
		return this->itPtr != it.itPtr;			// ����ֵ
	}
	void operator++(int)					// ���غ�׺"++"�����
	{
		itPtr = itPtr->next;				// itPtrָ����һԪ��		
	}
	Type operator*()						// ����"*"ָ�������������
	{
		return *itPtr;						// ����itPtrָ���ֵ
	}
};

template <class Type>
ostream &operator<<(ostream &out, const Node<Type> &nd)	// ����"<<"��������
{
	out << nd.data;							// �����������Ԫ��ֵ
	return out;								// ����out
}

template <class It>
void Show(It begin, It end)					// ������ʾ
{
	for (It it = begin; it != end; it++)
	{	// ������ʾ��Ԫ��
		cout << *it << " ";
	}
	cout << endl;							// ����
}

int main()									// ������main()
{
	int a[] = {1, 2, 3, 4, 5, 6};			// ����C����a
	int n = 6;								// Ԫ�ظ���
	Link<int> la;							// �����������
	int i;									// ������ʱ����

	for (i = 0; i < n; i++)
		la.Append(a[i]);					// ��ĩβ׷��Ԫ��

	LinkIterator<Node<int> > begin(la.Begin());	// ����begin
	LinkIterator<Node<int> > end(la.End());		// ����end
	cout << "����Ԫ��:";					// �����ʾ
	Show(begin, end);						// ��ʾ����

	system("PAUSE");						// ���ÿ⺯��system( )�����ϵͳ��ʾ��Ϣ
	return 0;               				// ����ֵ0, ���ز���ϵͳ
}
