/*
* @Description:	“访问者模式”标准代码
*/

#include <iostream>
#include <list>

using namespace std;

class ConcreteElementA;
class ConcreteElementB;

//抽象访问者
class Visitor
{
public: 
	virtual void Visit(ConcreteElementA *elementA) = 0;
	virtual void Visit(ConcreteElementB *elementB) = 0;
};

//具体访问者A
class ConcreteVisitorA : public Visitor
{
public: 
	void Visit(ConcreteElementA *elementA)
	{
		//元素ConcreteElementA操作代码
		cout << "ConcreteVisitorA Visit(ConcreteElementA *elementA)" << endl;
	}
	void Visit(ConcreteElementB *elementB)
	{
		//元素ConcreteElementB操作代码
		cout << "ConcreteVisitorA Visit(ConcreteElementB *elementB)" << endl;
	}
};

//具体访问者B
class ConcreteVisitorB : public Visitor
{
public: 
	void Visit(ConcreteElementA *elementA)
	{
		//元素ConcreteElementA操作代码
		cout << "ConcreteVisitorB Visit(ConcreteElementA *elementA)" << endl;
	}
	void Visit(ConcreteElementB *elementB)
	{
		//元素ConcreteElementB操作代码
		cout << "ConcreteVisitorB Visit(ConcreteElementB *elementB)" << endl;
	}
};

//抽象元素
class Element
{
public: 
	virtual void Accept(Visitor *visitor) = 0;
};


//具体元素A
class ConcreteElementA : public Element
{
public: 
	void Accept(Visitor *visitor)
	{
		visitor->Visit(this);
	}
	
	void OperationA()
	{
		//业务方法
		cout << "ConcreteElementA OperationA()" << endl;
	}
};

//具体元素B
class ConcreteElementB : public Element
{
public: 
	void Accept(Visitor *visitor)
	{
		visitor->Visit(this);
	}
	
	void OperationB()
	{
		//业务方法
		cout << "ConcreteElementA OperationB()" << endl;
	}
};


//对象结构
class ObjectStructure
{
public: 
	void Accept(Visitor *visitor)
	{
		//遍历访问集合中的每一个元素
		for (auto &e : elements)
		{
			e->Accept(visitor);
		}
	}
 
	void AddElement(Element *element)
	{
		elements.push_back(element);
	}
 
	void RemoveElement(Element *element)
	{
		elements.remove(element);
	}

private:
	list<Element*> elements; 		 //定义一个集合用于存储元素对象	
};


//客户调用
int main()
{
	//对象结构中，不止具体元素A，还有其他类型的元素；
	//同样，具体访问者也不止一个。
	ObjectStructure *o = new ObjectStructure();
	o->AddElement(new ConcreteElementA());
	o->AddElement(new ConcreteElementB());
	o->Accept(new ConcreteVisitorA());
	o->Accept(new ConcreteVisitorB());

	return 0;
}

