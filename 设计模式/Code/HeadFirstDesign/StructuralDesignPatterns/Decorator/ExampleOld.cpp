/*
* @Description: 咖啡订单系统的最初设计
*/

#include <stdio.h>
#include <iostream>

using namespace std;

#define TRANDITION_DESIGN	0	//传统方式，一种饮料不同调料对应不同类，缺点：只要调料不同，就需要定义不同的类，类爆炸
#define IMPROVE_DESIGN		1	//最传统方式的改进，在抽象调料类中，增加所有调料是否加入的开关

#if TRANDITION_DESIGN
//饮料接口
class Beverage
{
public:	
	string GetDescripation()
	{
		return Descripation;
	}

	virtual float Cost() = 0;

protected:
	string Descripation;	
};

//黑咖啡
class HouseBlend : public Beverage
{
public:
	HouseBlend()
	{
		this->Descripation = "HouseBlend";
	}

public:
	float Cost()
	{
		return 1.1;
	}	
};

//烘焙
class DarkRoast : public Beverage
{
public:
	DarkRoast()
	{
		this->Descripation = "DarkRoast";
	}

public:
	float Cost()
	{
		return 1.2;
	}
};

//低咖
class Decaf : public Beverage
{
public:
	Decaf()
	{
		this->Descripation = "Decaf";
	}

public:
	float Cost()
	{
		return 1.3;
	}
};
//浓咖
class Espresso : public Beverage
{
public:
	Espresso()
	{
		this->Descripation = "Espresso";
	}

public:
	float Cost()
	{
		return 1.4;
	}
};
#endif 

#if IMPROVE_DESIGN
//饮料接口
class Beverage
{
public:
	Beverage()
	{
		Milk = false;
		Soy = false;
		Whip = false;
	}

public:	
	string GetDescripation()
	{
		return Descripation;
	}

	void SetMilk()
	{
		this->Milk = true;
	}
	bool HasMilk()
	{
		return Milk;
	}

	void SetSoy()
	{
		this->Soy = true;
	}
	bool HasSoy()
	{
		return Soy;
	}

	void SetWhip()
	{
		this->Whip = true;
	}
	bool HasWhip()
	{
		return Whip;
	}

	float CondimentCost()
	{
		float AllCondimentCost = 0;
		if (HasMilk())
			AllCondimentCost += 0.1;
		if (HasSoy())
			AllCondimentCost += 0.2;
		if(HasWhip())
			AllCondimentCost += 0.3;

		return AllCondimentCost;
	}

public:
	string Descripation;	
	bool Milk;		//牛奶-调料
	bool Soy;		//豆浆-调料
	bool Whip;		//奶泡-调料
};

//黑咖啡
class HouseBlend : public Beverage
{
public:
	HouseBlend()
	{
		this->Descripation = "HouseBlend";
	}

public:
	float Cost()
	{
		return 1.1 + CondimentCost();
	}	
};

//烘焙
class DarkRoast : public Beverage
{
public:
	DarkRoast()
	{
		this->Descripation = "DarkRoast";
	}

public:
	float Cost()
	{
		return 1.2 + CondimentCost();
	}
};

//低咖
class Decaf : public Beverage
{
public:
	Decaf()
	{
		this->Descripation = "Decaf";
	}

public:
	float Cost()
	{
		return 1.3 + CondimentCost();
	}
};
//浓咖
class Espresso : public Beverage
{
public:
	Espresso()
	{
		this->Descripation = "Espresso";
	}

public:
	float Cost()
	{
		return 1.4 + CondimentCost();
	}
};
#endif

int main()
{
	#if TRANDITION_DESIGN
	//缺点：
	//	(1).购买咖啡时，要求添加各种调料，例如：蒸奶、豆浆,按照这个设计只要调料不同，就会定义不同的类，类爆炸!
	Espresso Espresso;
	cout << "Espresso: " << Espresso.GetDescripation() << ",cost: " << Espresso.Cost() << endl;	
	#elif IMPROVE_DESIGN
	//满足添加调料新需求版本
	//	1、缺点：
	//		(1).调料的价格改变会使我们更改现有代码；
	//		(2).一旦新的调料增加，就需要加上新的方法，并改变超类中的cost方法；
	//		(3).后续会开发出新的饮料。对于某些饮料(茶)而言某些调料(奶泡)不合适，但是这个设计方案中，
	//		Tea类仍继承那些不合适的方法，例如：加奶泡(SetWhip());
	//		(4).如果顾客想要双倍摩卡咖啡，怎么办?
	Espresso Espresso;
	cout << "Espresso: " << Espresso.GetDescripation() << ",cost: " << Espresso.Cost() << endl;	
	Espresso.SetSoy();
	Espresso.SetWhip();
	cout << "Espresso: " << Espresso.GetDescripation() << ",cost: " << Espresso.Cost() << endl;	
	#endif

	return 0;
}