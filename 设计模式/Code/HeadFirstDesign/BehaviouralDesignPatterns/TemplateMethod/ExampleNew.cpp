/*
* @Description: 使用“模板方法模式”设计的冲茶冲咖啡软件
*/

#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;

//抽象饮料-抽象类
class CaffeineBeverage
{
public:	
	void BoilWater()
	{
		cout << "boiling water" << endl;
	}	

	virtual void Brew() = 0;

	void PourInCup()
	{
		cout << "pouring into cup" << endl;
	}	

	virtual void AddCondiments() = 0;

	//"钩子"
	virtual bool CustomerWantsCondients()
	{
		cout << "in" << endl;
		return true;
	}


	virtual void PrepareRecipe() final
	{
		this->BoilWater();
		this->Brew();
		this->PourInCup();

		//钩子使用
		if (this->CustomerWantsCondients())
			this->AddCondiments();
	}
};

//咖啡-具体类
class Coffee : public CaffeineBeverage
{
public:
	void Brew()
	{
		cout << "dripping coffee through filter" << endl;
	}

	void AddCondiments()
	{
		cout << "adding sugar and milk" << endl;
	}

	bool CustomerWantsCondients()
	{
		while(1)
		{
			cout << "would you like milk and sugar with you coffee (y/n) ?" << endl;

			char CustomerWants[32] = {0};
			if (NULL != fgets(CustomerWants, 3,stdin))
			{
				char *Find = strstr(CustomerWants,"\n");	
				if (Find)
					*Find = '0';
				if (0 == strncmp("y",CustomerWants,1))
					return true;
				else if (0 == strncmp("n",CustomerWants,1))
					return false;
				else
					cout << "please input y or n" << endl;
			}	
		}	
		
			
	}
 	
};

//茶-具体类
class Tea : public CaffeineBeverage
{
public:
	void Brew()
	{
		cout << "steeping the tea" << endl;
	}

	void AddCondiments()
	{
		cout << "adding lemon" << endl;
	}

	bool CustomerWantsCondients()
	{
		while(1)
		{
			cout << "would you like lemon with you tea (y/n) ?" << endl;
			char CustomerWants[32] = {0};
			if (NULL != fgets(CustomerWants, 3 ,stdin))
			{
				char *Find = strstr(CustomerWants,"\n");	
				if (Find)
					*Find = '0';

				if (0 == strncmp("y",CustomerWants,1))
					return true;
				else if (0 == strncmp("n",CustomerWants,1))
					return false;
				else
					cout << "please input y or n" << endl;
			}
		}	
	}
};

//客户调用
int main()
{	
	//冲咖啡、茶叶
	CaffeineBeverage * coffee = new Coffee();
	coffee->PrepareRecipe();

	CaffeineBeverage * tea = new Tea();
	tea->PrepareRecipe();

	return 0;
}