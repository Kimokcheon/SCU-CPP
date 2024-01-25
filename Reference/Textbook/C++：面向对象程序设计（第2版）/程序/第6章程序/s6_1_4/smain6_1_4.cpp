// 文件路径名:s6_1_4\smain6_1_4.cpp
#include <iostream>            				// 编译预处理命令
using namespace std;						// 便用命名空间std 

// 定义链表类模板
template <class Type>
class Link
{
public:
// 定义内嵌类模板
	// 定义内嵌结点类模板
	struct Node 
	{
	// 数据成员:
		Type data;							// 数据
		Node *next;							// 指针
	};

	// 定义内嵌链表迭代器类模板
	class LinkIterator
	{
	private:
	// 数据成员:
		Node *itPtr;						// 迭代器本质是对Node *的封装
		
	public:
	// 公有函数模板:
		LinkIterator(Node *p): itPtr(p) { } 			// 构造函数模板
		bool operator != (const LinkIterator &it) const	// 重载"!="关系运算符
		{
			return this->itPtr != it.itPtr;	// 返回值
		}
		void operator++(int)				// 重载后缀"++"运算符
		{
			itPtr = itPtr->next;			// itPtr指向下一元素		
		}
		Node operator*()					// 重载"*"指针间接引用运算符
		{
			return *itPtr;					// 返回itPtr指向的值
		}
	};

public:
// 公有函数模板	

	Link()									// 构造函数模板
	{ 
		head = prev = tail = NULL;			// 初始化空链表
	}
	virtual ~Link()							// 析构函数模板
	{ 
		while (head->next != NULL)
		{	// 链表非空
			Node *p = head->next;			// p指向第一个链表元素结点
			head->next = p->next;			// 删除p所指结点
			delete p;						// 释放p所指存储空间
		}
	}				
	void Append(const Type &e)				// 向末尾追加元素
	{
		Node *p = new Node;					// 分配存储空间
		p->data = e;						// 数据元素值为e
		p->next = NULL;						// 新加入的结点后继为空
		if (head == NULL)
		{	// 空链表
			head = prev = p;				// head与p都向新结点
			tail = p->next;					// tail为prev的后继(NULL)
		}
		else
		{	// 非空链表
			prev->next = p;					// 新结点追加在末尾
			prev = p;						// p为新表尾
			tail = p->next;					// tail为prev的后继(NULL)
		}
	}
	Node *Begin()							// 返回开始
	{
		return head;	
	}
	Node *End()								// 返回结束
	{
		return tail;	
	}

private:
// 数据成员:
	Node *head;								// 表头
	Node *tail;								// 表尾(为了后面实现迭代器的需要，不是指向最后一个元
											// 素，而是此元素的后面，此处将表尾定义为NULL)
	Node *prev;								// 表尾前驱(prev->next == tail)
};

template <class Type>
ostream &operator<<(ostream &out, const Link<Type>::Node &nd)	// 重载"<<"输出运算符
{
	out << nd.data;							// 输出结点的数据元素值
	return out;								// 返回out
}

template <class It>
void Show(It begin, It end)					// 泛型显示
{
	for (It it = begin; it != end; it++)
	{	// 依次显示各元素
		cout << *it << " ";
	}
	cout << endl;							// 换行
}

int main()									// 主函数main()
{
	int a[] = {1, 2, 3, 4, 5, 6};			// 定义C数组a
	int n = 6;								// 元素个数
	Link<int> la;							// 定义链表对象
	int i;									// 定义临时变量

	for (i = 0; i < n; i++)
		la.Append(a[i]);					// 向末尾追加元素

	Link<int>::LinkIterator begin(la.Begin());	// 定义begin
	Link<int>::LinkIterator end(la.End());		// 定义end
	cout << "链表元素:";					// 输出提示
	Show(begin, end);						// 显示链表

	system("PAUSE");						// 调用库函数system( )，输出系统提示信息
	return 0;               				// 返回值0, 返回操作系统
}
