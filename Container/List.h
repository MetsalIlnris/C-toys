#ifndef LIST_H_
#define LIST_H_

//#include"LinearList.h" 
#include<cstdlib>

//basic type name: Item
template<typename>class List;
template<typename Item>
std::ostream & operator<< (std::ostream & os,const List<Item> & L);


template<typename Item>
struct TreeNode<Item>{
	Item data;
	TreeNode<Item> * link;
};

template<typename Item> 
class List 
{
private:
	int NodeAmount;
protected:
	struct TreeNode<Item> * head;
	struct TreeNode<Item> * rear;
	
public:
	void clear(); //清空链表 
	
	//constructor
	
	List(); 
	List(List & L);//copy constructor 
	~List();//destructor
	
	//member function
	
	bool assign(Item item,int i = 1);//给第i个Node赋值
	bool isempty(){return head == NULL;} //如果list是空的则返回true
//	void insert(); //插入一个元素到list中
	bool pop_back(Item & item); //弹出最后一个元素
	bool pop_front(Item & item); //弹出第一个元素
	bool push_back(Item item); //在list的末尾添加一个元素
	bool push_front(Item item); //在list的头部添加一个元素
	int size() {return NodeAmount;}; //返回list中的元素个数
	
	//advanced member function options
	
	void connect(List<Item> L); //将L深拷贝至末尾 
	void sort(); //给list排序
//	void swap(); //交换两个list
//	void unique(); //删除list中重复的元素
	void reverse(); //把list的元素倒转
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
	head = NULL;
	rear = NULL;
	NodeAmount = 0;
}

template<typename Item>
List<Item>::List(List & L){
	head = NULL;
	rear = NULL;
	if (!L.isempty()) {
		struct TreeNode<Item>* now = L.head;
		while (now!=NULL)
		{
			push_back(now->data);
			now = now->link;
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
	struct TreeNode<Item> * now;
	while (head != NULL) {
		now = head;
		head = head->link;
		delete now;
	}
	rear = NULL;
	NodeAmount = 0;
}



template<typename Item>
bool List<Item>::assign(Item item,int i){
	struct TreeNode<Item> * now = head;
	int cnt = 1; 
	while(now != NULL){
		if(cnt == i){
			now->data = item;
			return 1; 
		}
		now = now->link;
		cnt++;
	}
	return 0;
}

template<typename Item>
bool List<Item>::pop_back(Item & item){
	if(isempty())return false;
	rear = head;
	if (rear->link == NULL) {
		item = rear->data;
		clear();
	}
	while(rear->link->link!=NULL){
		rear = rear->link;
	}
	item=*(rear->link->data);
	delete rear->link;
	rear->link = NULL;
	NodeAmount--;
	return true;
}

template<typename Item>
bool List<Item>::pop_front(Item & item){
	if(isempty())return false;
	NodeAmount--;
	if(head->link == NULL){
		item = head->data;
		clear();
		return true;
	}
	struct TreeNode<Item> * now=head->link;
	item = head->data;
	delete head;
	head = now;
	return true;
}

template<typename Item>
bool List<Item>::push_back(Item item){
	NodeAmount++;
	if(isempty()){
		head = new TreeNode<Item>;
		head->data = item;
		head->link = NULL;
		rear = head;
		return true;
	}
	rear->link = new TreeNode<Item>;
	rear = rear->link;
	rear->link = NULL;
	rear->data = item;
	return true;
}

template<typename Item>
bool List<Item>::push_front(Item item){
	struct TreeNode<Item> * now = new TreeNode<Item>;
	now->Link = head;
	head = now;
	now->link->data = item;
	NodeAmount++;
	return true;
}


//---------------------------------------————————————
//advanced Member function implementation 
//---------------------------------------——————————



template<typename Item>
void List<Item>::connect(List<Item> L){
	Item tem;
	while(L.pop_front(tem)){
		push_back(tem);
	}
}

template<typename Item>
void List<Item>::sort() {
	if (head == rear)return;
	Item tem;
	struct TreeNode<Item>* cur = head->link,* pre = head;
	bool end_Flag = 0;
	while (end_Flag == 0) {
		end_Flag = 1;
		while (cur != NULL) {
			if (cur->data > pre->data) {
				tem = cur->data;
				cur->data = pre->data;
				pre->data = tem;
				end_Flag = 0;
			}
			pre = cur;
			cur = cur->link;
		}
	}
}

template<typename Item>
void List<Item>::reverse() {
	if (head == rear)return;
	rear = head;
	struct TreeNode<Item>* cur = head , * pre = NULL;
	while (head != NULL) {
		cur = head;
		head = head->link;
		cur->link = pre;
		pre = cur;
	}
	head = cur;//不必理会警告;当cur==NULL时对head正常赋值
}

//---------------------------------------
//friend function implementation
//---------------------------------------

template<typename Item>
std::ostream & operator<<(std::ostream & os,const List<Item> & L){
	struct TreeNode<Item> * now;
	for(now = L.head;now != NULL;now = now->link){
		os<<now->data<<std::endl;
	}
	return os;
}



#endif
