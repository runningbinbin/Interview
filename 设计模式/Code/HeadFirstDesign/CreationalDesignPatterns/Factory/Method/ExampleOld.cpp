/*
* @Description:	使用“简单工厂模式”的“不同地区同款披萨不同风味的披萨制作”
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

//纽约披萨工厂-简单工厂
class NYPizzaFactory
{
public:
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

//芝加哥披萨工厂-简单工厂
class ChicagoPizzaFactory
{
public:
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
class NYPizzaStore
{
public:
	NYPizzaStore(NYPizzaFactory *factory)
	{
		this->factory = factory;
	}	

public:
	Pizza OrderPizza(string type)
	{	
		Pizza *pizza;
		pizza = factory->CreatePizza(type);

		pizza->Prepare();
		pizza->Bake();
		//直接不切片
		//pizza->Cut();
		pizza->Box();	
	}

public:
	NYPizzaFactory *factory;
};

//客户调用
class ChicagoPizzaStore
{
public:
	ChicagoPizzaStore(ChicagoPizzaFactory *factory)
	{
		this->factory = factory;
	}	

	//其他厂商打包盒打包
	void BoxOther() 
	{
		printf("BoxOther...\n");
	}

public:
	Pizza OrderPizza(string type)
	{	
		Pizza *pizza;
		pizza = factory->CreatePizza(type);

		pizza->Prepare();
		pizza->Bake();
		pizza->Cut();
		//用其他厂商打包盒打包
		BoxOther();	
	}

public:
	ChicagoPizzaFactory *factory;
};

 

int main()
{
	/* 背景：不同地区的披萨加盟店，需要提供不同风味的披萨 */
	NYPizzaStore *nyStore = new NYPizzaStore(new NYPizzaFactory());
	nyStore->OrderPizza("cheese");

	ChicagoPizzaStore *chicagoStore = new ChicagoPizzaStore(new ChicagoPizzaFactory());
	chicagoStore->OrderPizza("cheese");

	return 0;
}