/*
* @Description: “迭代器模式”标准代码
*/

#include <iostream>

using namespace std;

//聚合对象中的单个元素
class Object
{

};

//抽象迭代器
class Iterator 
{
public:	
	//将游标指向第一个元素
	virtual Object First() = 0; 
	//将游标指向下一个元素
	virtual Object Next() = 0; 
	//判断是否存在下一个元素
	virtual bool HasNext() = 0; 
	//获取游标指向的当前元素
	virtual Object CurrentItem() = 0; 
};

class ConcreteAggregate;

//具体迭代器
class ConcreteIterator : public Iterator 
{
public: 
	ConcreteIterator(ConcreteAggregate *concrete_aggregate) 
	{
		this->concrete_aggregate = concrete_aggregate;
	}
 
	Object First() 
	{
		//游标指向的第一个元素
	}
		
	Object Next() 
	{  
		//游标指向的下一个元素
	}
 
	bool HasNext() 
	{  
		//判断是否存在下一个元素 
	}
	
	Object CurrentItem() 
	{  
		//游标当前指向的元素
	}

private:
	//维持一个对具体聚合对象的引用，以便于访问存储在聚合对象中的数据
	ConcreteAggregate *concrete_aggregate;
	//定义一个游标，用于记录当前访问位置
	int cursor; 
};

//抽象聚合类
class Aggregate 
{
public:	
	virtual Iterator* CreateIterator() = 0;
};

//具体聚合类
class ConcreteAggregate : public  Aggregate 
{	
public: 
	Iterator* CreateIterator() 
	{
		return new ConcreteIterator(this);
    }
};

//客户调用
int main()
{
	Aggregate *aggregate = new ConcreteAggregate();
	Iterator *iter = aggregate->CreateIterator();

	//使用迭代器访问聚合对象中的元素
	while(iter->HasNext())
	{
		Object object = iter->CurrentItem();
	}

	return 0;
}