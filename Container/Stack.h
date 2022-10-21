#pragma once

#include<cstdlib>
#include<iostream>

//basic type name: Item
template<typename>class Stack;
template<typename Item> 
std::ostream& operator<< (std::ostream& os, const Stack<Item>& S);


template<typename Item> 
class LinkNode
{
public:
	Item data;
	LinkNode<Item>* link;

	friend class Stack<Item>;
	friend std::ostream& operator<< <Item>(std::ostream& os, const Stack<Item>& S);
};

template<typename Item> 
class Stack
{
protected:
	int NodeAmount;
	LinkNode<Item>* bottom;
	LinkNode<Item>* top;

public:
	void clear(); //清空栈

	//constructor

	Stack();
	Stack(Stack& S);//copy constructor 
	~Stack();//destructor

	//member function

//	bool assign(Item item,int i = 1);//给第i个Node赋值
	bool isempty() { return top == NULL; } //如果stack是空的则返回true
	bool pop(); //弹出并删除一个元素
	bool pop(Item& item); //弹出一个元素
	virtual bool push(Item item); //压入一个元素
	int size() { return NodeAmount; }; //返回Stack中的元素个数

	//advanced member function options

	void merge(Stack<Item> S); //将S融合入stack
//	void swap(); //交换两个stack
//	void unique(); //删除stack中重复的元素
//	void search(); //按指定条件搜索元素
//	void remove(); //从Stack删除元素
//	void remove_if(); //按指定条件删除元素 

	//iterator
//	void begin() //返回指向第一个元素的迭代器
//	void end() //返回末尾的迭代器
//	void rbegin() //返回指向第一个元素的逆向迭代器
//	void rend() //指向Stack末尾的逆向迭代器
//	void get_allocator() //返回Stack的配置器

	//operator overloading

//	Stack & operator+(const Stack & S);
//	Stack & operator*(double n);

//	friend Stack & operator*(double n,Stack & n);
	friend std::ostream& operator<< <Item>(std::ostream& os, const Stack<Item>& S);

};

//---------------------------------------
//Member function implementation 
//---------------------------------------

template<typename Item> 
Stack<Item>::Stack() {
	bottom = NULL;
	top = NULL;
	NodeAmount = 0;
}

template<typename Item> 
Stack<Item>::Stack(Stack& S) {
	bottom = NULL;
	top = NULL;
	NodeAmount = S.NodeAmount;
	if (S.isempty())return;
	Item tem;
	while(S.pop(tem))
		push(tem);

}

template<typename Item> 
Stack<Item>::~Stack() {
	clear();
}

template<typename Item> 
void Stack<Item>::clear() {
	 LinkNode<Item>* cur;
	while (top != NULL) {
		cur = top;
		top = top->link;
		delete cur;
	}
	bottom = NULL;
	NodeAmount = 0;
}

template<typename Item>
bool Stack<Item>::push(Item item) {
	LinkNode<Item>* tem = top;
	top = new LinkNode<Item>;
	if (tem == NULL)bottom = top;
	top->link = tem;
	top->data = item;
	NodeAmount++;
	return true;
}

template<typename Item>
bool Stack<Item>::pop() {
	if (isempty())return false;
	if (top == bottom) {
		clear();
	}
	else {
		LinkNode<Item>* tem = top;
		top = top->link;
		NodeAmount--;
		delete tem;
	}
	return true;
}

template<typename Item>
bool Stack<Item>::pop(Item& item) {
	if (isempty())return false;
	if (top == bottom) {
		item = top->data;
		clear();
	}
	else {
		LinkNode<Item>* tem = top;
		top = top->link;
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
void Stack<Item>::merge(Stack<Item> S) {
	if (S.isempty())return;
	Item tem;
	NodeAmount += S.NodeAmount;
	while (S.pop(tem))
		push(tem);
}


//---------------------------------------
//friend function implementation
//---------------------------------------

template<typename Item> 
std::ostream& operator<<(std::ostream& os, const Stack<Item>& S) {
	 LinkNode<Item>* cur;
	for (cur = S.top; cur != NULL; cur = cur->link) {
		os << cur->data << std::endl;
	}
	return os;
}



