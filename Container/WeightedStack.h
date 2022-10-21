#pragma once

#include"Stack.h"

//权重请自己重载class Item的大于号与小于号运算符，这里的权重直接比较Item的data


template<typename Item>
class WeightedStack :public Stack<Item>
{
public:
	//constructor

//	WeightedStack();
//	WeightedStack(Stack<Item>& S);//copy constructor 
//	~WeightedStack();//destructor

	//member function

	virtual bool push(Item item); //压入

};

//---------------------------------------
//Member function implementation 
//---------------------------------------

template<typename Item>
bool WeightedStack<Item>::push(Item item) {
	if (Stack<Item>::isempty()) {
		Stack<Item>::top = new LinkNode<Item>;
		Stack<Item>::bottom = Stack<Item>::top;
		Stack<Item>::top->link = NULL;
		Stack<Item>::top->data = item;
	}
	else {
		LinkNode<Item>* tem = Stack<Item>::top,*pre = NULL;
		while (tem != NULL && tem->data < item) {
			pre = tem;
			tem = tem->link;
		}
		if (pre == NULL) {
			Stack <Item>::top = new LinkNode<Item>;
			Stack <Item>::top->link = tem;
			Stack <Item>::top->data = item;
		}
		else if (tem == NULL) //tem指针抵达链表尾部，item为全链表最大元素
		{
			tem = new LinkNode<Item>;
			tem->link = NULL;
			tem->data = item;
			Stack <Item>::bottom->link = tem;
			Stack <Item>::bottom->link = tem;
			Stack <Item>::bottom = tem;
		}
		else {
			pre->link = new LinkNode<Item>;
			pre = pre->link;
			pre->data = item;
			pre->link = tem;
		}
	}
	Stack<Item>::NodeAmount++;
	return true;
}


//template<typename Item>
//std::ostream& operator<<(std::ostream& os, const Stack<Item>& S) {
//	LinkNode<Item>* cur;
//	for (cur = S.Stack<Item>::top; cur != NULL; cur = cur->link) {
//		os << cur->data << std::endl;
//	}
//	return os;
//}

