/*
* @Description:	“中介者模式”标准代码
*/

#include <iostream>

using namespace std;

class Colleague;
class ConcreteColleagueA;
class ConcreteColleagueB;

//抽象中介者-声明
class Mediator
{
public:	
	virtual void Operation(Colleague *c) = 0;	
};

//具体中介者-声明
class ConcreteMediator : public Mediator
{
public:	
	ConcreteMediator(ConcreteColleagueA *ca,ConcreteColleagueB *cb);

	void Operation(Colleague *c);

private:
	ConcreteColleagueA *ca;
	ConcreteColleagueB *cb;
};

//抽象同事类-声明
class Colleague
{
public:
	void SetMediator(Mediator *mediator);

	//依赖方法
	void Operation();

	//自己的方法
	virtual void Method() = 0;

private:
	Mediator *mediator;	
};

//具体同事类-声明
class ConcreteColleagueA : public Colleague
{
public:	
	void Method();
};

//具体同事类-声明
class ConcreteColleagueB : public Colleague
{
public:	
	void Method();
};


//具体中介者-定义
ConcreteMediator::ConcreteMediator(ConcreteColleagueA *ca,ConcreteColleagueB *cb)
{
	this->ca = ca;
	this->cb = cb;
}
void ConcreteMediator::Operation(Colleague *c)
{	
	if (ca == c)
	{
		cb->Method();
	}
	else if (cb == c)
	{
		ca->Method();
	}
}

//抽象同事类-定义
void Colleague::SetMediator(Mediator *mediator)
{
	this->mediator = mediator;
}
void Colleague::Operation()
{
	mediator->Operation(this);
}

//具体同事类-定义 
void ConcreteColleagueA::Method()
{
	cout << "ConcreteColleagueA Method" << endl;
}

//具体同事类-定义
void ConcreteColleagueB::Method()
{
	cout << "ConcreteColleagueB Method" << endl;
}

//客户调用
int main()
{
	ConcreteColleagueA *ca = new ConcreteColleagueA();
	ConcreteColleagueB *cb = new ConcreteColleagueB();

	Mediator *mediator = new ConcreteMediator(ca,cb);

	ca->SetMediator(mediator);
	cb->SetMediator(mediator);

	ca->Operation();
	cb->Operation();

	return 0;
}