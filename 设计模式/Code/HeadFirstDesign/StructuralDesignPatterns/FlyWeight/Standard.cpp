/*
* @Description: “享元模式”标准代码
*/

#include <iostream>
#include <map>
#include <iterator>

using namespace std;

//抽象享元类
class Flyweight
{
public:
	//外部状态由外部状态，不保存在享元对象中，即使是同一个对象，在每一次调用时也可以传入不同的外部状态
	virtual void Operation(string extrinsic_state) = 0;

	virtual string GetIntrinsicState() = 0;
};

//具体享元类
class ConcreteFlyweight : public Flyweight
{
public:
	ConcreteFlyweight(string intrinsic_state)
	{
		this->intrinsic_state = intrinsic_state;
	}
public:
	//外部状态由外部状态，不保存在享元对象中，即使是同一个对象，在每一次调用时也可以传入不同的外部状态
	void Operation(string extrinsic_state)
	{
		//具体操作。。。
		cout << extrinsic_state << endl;
	}		

	string GetIntrinsicState()
	{
		return intrinsic_state;
	}

private:
	//内部状态作为成员变量，同一个享元对象其内部状态一致
	string intrinsic_state;	
};

//非共享具体享元类
class UnsharedConcreteFlyweight : public Flyweight
{
public:
	UnsharedConcreteFlyweight(string state)
	{
		this->state = state;
	}
public:
	void Operation(string extrinsic_state)
	{
		//具体操作。。。
		cout << extrinsic_state << endl;
	}	
	string GetIntrinsicState()
	{
		return state;
	}	

private:
	string state;	
};

//享元工厂类
class FlyweightFactory 
{
public:
 	static Flyweight* GetFlyweight(string key)
 	{
        //如果对象存在，则直接从享元池获取
        map<string,Flyweight*>::iterator iter = flyweights.find(key);
        if(iter != flyweights.end())
        {
           	return iter->second;
        }
      	//如果对象不存在，先创建一个新的对象添加到享元池中，然后返回
      	else 
      	{
            Flyweight *fw = new ConcreteFlyweight("intrinsic_state");
            flyweights.insert(make_pair(key,fw));
            return fw;
    	}
    }

private:
	//定义一个map用于存储享元对象，实现享元池
	static map<string,Flyweight*> flyweights;
};
map<string,Flyweight*> FlyweightFactory::flyweights;


//客户调用
int main()
{
	//fw设置前后内部状态一样，使用前设置外部状态，从而达到共享
	Flyweight *fw = FlyweightFactory::GetFlyweight("key");
	fw->Operation("extrinsic_state");
	cout << fw->GetIntrinsicState() << endl;	

	fw->Operation("extrinsic_state2");
	cout << fw->GetIntrinsicState() << endl;	

	//非共享直接创建实例
	Flyweight *unfw = new UnsharedConcreteFlyweight("state");
	unfw->Operation("extrinsic_state");

	return 0;
}