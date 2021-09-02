/*
* @Description:	使用“适配器模式”的火鸡适配鸭子
*/

#include <stdio.h>
#include <iostream>

using namespace std;

//鸭子-目标类
class Duck
{
public:
	virtual void Quack() = 0;		
	virtual void Fly() = 0;		
};

//绿头鸭
class MallardDuck : public Duck
{
	void Quack()
	{
		cout << "Quack" << endl;
	}		
	void Fly()
	{
		cout << "Fly" << endl;
	}

};

void TestDuck(Duck* Duck)
{
	Duck->Quack();
	Duck->Fly();
}

//火鸡-适配者
class Turkey
{
public:	
	void Gobble()
	{
		cout << "gobble" << endl;
	}		
	void Fly()
	{
		cout << "Flying a short distance" << endl;
	}
};

//火鸡适配器-适配器
class TurkeyAdapter : public Duck
{
public:
	TurkeyAdapter(Turkey *turkey)
	{
		this->turkey = turkey;
	}

public:
	void Quack()
	{
		this->turkey->Gobble();
	}

	void Fly()
	{
		//火鸡飞行距离短，要让鸭子的飞行距离和火鸡的飞行能够对应,故连续飞5次完成
		for (int i = 0; i < 5; i++)
			this->turkey->Fly();
	}

private:
	Turkey *turkey;
};

int main()
{	
	TestDuck(new MallardDuck());

	Duck *duck = new TurkeyAdapter(new Turkey());	
	TestDuck(duck);

	return 0;
}