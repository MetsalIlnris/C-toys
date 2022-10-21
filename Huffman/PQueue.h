#pragma once


/*以顺序结构构造优先级队列
优先级采用<和>判断
请在Item数据类型中重载好优先级的比较符号*/

#include<cstdlib>
#include<iostream>

#define DefaultSize 300;

//basic type name: Item
template<typename>class PQueue;
template<typename Item> 
std::ostream& operator<< (std::ostream& os, const PQueue<Item>& PQ);

template<typename Item> 
class PQueue
{
protected:
	Item* PQElem;
	int currentSize; //当前元素数量
	int maxSize;		 //元素容量

public:
	void clear() { currentSize = 0; } //清空队列

	//constructor

	PQueue(int sz = 300);
	PQueue(PQueue& PQ);//copy constructor 
	~PQueue() { delete[] PQElem; };//destructor

	//member function

	bool isempty() { return currentSize; } //如果queue是空的则返回true
	bool isfull() { return currentSize == maxSize; } //如果queue是满的则返回true
	bool pop(); //弹出并删除一个元素
	bool pop(Item& item); //弹出一个元素
	virtual bool push(Item item); //压入一个元素
	int size() { return currentSize; }; //返回PQueue中的元素个数
	Item check_head() {  return PQElem[0]; };

	//operator overloading

	friend std::ostream& operator<< <Item>(std::ostream& os, const PQueue<Item>& PQ);

};

//---------------------------------------
//Member function implementation 
//---------------------------------------

template<typename Item> 
PQueue<Item>::PQueue(int sz) {
	maxSize = sz;
	PQElem = new Item[sz];
	currentSize = 0;
}

template<typename Item> 
PQueue<Item>::PQueue(PQueue& PQ) {
	delete[] PQElem;
	maxSize = PQ.maxSize;
	PQElem = new Item[PQ.maxSize];
	currentSize = 0;
}

template<typename Item>
bool PQueue<Item>::push(Item item) {
	if (!isfull()) {
		int i, k;
		for (i = 0; i < currentSize; i++) {
			if (PQElem[i] < item)break;
		}
		for (k = currentSize - 1; k >= i;k--) {
			PQElem[k + 1] = PQElem[k];
		}
		PQElem[i] = item;
		currentSize++;
		return true;
	}
	else return false;
}

template<typename Item>
bool PQueue<Item>::pop() {
	if (currentSize == 0)return false;
	else {
		for (int i = 0; i < currentSize; i++) {
			PQElem[i] = PQElem[i + 1];
		}
		currentSize--;
	}
	return true;
}

template<typename Item>
bool PQueue<Item>::pop(Item& item) {
	if (currentSize == 0)return false;
	else {
		item = PQElem[--currentSize];
		for (int i = 0; i < currentSize; i++) {
			PQElem[i] = PQElem[i + 1];
		}
	}
	return true;
}

//---------------------------------------
//friend function implementation
//---------------------------------------

template<typename Item> 
std::ostream& operator<<(std::ostream& os, const PQueue<Item>& PQ) {
	for (int i = 0; i < PQ.currentSize; i++) {
		os << PQ.PQElem[i] << ' ';
	}
	return os;
}



