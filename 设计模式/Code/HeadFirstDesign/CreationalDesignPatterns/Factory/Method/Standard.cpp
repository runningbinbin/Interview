/*
* @Description:	“工厂方法模式”标准代码
*/

#include <iostream>

using namespace std;

//抽象产品
class Product
{
public:
	//所有产品类公共方法
	void MethodSame()
	{
		//公共方法实现
		cout << "公共方法实现" << endl;
	}

	//抽象业务方法
	virtual void MethodDiff() = 0;
};

//具体产品
//具体产品A
class ConcreteProductA : public Product
{
public:
	void MethodDiff()
	{
		cout << "ConcreteProductA MethodDiff()" << endl;
	}	
};
//具体产品B
class ConcreteProductB : public Product
{
public:
	void MethodDiff()
	{
		cout << "ConcreteProductB MethodDiff()" << endl;
	}	
};

//抽象工厂
class Factory
{
public:
	virtual Product* FactoryMethod() = 0;
};

//具体工厂A
class ConcreteFactoryA : public Factory
{
	Product* FactoryMethod()
	{
		return new ConcreteProductA();
	}
};

//具体工厂B
class ConcreteFactoryB : public Factory
{
	Product* FactoryMethod()
	{
		return new ConcreteProductB();
	}
};

//客户调用
int main()
{
	//创建具体产品A
	Factory *factory1 = new ConcreteFactoryA(); 
	Product *product1 = factory1->FactoryMethod();
	product1->MethodDiff();

	//创建具体产品B
	Factory *factory2 = new ConcreteFactoryB(); 
	Product *product2 = factory2->FactoryMethod();
	product2->MethodDiff();

	return 0;
}
