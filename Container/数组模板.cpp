//一个能在任意一种顺序结构数组类中查找值的模板，这个类必须把值储存在最前面 
template<typename ElemType>
ElemType* find(ElemType* first,const ElemType* last,ElemType value)
{
	if((!first)||(!last))return 0;
	
	for(;first!=last;first++){
		if(*first==value)return first; 
	}
	return 0;
}

//增加支持链表结构的查找模板
template<typename iteratorType,typename ElemType>
ElemType* find(iteratorType first,iteratorType last,ElemType value)
{
	if((!first)||(!last))return 0;
	
	for(;first!=last;first++){
		if(*first==value)return first; 
	}
	return 0;
} 
