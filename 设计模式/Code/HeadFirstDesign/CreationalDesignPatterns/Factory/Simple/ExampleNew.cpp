/*
* @Description:	使用“简单工厂模式”的“披萨制作”
*/

#include <stdio.h>
#include <iostream>

using namespace std;


//披萨-抽象产品
class Pizza
{
public:
	Pizza()
	{
		//printf("pizza\n");
	}

public:
	//准备
	void Prepare()
	{
		printf("Prepare...\n");	
	}

	//烘焙
	void Bake()
	{
		printf("Bake...\n");	
	}

	//切片
	void Cut()
	{
		printf("Cut...\n");	
	}

	//包装
	void Box()
	{
		printf("Box...\n");	
	}
};


//奶酪披萨-具体产品
class CheesePizza : public Pizza
{
public:	
	CheesePizza()
	{
		printf("CheesePizza\n");
	}
};
//希腊披萨-具体产品
class GreekPizza : public Pizza
{
public:	
	GreekPizza()
	{
		printf("GreekPizza\n");
	}
};
//意大利腊肉披萨-具体产品
class PepperoniPizza : public Pizza
{
public:	
	PepperoniPizza()
	{
		printf("PepperoniPizza\n");
	}
};

//简单工厂
class SimplePizzaFactory
{
public:
	Pizza* CreatePizza(string type)
	{
		Pizza *pizza = NULL;

		if (type == "cheese")
			pizza = new CheesePizza();
		else if (type == "greek")
			pizza = new GreekPizza();
		else if (type == "pepperoni")
			pizza = new PepperoniPizza();

		return pizza;
	}
};

//客户调用
class PizzaStore
{
public:
	PizzaStore(SimplePizzaFactory *factory)
	{
		this->factory = factory;
	}	

public:
	Pizza OrderPizza(string type)
	{	
		Pizza *pizza;

		/* 变化的部分
		if (type == "cheese")
			pizza = new CheesePizza();
		else if (type == "greek")
			pizza = new GreekPizza();
		else if (type == "pepperoni")
			pizza = new PepperoniPizza();
		*/
		pizza = factory->CreatePizza(type);

		pizza->Prepare();
		pizza->Bake();
		pizza->Cut();
		pizza->Box();	
	}

public:
	SimplePizzaFactory *factory;
};

int main()
{	
	PizzaStore PizzaStore(new SimplePizzaFactory());	
	PizzaStore.OrderPizza("greek");

	return 0;	
}