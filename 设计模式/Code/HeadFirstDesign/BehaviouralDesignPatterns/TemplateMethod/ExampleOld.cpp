/*
* @Description: 冲茶冲咖啡软件最初设计
*/
#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;

#define FIRST_DESIGN		0		//第一次设计
#define SECOND_DESIGN		1		//第二次设计

#if FIRST_DESIGN
//咖啡冲泡法
//	(1).把水煮沸
//	(2).用沸水冲泡咖啡
//	(3).把咖啡倒进杯子
//	(4).加糖和牛奶
class Coffee
{
public:
	void BoilWater()
	{
		cout << "boiling water" << endl;
	}	

	void BrewCoffeeGrinds()
	{
		cout << "dripping coffee through filter" << endl;
	}
	void PourInCup()
	{
		cout << "pouring into cup" << endl;
	}
	void AddSugarAndMilk()
	{
		cout << "adding sugar and milk" << endl;
	}

	void PrepareRecipe()
	{
		this->BoilWater();
		this->BrewCoffeeGrinds();
		this->PourInCup();
		this->AddSugarAndMilk();
	}
};

//c茶叶冲泡法
//	(1).把水煮沸
//	(2).用沸水浸泡茶叶
//	(3).把茶倒进杯子
//	(4).加柠檬
class Tea
{
public:
	void BoilWater()
	{
		cout << "boiling water" << endl;
	}	

	void SteepTeaBag()
	{
		cout << "steeping the tea" << endl;
	}
	void PourInCup()
	{
		cout << "pouring into cup" << endl;
	}
	void AddLemon()
	{
		cout << "adding lemon" << endl;
	}

	void PrepareRecipe()
	{
		this->BoilWater();
		this->SteepTeaBag();
		this->PourInCup();
		this->AddLemon();
	}
};
#endif 

#if SECOND_DESIGN
//把一样的方法提取到抽象类
class CaffeineBeverage
{
public:
	void BoilWater()
	{
		cout << "boiling water" << endl;
	}	
	void PourInCup()
	{
		cout << "pouring into cup" << endl;
	}		

	virtual void PrepareRecipe() = 0;
};

class Coffee : public CaffeineBeverage
{
public:
	void BrewCoffeeGrinds()
	{
		cout << "dripping coffee through filter" << endl;
	}

	void AddSugarAndMilk()
	{
		cout << "adding sugar and milk" << endl;
	}

	void PrepareRecipe()
	{
		this->BoilWater();
		this->BrewCoffeeGrinds();
		this->PourInCup();
		this->AddSugarAndMilk();
	}

};

class Tea : public CaffeineBeverage
{
public:
	void SteepTeaBag()
	{
		cout << "steeping the tea" << endl;
	}

	void AddLemon()
	{
		cout << "adding lemon" << endl;
	}

	void PrepareRecipe()
	{
		this->BoilWater();
		this->SteepTeaBag();
		this->PourInCup();
		this->AddLemon();
	}

};
#endif 

int main()
{
	//冲咖啡、茶叶
	Coffee coffee;
	coffee.PrepareRecipe();

	Tea tea;
	tea.PrepareRecipe();

	return 0;
}