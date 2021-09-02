/*
* @Description:	“适配器模式”标准代码
*/

#define OBJECT_ADAPTER		0		//对象适配器
#define CLASS_ADAPTER		1		//类适配器

using namespace std;

#include <iostream>

#if OBJECT_ADAPTER
//目标抽象类
class Target
{
public:
	virtual void Request() = 0;
};

//适配者类
class Adaptee
{
public:
	void SpecialReques()
	{
		//被适配者功能
		cout << "Adaptee SpecialReques()" << endl;
	}
};

//适配器类
class Adapter : public Target
{
public:
	Adapter(Adaptee *adapter)
	{
		this->adapter = adapter;
	}

	void Request()
	{
		//转发调用
		adapter->SpecialReques();
	}
private:
	Adaptee *adapter;
};



#endif 

#if CLASS_ADAPTER
class Target
{
public:
	virtual void Request() = 0;
};

//适配者类
class Adaptee
{
public:
	void SpecialReques()
	{
		//被适配者功能
		cout << "Adaptee SpecialReques()" << endl;
	}
};

//适配器类
class Adapter : public Target, public Adaptee
{
public:
	void Request()
	{
		SpecialReques();
	}
};


#endif 


//客户调用
int main()
{
	#if OBJECT_ADAPTER	
	Target *target = new Adapter(new Adaptee());
	#elif CLASS_ADAPTER
	Target *target = new Adapter();	
	#endif 

	target->Request();

	return 0;
}