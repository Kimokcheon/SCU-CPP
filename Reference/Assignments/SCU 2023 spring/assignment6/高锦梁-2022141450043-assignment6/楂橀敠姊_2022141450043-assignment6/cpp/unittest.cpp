#include "../h/linkedlist.h"
#include <iostream>
#include <iomanip>
#include "gtest/gtest.h"

namespace {



TEST(assignment6Test, NodeTest) {
    LinkedList::Node n;
    EXPECT_EQ(0, n.getValue());
    LinkedList::Node* pn = new LinkedList::Node(5);
    EXPECT_EQ(5, pn->getValue());
    pn->setValue(10);
    EXPECT_EQ(10, pn->getValue());
    std::cout << n << " " << *pn << std::endl;
    EXPECT_EQ(n.next, nullptr);
    EXPECT_EQ(n.previous, nullptr);
}

TEST(assignment6Test, LinkedListConstructors) {
    LinkedList l1;
    l1.show();      //
    LinkedList l2{3.14, 20, 13, -5, 0, -3.2}; // Help: initializer list
    l2.show();      // 3.14 20 13 -5 0 -3.2
}

TEST(assignment6Test, LinkedListCopyConstructor) {
    LinkedList l1{1, 2, 3, 4, 5, 6, 7, 8, 9};
    LinkedList l2{l1};
    LinkedList::Node* n1 = l1.head;
    LinkedList::Node* n2 = l2.head;

    for(size_t i = 0 ; i < 9 ; i++) {
        EXPECT_EQ(false, n1 == n2);
        n1 = n1->next;
        n2 = n2->next;
    }
    l1.push_back(10);
    l2.push_front(0);
    l1.show();      // 1 2 3 4 5 6 7 8 9 10
    l2.show();      // 0 1 2 3 4 5 6 7 8 9
}

TEST(assignment6Test, LinkedListPush) {
    LinkedList l1;
    l1.push_back(1);
    l1.push_back(2);
    l1.push_front(0);
    l1.push_back(3);
    l1.push_back(4);
    l1.show();      // 0 1 2 3 4

    LinkedList l2;
    l2.push_front(3);
    l2.push_back(4);
    l2.push_front(2);
    l2.push_front(1);
    l2.push_front(0);
    l2.show();      // 0 1 2 3 4

    LinkedList l3{-4, -3, -2, -1, 0};
    l3.push_back(1);
    l3.push_front(-5);
    l3.push_front(-6);
    l3.push_back(2);
    l3.push_front(-7);
    l3.push_back(3);
    l3.show();      // -7 -6 -5 -4 -3 -2 -1 0 1 2 3
}

TEST(assignment6Test, LinkedListPop) {
    LinkedList l1;
    EXPECT_THROW(l1.pop_back(), std::logic_error);
    EXPECT_THROW(l1.pop_front(), std::logic_error);

    LinkedList l2{1, 2, 3, 4, 5, 6, 7, 8, 9};
    l2.pop_back();
    l2.pop_back();
    l2.pop_front();
    l2.pop_back();
    l2.show();      // 2 3 4 5 6

    LinkedList l3{1, 2, 3, 4, 5, 6, 7, 8, 9};
    l3.pop_front();
    l3.pop_front();
    l3.pop_back();
    l3.pop_front();
    l3.show();      // 4 5 6 7 8
}

TEST(assignment6Test, LinkedListSides) {
    LinkedList l1;
    EXPECT_THROW(l1.back(), std::logic_error);
    EXPECT_THROW(l1.front(), std::logic_error);

    LinkedList l2{1, 2, 3, 4, 5, 6, 7, 8, 9};
    EXPECT_EQ(l2.back(), 9);
    EXPECT_EQ(l2.front(), 1);
    l2.pop_back();
    EXPECT_EQ(l2.back(), 8);
    EXPECT_EQ(l2.front(), 1);
    l2.pop_front();
    EXPECT_EQ(l2.back(), 8);
    EXPECT_EQ(l2.front(), 2);
    l2.pop_back();
    EXPECT_EQ(l2.back(), 7);
    EXPECT_EQ(l2.front(), 2);
}

TEST(assignment6Test, LinkedListExtend) {
    LinkedList l1;
    LinkedList l2;
    l1.extend(l2);
    l1.show();      //
    l2.show();      //

    LinkedList l3;
    LinkedList l4{1, 2, 3, 4, 5, 6, 7, 8, 9};
    l3.extend(l4);
    l3.show();      // 1 2 3 4 5 6 7 8 9
    l4.show();      // 1 2 3 4 5 6 7 8 9

    LinkedList l5{1, 2, 3, 4, 5, 6, 7, 8, 9};
    LinkedList l6;
    l5.extend(l6);
    l5.show();      // 1 2 3 4 5 6 7 8 9
    l6.show();      //

    LinkedList l7{1, 2, 3, 4, 5, 6, 7, 8, 9};
    LinkedList l8{10, 11, 12, 13, 14};
    l7.extend(l8);
    l7.show();      // 1 2 3 4 5 6 7 8 9 10 11 12 13 14
    l8.show();      // 10 11 12 13 14
}

TEST(assignment6Test, LinkedListBracket) {
    LinkedList l1;
    EXPECT_THROW(l1[0], std::logic_error);
    EXPECT_THROW(l1[-5], std::logic_error);

    LinkedList l2{1, 2, 3, 4, 5, 6, 7, 8, 9};
    EXPECT_EQ(l2[3], 4);
    for (size_t i = 0; i < 9 ; i++)
        l2[i] = i * i;
    for (size_t i = 0; i < 9 ; i++)
        EXPECT_EQ(l2[i], i * i);
    l2.show();      // 0 1 4 9 16 25 36 49 64
}

TEST(assignment6Test, LinkedListMainNodes) {
    LinkedList l2{1, 2, 3, 4, 5, 6, 7, 8, 9};
    EXPECT_EQ(l2.tail->getValue(), 9);
    EXPECT_EQ(l2.head->getValue(), 1);
    l2.pop_back();
    EXPECT_EQ(l2.tail->getValue(), 8);
    EXPECT_EQ(l2.head->getValue(), 1);
    l2.pop_front();
    EXPECT_EQ(l2.tail->getValue(), 8);
    EXPECT_EQ(l2.head->getValue(), 2);
    l2.pop_back();
    EXPECT_EQ(l2.tail->getValue(), 7);
    EXPECT_EQ(l2.head->getValue(), 2);
}

TEST(assignment6Test, LinkedListOthers) {
    LinkedList l1;
    EXPECT_EQ(l1.getSize(), 0);
    EXPECT_EQ(l1.empty(), true);
    l1.clear();
    l1.clear();

    LinkedList l2{1, 2, 3, 4, 5, 6, 7, 8, 9};
    EXPECT_EQ(l2.getSize(), 9);
    EXPECT_EQ(l2.empty(), false);
    l2.clear();
    l2.clear();
    EXPECT_EQ(l2.getSize(), 0);
    EXPECT_EQ(l2.empty(), true);
}
}
