/*
* @Description:	使用“工厂方法模式”的“不同地区同款披萨不同风味的披萨制作”
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
 

//纽约-奶酪披萨-具体产品
class NYCheesePizza : public Pizza
{
public:	
	NYCheesePizza()
	{
		printf("NYCheesePizza\n");
	}
};
//纽约-希腊披萨-具体产品
class NYGreekPizza : public Pizza
{
public:	
	NYGreekPizza()
	{
		printf("NYGreekPizza\n");
	}
};
//纽约-意大利腊肉披萨-具体产品
class NYPepperoniPizza : public Pizza
{
public:	
	NYPepperoniPizza()
	{
		printf("NYPepperoniPizza\n");
	}
};

//芝加哥-奶酪披萨-具体产品
class ChicagoCheesePizza : public Pizza
{
public:	
	ChicagoCheesePizza()
	{
		printf("ChicagoCheesePizza\n");
	}
};
//芝加哥-希腊披萨-具体产品
class ChicagoGreekPizza : public Pizza
{
public:	
	ChicagoGreekPizza()
	{
		printf("ChicagoGreekPizza\n");
	}
};
//芝加哥-意大利腊肉披萨-具体产品
class ChicagoPepperoniPizza : public Pizza
{
public:	
	ChicagoPepperoniPizza()
	{
		printf("ChicagoPepperoniPizza\n");
	}
};


//抽象工厂
class PizzaStore
{
public:
	//每个子类都会实现CreatePizza，同时使用PizzaStore的OrderPizza的方法
	void OrderPizza(string type)
	{	
		Pizza *pizza = NULL;
		pizza = CreatePizza(type);
		pizza->Prepare();
		pizza->Bake();
		pizza->Cut();
		pizza->Box();	
	}

	//一个方法， 功能类似工厂，故称 工厂方法
	virtual Pizza* CreatePizza(string type) = 0;
};

//纽约披萨店-具体工厂
class NYPizzaStore : public PizzaStore
{
	 Pizza* CreatePizza(string type)
	 {
	 	Pizza *pizza = NULL;
	
	 	if (type == "cheese")
			pizza = new NYCheesePizza();
		else if (type == "greek")
			pizza = new NYGreekPizza();
		else if (type == "pepperoni")
			pizza = new NYPepperoniPizza();

		return pizza;
	 }
};

//芝加哥披萨店-具体工厂
class ChicagoPizzaStore : public PizzaStore
{
	 Pizza* CreatePizza(string type)
	 {
	 	Pizza *pizza = NULL;

		if (type == "cheese")
			pizza = new ChicagoCheesePizza();
		else if (type == "greek")
			pizza = new ChicagoGreekPizza();
		else if (type == "pepperoni")
			pizza = new ChicagoPepperoniPizza();

		return pizza;
	 }
};

//客户调用
int main()
{
	/*工厂方法优点：
		(1).将披萨制作活动局限于PizzaStore类，，而同时又能让这些加盟店可以自由的制作该区域的风味;
		(2).将产品的“实现” 从 “使用”中解耦，如果增加或者改变产品的实现，使用者不会受到影响。*/
	PizzaStore *nyStore = new NYPizzaStore();
	nyStore->OrderPizza("cheese");

	PizzaStore *chicagoStore = new ChicagoPizzaStore();
	chicagoStore->OrderPizza("cheese");

	return 0;
}