#pragma once

#include<iostream>
//#include"LinearList.h" 
#include<cstdlib>

//basic type name: Item
template<typename>class List;
template<typename Item>
std::ostream & operator<< (std::ostream & os,const List<Item> & L);


template<typename Item>
struct LinkNode{
	Item data;
	LinkNode<Item>* lLink;
	LinkNode<Item>* rLink;
};

template<typename Item> 
class List 
{
protected:
	struct LinkNode<Item> * head;
	struct LinkNode<Item> * rear;
	int NodeAmount;
	
public:
	void clear(); //清空链表 
	
	//constructor
	
	List(); 
	List(List & L);//copy constructor 
	~List();//destructor
	
	//member function
	
//	bool assign(Item item,int i = 1);//给第i个Node赋值
	bool isempty(){return head == rear;} //如果list是空的则返回true
//	void insert(); //插入一个元素到list中
	bool pop_back();
	bool pop_back(Item & item); //弹出最后一个元素
	bool pop_front();
	bool pop_front(Item & item); //弹出第一个元素
	bool push_back(Item item); //在list的末尾添加一个元素
	bool push_front(Item item); //在list的头部添加一个元素
	int size() {return NodeAmount;}; //返回list中的元素个数
	
	//advanced member function options
	
	void cat(List<Item> L); //将L深拷贝至末尾 
//	void sort(); //给list排序
//	void swap(); //交换两个list
//	void unique(); //删除list中重复的元素
//	void reverse(); //把list的元素倒转
//	void search(); //按指定条件搜索元素
//	void remove(); //从list删除元素
//	void remove_if(); //按指定条件删除元素 
	
	//iterator
//	void begin() //返回指向第一个元素的迭代器
//	void end() //返回末尾的迭代器
//	void rbegin() //返回指向第一个元素的逆向迭代器
//	void rend() //指向list末尾的逆向迭代器
//	void get_allocator() //返回list的配置器
	
	//operator overloading
	
//	List & operator+(const List & L);
//	List & operator*(double n);
	
//	friend List & operator*(double n,List & n);
	friend std::ostream & operator<< <Item>(std::ostream & os,const List<Item> & L);

}; 

//---------------------------------------
//Member function implementation 
//---------------------------------------

template<typename Item>
List<Item>::List(){
	head = new LinkNode<Item>;
	head->data = NULL;
	head->lLink = NULL;
	head->rLink = NULL;
	rear = head;
	NodeAmount = 0;
}

template<typename Item>
List<Item>::List(List & L){
	head = new LinkNode<Item>;
	head->data = NULL;
	head->lLink = NULL;
	head->rLink = NULL;
	rear = head;
	if (!L.isempty()) {
		struct LinkNode<Item>* now = L.head->rLink;
		while (now!=NULL)
		{
			push_back(now->data);
			now = now->rLink;
		}
		
	}
	NodeAmount = L.NodeAmount;
}

template<typename Item>
List<Item>::~List(){
	clear();
}

template<typename Item>
void List<Item>::clear(){
	struct LinkNode<Item> * now;
	while (head != NULL) {
		now = head;
		head = head->rLink;
		delete now;
	}
	rear = NULL;
	NodeAmount = 0;
}

template<typename Item>
bool List<Item>::pop_back() {
	if (isempty())return false;
	rear = rear->lLink;
	rear->rLink = NULL;
	delete rear->rLink;
	NodeAmount--;
	return true;
}

template<typename Item>
bool List<Item>::pop_back(Item & item){
	if (isempty())return false;
	rear = rear->lLink;
	rear->rLink = NULL;
	delete rear->rLink;
	NodeAmount--;
	return true;
}

template<typename Item>
bool List<Item>::pop_front() {
	if (isempty())return false;
	LinkNode<Item>* cur = head->rLink;
	head->rLink = cur->rLink;
	if (cur->rLink != NULL)cur->rLink->lLink = head;
	delete cur;
	NodeAmount--;
	return true;
}

template<typename Item>
bool List<Item>::pop_front(Item & item){
	if (isempty())return false;
	LinkNode<Item>* cur = head->rLink;
	head->rLink = cur->rLink;
	if (cur->rLink != NULL)cur->rLink->lLink = head;
	else rear = head;
	item = cur->data;
	delete cur;
	return true;
}

template<typename Item>
bool List<Item>::push_back(Item item){
	rear->rLink = new LinkNode<Item>;
	rear->rLink->lLink = rear;
	rear = rear->rLink;
	rear->data = item;
	rear->rLink = NULL;
	NodeAmount++;
	return true;
}

template<typename Item>
bool List<Item>::push_front(Item item){
	LinkNode<Item>* cur = head->rLink;
	head->rLink = new LinkNode<Item>;
	head->rLink->lLink = head;
	head->rLink->rLink = cur;
	head->rLink->data = item;
	NodeAmount++;
	return true;
}


//---------------------------------------————————————
//advanced Member function implementation 
//---------------------------------------——————————



template<typename Item>
void List<Item>::cat(List<Item> L){
	Item tem;
	while(L.pop_front(tem)){
		push_back(tem);
	}
}

//---------------------------------------
//friend function implementation
//---------------------------------------

template<typename Item>
std::ostream & operator<<(std::ostream & os,const List<Item> & L){
	struct LinkNode<Item> * cur;
	for(cur = L.head->rLink;cur != NULL;cur = cur->rLink){
		os<<cur->data<<std::endl;
	}
	return os;
}


