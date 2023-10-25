#include <iostream>
#include <initializer_list>

class LinkedList {
public:
    class Node {
    public:
        Node() = default;
        explicit Node(double value) {
            this->value = value;
        }
        Node *next{};
        Node *previous{};
        double& getValue();
        void setValue(double);
        friend std::ostream& operator<<(std::ostream& os, Node current) {
            os << current.getValue() << " ";
            return os;
        }
    private:
        double value{};
    };
    LinkedList(std::initializer_list<double> values) {
        for (auto x : values) {
            this->push_back(x);
        }
    }
    LinkedList() = default;
    LinkedList(const LinkedList &preList);
    ~LinkedList();
    void push_back(double x);
    void push_front(double x);
    void pop_back();
    void pop_front();
    double back() const;
    double front() const;
    bool empty() const;
    void clear();
    void show() const;
    int getSize() const;
    void extend(LinkedList preList);
    double& operator[](int x) const;
    double operator<<(Node *n);
private:
    int N{0};
public:
    Node *head{};
    Node *tail{};
};