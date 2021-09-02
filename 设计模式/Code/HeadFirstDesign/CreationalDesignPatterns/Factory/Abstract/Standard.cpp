/*
* @Description:	“抽象工厂模式”标准代码
*/

#include <iostream>

using namespace std;

//抽象产品创建-抽象产品A
class ProductA
{
public:
	//所有产品类公共方法
	void MethodSame()
	{
		//公共方法实现
		cout << "ProductA 公共方法实现" << endl;
	}

	//抽象业务方法
	virtual void MethodDiff() = 0;
};

//抽象产品B
class ProductB
{
public:
	//所有产品类公共方法
	void MethodSame()
	{
		//公共方法实现
		cout << "ProductB 公共方法实现" << endl;
	}

	//抽象业务方法
	virtual void MethodDiff() = 0;
};

//具体产品创建
//具体产品A1
class ConcreteProductA1 : public ProductA
{
public:
	void MethodDiff()
	{
		cout << "ConcreteProductA1 MethodDiff()" << endl;
	}	
};
//具体产品A2
class ConcreteProductA2 : public ProductA
{
public:
	void MethodDiff()
	{
		cout << "ConcreteProductA2 MethodDiff()" << endl;
	}	
};
//具体产品B1
class ConcreteProductB1 : public ProductB
{
public:
	void MethodDiff()
	{
		cout << "ConcreteProductB1 MethodDiff()" << endl;
	}	
};
//具体产品B2
class ConcreteProductB2 : public ProductB
{
public:
	void MethodDiff()
	{
		cout << "ConcreteProductB2 MethodDiff()" << endl;
	}	
};

//抽象工厂
class Factory
{
public:
	//工厂方法一
	virtual ProductA* CreateProductA() = 0;
	//工厂方法二
	virtual ProductB* CreateProductB() = 0;
};

//具体工厂1
class ConcreteFactory1 : public Factory
{
	ProductA* CreateProductA()
	{
		return new ConcreteProductA1();
	}
	ProductB* CreateProductB()
	{
		return new ConcreteProductB1();
	}
};

//具体工厂2
class ConcreteFactory2 : public Factory
{
	ProductA* CreateProductA()
	{
		return new ConcreteProductA2();
	}
	ProductB* CreateProductB()
	{
		return new ConcreteProductB2();
	}
};


//客户调用
int main()
{
	//用“具体工厂1”创建产品集 “具体产品A1”和“具体产品B1”
	Factory *factory1 = new ConcreteFactory1();
	ProductA *product1 = factory1->CreateProductA();
	product1->MethodDiff();
	ProductB *product2 = factory1->CreateProductB();
	product2->MethodDiff();

	//用“具体工厂1”创建产品集 “具体产品A2”和“具体产品B2”
	Factory *factory2 = new ConcreteFactory2();
	ProductA *product3 = factory2->CreateProductA();
	product3->MethodDiff();
	ProductB *product4 = factory2->CreateProductB();
	product4->MethodDiff();

	return 0;
}