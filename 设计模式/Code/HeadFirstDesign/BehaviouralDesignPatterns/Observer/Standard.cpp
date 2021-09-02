/*
* @Description: “观察者模式”标准代码
*/


#include <iostream>
#include <list>

using namespace std;


//抽象观察者
class Observer
{
public:
	virtual void Update() = 0;
};


//具体观察者
class ConcreteObserver : public Observer
{
public:
	//实现响应方法
	void Update()
	{
		//具体响应代码
		cout << "收到主题更新" << endl;
	}
};

//抽象主题
class Subject
{
public:
	void RegisterObserver(Observer *observer)
	{
		observers.push_back(observer);
	}

	void RemoveObserver(Observer *observer)
	{
		observers.remove(observer);
	}

	//可抽象可具体
	virtual void NotifyObserver() = 0;

protected:
	list <Observer *> observers;	
};

//具体主题
class ConcreteSubject : public Subject
{
public:
	//实现通知方法
	void NotifyObserver()
	{
		cout << "主题更新" << endl;
		for (auto &obs : observers)
		{
			obs->Update();
		}
	}
};

int main()
{
	Observer *observer = new ConcreteObserver();
	Subject *subject = new ConcreteSubject();

	//注册观察者
	subject->RegisterObserver(observer);

	//主题更新
	subject->NotifyObserver();

	return 0;
}