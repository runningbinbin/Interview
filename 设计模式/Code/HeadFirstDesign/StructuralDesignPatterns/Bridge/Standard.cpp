/*
* @Description:	“桥接模式”标准代码
*/

#include <iostream>

using namespace std;

//抽象实现
class Implementor 
{
public:
	virtual void OperationImpl() = 0;
};

//具体实现A
class ConcreateImplementorA : public Implementor
{
public:
	void OperationImpl()
	{
		//具体操作
		cout << "ConcreateImplementorA OperationImpl()" << endl;
	}
};

//具体实现B
class ConcreateImplementorB : public Implementor
{
public:
	void OperationImpl()
	{
		//具体操作
		cout << "ConcreateImplementorB OperationImpl()" << endl;
	}
};

//抽象类
class Abstraction 
{
public: 
	void SetImplementor(Implementor *impl) 
	{
		this->impl = impl;
	}

	//声明抽象业务方法
	virtual void Operation() = 0;  

protected:
	Implementor *impl;		//定义实现类接口对象
};

//扩充类
class RefinedAbstraction : public Abstraction 
{
public:
 	void Operation() 
 	{
 		cout << "RefinedAbstraction Operation()" << endl;	
		//业务代码
		impl->OperationImpl();  //调用实现类的方法
		//业务代码
	}
};

//客户调用
int main()
{
	Abstraction * ab = new RefinedAbstraction();
	ab->SetImplementor(new ConcreateImplementorA());
	ab->Operation();

	ab->SetImplementor(new ConcreateImplementorB());
	ab->Operation();

	return 0;
}