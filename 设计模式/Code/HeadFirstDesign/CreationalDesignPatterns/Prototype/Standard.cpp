/*
* @Description:	“原型模式”标准代码
*/

#include <stdio.h>
#include <iostream>

using namespace std;

/**
 * 原型模式
 * 	1、定义：
 * 		能够复制已有对象， 而又无需使代码依赖它们所属的类。			 
 */

//抽象原型
class Prototype
{
public:
	virtual Prototype *Clone() = 0;	

	virtual string GetAttr() = 0;	
	virtual void SetAttr(string attr) = 0;
};

//具体原型
class ConcreateProrotype : public Prototype
{
public:
	string GetAttr()
	{
		return this->attr;
	}

	void SetAttr(string attr)
	{
		this->attr = attr;
	}

	//复制自身
	Prototype *Clone()
	{	
		Prototype *proto_type = new ConcreateProrotype(); 
		proto_type->SetAttr(attr);

		return  proto_type;
	}

private:
	string attr;	
};


//客户调用
int main()
{
	Prototype *ConProA = new ConcreateProrotype();
	ConProA->SetAttr("hello");
	Prototype *ConProB = ConProA->Clone();

	cout << ConProA->GetAttr() << endl;
	cout << ConProB->GetAttr() << endl;

	return 0;
}
