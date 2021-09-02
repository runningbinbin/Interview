/*
* @Description:	“简单工厂模式”标准代码
*/

#include <iostream>

using namespace std;

//抽象产品创建
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

//具体产品创建
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

//工厂类创建
class Factory
{
public:
	//静态工厂方法
	static Product* GetProduct(string arg)
	{
		Product *product = NULL;
		if ("A" == arg)
		{
			product = new ConcreteProductA();
		}
		else if ("B" == arg)
		{
			product = new ConcreteProductB();
		}

		return product;
	}	
};

//客户调用
int main()
{
	//创建工厂对象
	Factory factory;

	//创建“具体产品A”
	Product *product1 = factory.GetProduct("A");
	product1->MethodDiff();

	//创建“具体产品B”
	Product *product2 = factory.GetProduct("B");
	product2->MethodDiff();

	return 0;
}