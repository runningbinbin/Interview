/*
* @Description: “装饰器模式”标准代码
*/

#include <iostream>

using namespace std;

//抽象构件
class Component
{
public:
	virtual void Operation() = 0;
};

//具体构件
class ConcreateComponent : public Component
{
public:
	void Operation()
	{
		//具体业务
        cout << "ConcreateComponent Operation" << endl;
	}
};

//抽象装饰者
class Decorator : public Component
{
public:
	//注入一个抽象构件类型的对象
	Decorator(Component *component)  
  {
      this->component = component;
  }

public:
    void Operation()
    {
        //其他通用业务。。。
    
        //调用原有的业务方法
        this->component->Operation();
        cout << "Decorator Operation" << endl;
    }

public:
	//维持一个对抽象构件对象的引用
	Component *component;  
};

//具体装饰者A
class ConcreteDecoratorA : public Decorator
{
public:
    ConcreteDecoratorA(Component  *component) : Decorator(component)
    {
        ;
    }

    void Operation()
    {
        //调用原有业务方法
        Decorator::Operation();

        //调用新增业务方法  
        AddedBehavior();  
        cout << "ConcreteDecoratorA Operation" << endl;
    }

    //新增业务方法
    void AddedBehavior()
    {    
        cout << "ConcreteDecoratorA addedBehavior" << endl;;
    }

};

//具体装饰者B
class ConcreteDecoratorB : public Decorator
{
public:
   	ConcreteDecoratorB(Component  *component) : Decorator(component)
   	{
		  ;
   	}

   	void Operation()
   	{
        //调用原有业务方法
        Decorator::Operation();

        //调用新增业务方法  
      	AddedBehavior();  
        cout << "ConcreteDecoratorB Operation" << endl;
   	}

    //新增业务方法
    void AddedBehavior()
    {    
        cout << "ConcreteDecoratorB addedBehavior" << endl;;
	}
};

//客户调用
int main()
{
    Component *base = new ConcreateComponent();
    base->Operation();

    //用“具体装饰者B”装饰“具体构件”，然后再用“具体装饰者A”装饰“具体装饰者B”
    Component *decorator = new ConcreteDecoratorA(new ConcreteDecoratorB(base));
    decorator->Operation();

    return 0;
}
