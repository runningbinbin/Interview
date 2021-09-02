/*
* @Description:	“构建者模式”标准代码
*/

#include <stdio.h>
#include <iostream>

using namespace std;

//产品
class Product
{
public:
	string GetPartA()
	{
		return part_a;
	}
	void SetPartA(string part_a)
	{
		this->part_a = part_a;
	}

	string GetPartB()
	{
		return part_b;
	}
	void SetPartB(string part_b)
	{
		this->part_b = part_b;
	}

	string GetPartC()
	{
		return part_c;
	}
	void SetPartC(string part_c)
	{
		this->part_c = part_c;
	}

private:
	string part_a;		//A成员
	string part_b;		//B成员	
	string part_c;		//C成员
};

//抽象建造者
class Builder
{
public:
	Builder()
	{
		product = new Product();
	}

public:
	virtual void BuildPartA() = 0;
	virtual void BuildPartB() = 0;
	virtual void BuildPartC() = 0;
	Product *GetProduct()
	{
		return product;
	}

protected:
	Product *product;
};


//具体建造者1
class ConcreteBuilder1 : public Builder
{
public:
	void BuildPartA()
	{
		product->SetPartA("A1");
	}
	void BuildPartB()
	{
		product->SetPartB("B1");
	}
	void BuildPartC()
	{
		product->SetPartC("C1");
	}	
};
//具体建造者2
class ConcreteBuilder2 : public Builder
{
public:
	void BuildPartA()
	{
		product->SetPartA("A2");
	}
	void BuildPartB()
	{
		product->SetPartB("B2");
	}
	void BuildPartC()
	{
		product->SetPartC("C2");
	}	
};

//指挥者
class Director
{
public:
	Director(Builder *builder)
	{
		this->builder = builder;
	}
	void SetBuilder(Builder *builder)
	{
		this->builder = builder;
	}

	Product* ConstructProduct()
	{
		builder->BuildPartA();
		builder->BuildPartB();
		builder->BuildPartC();

		return builder->GetProduct();
	} 

private:
	Builder *builder;	
};

//客户调用
int main()
{
	Director *director = new Director(new ConcreteBuilder1());
	Product *product1 = director->ConstructProduct();
	cout << product1->GetPartA() << endl;

	director->SetBuilder(new ConcreteBuilder2());
	Product *product2 = director->ConstructProduct();
	cout << product2->GetPartA() << endl;

	return 0;
}