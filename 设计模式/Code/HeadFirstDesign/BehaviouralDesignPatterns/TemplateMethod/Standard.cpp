/*
* @Description: “模板模式”标准代码
*/

#include <iostream>

using namespace std;

//抽象类
class AbstractClass 
{
public: 
	//模板方法
	void TemplateMethod() 
	{
        PrimitiveOperation1();
        PrimitiveOperation2();
        PrimitiveOperation3();
	}
 
	//基本方法—具体方法
	void PrimitiveOperation1() 
	{
	    //实现代码
	    cout << "AbstractClass PrimitiveOperation1()" << endl;
	}
 
	//基本方法—抽象方法
    virtual void PrimitiveOperation2() = 0;    
 
	//基本方法—抽象方法
	virtual void PrimitiveOperation3() = 0;   

	//基本方法-钩子方法
	virtual bool IsOperation3()
	{
		return false;
	}
};

//具体类
class ConcreteClass : public AbstractClass 
{
public: 
	void PrimitiveOperation2() 
	{
	    //实现代码
	    cout << "ConcreteClass PrimitiveOperation2()" << endl;
	}
	 
	void PrimitiveOperation3() 
	{
	    //实现代码
	     cout << "ConcreteClass PrimitiveOperation3()" << endl;
	}
	bool IsOperation3()
	{
		return true;
	}
};

//客户调用
int main()
{
	AbstractClass *c = new ConcreteClass();
	c->TemplateMethod();

	return 0;
}