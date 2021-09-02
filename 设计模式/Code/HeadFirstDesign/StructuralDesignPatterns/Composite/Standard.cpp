/*
* @Description:	“组合模式”标准代码
*/

#include <stdio.h>
#include <iostream>
#include <list>

using namespace std;

//抽象构件
class Component 
{
public:
	//增加成员
	virtual void Add(Component *c) = 0; 

	//删除成员
	virtual void Remove(Component *c) = 0; 

	//获取成员
	virtual Component* GetChild(int i) = 0; 

	//业务方法
	virtual void Operation() = 0;  
};


//叶子构件
class Leaf : public Component 
{
public: 
	void Add(Component *c) 
	{ 
		//异常处理或错误提示 
	}	
		
	void Remove(Component *c) 
	{ 
		//异常处理或错误提示 
	}
	
	Component* GetChild(int i) 
	{ 
		//异常处理或错误提示
		return NULL; 
	}
	
	void Operation() 
	{
		//叶子构件具体业务方法的实现
		cout << "Leaf Operation()" << endl;
	}
};

//容器构件
class Composite : public Component 
{	
public: 
	void Add(Component *c) 
	{
		components.push_back(c);
	}
	
	void Remove(Component *c) 
	{
		components.remove(c);
	}
	
	Component* GetChild(int index) 
	{
		list <Component *>::iterator iter = components.begin();

		for (int i = 0;i < index;i++)
		{
			iter++;	
		}

		return *iter;
	}
	
	void Operation() 
	{
		cout << "Composite Operation()" << endl;	
		//容器构件具体业务方法的实现
        //递归调用成员构件的业务方法
		for(auto &c : components) 
		{
			c->Operation();
		}
	} 	

private:
	list <Component*> components;
};

//客户调用
int main()
{
	//总的构建
	Component *all = new Composite();	
	
	//组合构建
	Component *c = new Composite();	
	
	//叶子
	Component *l = new Leaf();

	c->Add(l);
	
	all->Add(c);

	//递归遍历此构建里面的所有叶子，并调用叶子的Operation()方法
	all->Operation();

	return 0;
}