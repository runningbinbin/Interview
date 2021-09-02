/*
* @Description: 使用“装饰器模式”设计的咖啡订单系统
*/

#include <stdio.h>
#include <iostream>

using namespace std;
 

//饮料接口-抽象构件
class Beverage
{
public:
	Beverage()
	{
		descripation = "unkown beverage";
	}

public:	
	virtual string GetDescripation()
	{
		return descripation;
	}

	virtual float Cost() = 0;

public:
	string descripation;	
};

//黑咖啡-具体构件
class HouseBlend : public Beverage
{
public:
	HouseBlend()
	{
		this->descripation = "HouseBlend";
	}

public:
	float Cost()
	{
		return 1.1;
	}	
};

//烘焙-具体构件
class DarkRoast : public Beverage
{
public:
	DarkRoast()
	{
		this->descripation = "DarkRoast";
	}

public:
	float Cost()
	{
		return 1.2;
	}
};

//低咖-具体构件
class Decaf : public Beverage
{
public:
	Decaf()
	{
		this->descripation = "Decaf";
	}

public:
	float Cost()
	{
		return 1.3;
	}
};
//浓咖-具体构件
class Espresso : public Beverage
{
public:
	Espresso()
	{
		this->descripation = "Espresso";
	}

public:
	float Cost()
	{
		return 1.4;
	}
};


//调料-抽象装饰者
class CondimentDecorator : public Beverage
{
public:
	CondimentDecorator(Beverage *beverage)
	{
		this->beverage = beverage;
	}

	string GetDescripation()
	{
		return beverage->GetDescripation();
	}

	float Cost()
	{
		return beverage->Cost();
	}

private:
	Beverage *beverage;	
};

//牛奶-具体装饰者
class Milk : public CondimentDecorator
{
public:
	Milk(Beverage *beverage) : CondimentDecorator(beverage)
	{
		;
	}

public:
	string GetDescripation()
	{
		return CondimentDecorator::GetDescripation() + " Milk";
	}

	float Cost()
	{
		return CondimentDecorator::Cost() + 0.1;
	}
public:
	
};

//摩卡-具体装饰者
class Mocha : public CondimentDecorator
{
public:
	Mocha(Beverage *beverage) : CondimentDecorator(beverage)
	{
		;
	}

public:
	string GetDescripation()
	{
		return CondimentDecorator::GetDescripation() + " Mocha";
	}

	float Cost()
	{
		return CondimentDecorator::Cost() + 0.2;
	}
};

//豆浆-具体装饰者
class Soy : public CondimentDecorator
{
public:
	Soy(Beverage *beverage) : CondimentDecorator(beverage)
	{
		;
	}

public:
	string GetDescripation()
	{
		return CondimentDecorator::GetDescripation() + " Soy";
	}

	float Cost()
	{
		return CondimentDecorator::Cost() + 0.3;
	}
};

//奶泡-具体装饰者
class Whip : public CondimentDecorator
{
public:
	Whip(Beverage *beverage) : CondimentDecorator(beverage)
	{
		;
	}

public:
	string GetDescripation()
	{
		return CondimentDecorator::GetDescripation() + " Whip";
	}

	float Cost()
	{
		return CondimentDecorator::Cost() + 0.4;
	}
};


//客户调用
int main()
{
	Beverage *beverage = new Espresso();
	cout << "Espresso: " << beverage->GetDescripation() << ",cost: " << beverage->Cost() << endl;	

	Beverage *beverage2 = new DarkRoast();
	beverage2 = new Mocha(beverage2);
	beverage2 = new Mocha(beverage2);
	beverage2 = new Whip(beverage2);
	cout << "DarkRoast: " << beverage2->GetDescripation() << ",cost: " << beverage2->Cost() << endl;	

	return 0;
}
