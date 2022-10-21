#pragma once

#include<cassert>
#include<iostream>
#include<cstdlib>

//basic type name: Item
template<typename>class Queue;
template<typename Item>
std::ostream& operator<< (std::ostream& os, const Queue<Item>& Q);


template<typename Item>
class LinkNode
{
public:
	Item data;
	LinkNode<Item>* link;

	friend class Queue<Item>;
	friend std::ostream& operator<< <Item>(std::ostream& os, const Queue<Item>& Q);
};

template<typename Item>
class Queue
{
protected:
	int NodeAmount;
	LinkNode<Item>* rear;
	LinkNode<Item>* head;

public:
	void clear(); //清空队列

	//constructor

	Queue();
	Queue(Queue& Q);//copy constructor 
	~Queue();//destructor

	//member function

	bool isempty() { return head == NULL; } //如果queue是空的则返回true
	bool pop(); //弹出并删除一个元素
	bool pop(Item& item); //弹出一个元素
	virtual bool push(Item item); //压入一个元素
	int size() { return NodeAmount; }; //返回Queue中的元素个数
	int check_rear() { if (isempty())return 0; return rear->data; };
	int check_head() { if (isempty())return 0; return head->data; };
	//advanced member function options

	void merge(Queue<Item> Q); //将Q融合入queue
//	void swap(); //交换两个queue
//	void unique(); //删除queue中重复的元素
//	void search(); //按指定条件搜索元素
//	void remove(); //从Queue删除元素
//	void remove_if(); //按指定条件删除元素 

	//iterator
//	void begin() //返回指向第一个元素的迭代器
//	void end() //返回末尾的迭代器
//	void rbegin() //返回指向第一个元素的逆向迭代器
//	void rend() //指向Queue末尾的逆向迭代器
//	void get_allocator() //返回Queue的配置器

	//operator overloading

//	Queue & operator+(const Queue & Q);
//	Queue & operator*(double n);

//	friend Queue & operator*(double n,Queue & n);
	friend std::ostream& operator<< <Item>(std::ostream& os, const Queue<Item>& Q);

};

//---------------------------------------
//Member function implementation 
//---------------------------------------

template<typename Item>
Queue<Item>::Queue() {
	rear = NULL;
	head = NULL;
	NodeAmount = 0;
}

template<typename Item>
Queue<Item>::Queue(Queue& Q) {
	rear = NULL;
	head = NULL;
	NodeAmount = Q.NodeAmount;
	if (Q.isempty())return;
	Item tem;
	while (Q.pop(tem))
		push(tem);

}

template<typename Item>
Queue<Item>::~Queue() {
	clear();
}

template<typename Item>
void Queue<Item>::clear() {
	LinkNode<Item>* cur;
	while (head != NULL) {
		cur = head;
		head = head->link;
		delete cur;
	}
	rear = NULL;
	NodeAmount = 0;
}

template<typename Item>
bool Queue<Item>::push(Item item) {
	LinkNode<Item>* tem = rear;
	rear = new LinkNode<Item>;
	if (tem == NULL)head = rear;
	else tem->link = rear;
	rear->data = item;
	rear->link = NULL;
	NodeAmount++;
	return true;
}

template<typename Item>
bool Queue<Item>::pop() {
	if (isempty())return false;
	if (head == rear) {
		clear();
	}
	else {
		LinkNode<Item>* tem = head;
		head = head->link;
		NodeAmount--;
		delete tem;
	}
	return true;
}

template<typename Item>
bool Queue<Item>::pop(Item& item) {
	if (isempty())return false;
	if (head == rear) {
		item = head->data;
		clear();
	}
	else {
		LinkNode<Item>* tem = head;
		head = head->link;
		item = tem->data;
		NodeAmount--;
		delete tem;
	}
	return true;
}

//---------------------------------------————————————
//advanced Member function implementation 
//---------------------------------------——————————



template<typename Item>
void Queue<Item>::merge(Queue<Item> Q) {
	if (Q.isempty())return;
	Item tem;
	NodeAmount += Q.NodeAmount;
	while (Q.pop(tem))
		push(tem);
}


//---------------------------------------
//friend function implementation
//---------------------------------------

template<typename Item>
std::ostream& operator<<(std::ostream& os, const Queue<Item>& Q) {
	LinkNode<Item>* cur;
	for (cur = Q.head; cur != NULL; cur = cur->link) {
		os << cur->data << std::endl;
	}
	return os;
}
