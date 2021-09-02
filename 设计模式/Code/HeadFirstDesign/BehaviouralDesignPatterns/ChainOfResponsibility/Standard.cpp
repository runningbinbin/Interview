/*
* @Description:	“责任链模式”标准代码
*/

#include <iostream>

using namespace std;

//请求
class Request
{
public:
	void SetValue(int value)
	{
		this->value = value;
	}

	int GetValue()
	{
		return value;
	}

private:
	int value;
};

//抽象处理者
class Handler 
{	
public:
	void SetSuccessor(Handler *successor) 
	{
		this->successor = successor;
	}
	
	virtual void HandleRequest(Request *request) = 0;

protected: 
	Handler *successor;			//维持对下家的引用
};

//具体处理者A
class ConcreteHandlerA : public Handler 
{
public:
	 void HandleRequest(Request *request) 
	 {
	 	//请求满足条件
		if (0 == request->GetValue()) 
		{
			//处理请求
			cout << "ConcreteHandlerA HandleRequest()" << endl;
		}
		//请求不满足条件,则转发请求
		else 
		{
			this->successor->HandleRequest(request);  
		}
	}
};

//具体处理者B
class ConcreteHandlerB : public Handler 
{
public:
	 void HandleRequest(Request *request) 
	 {
	 	//请求满足条件
		if (1 == request->GetValue()) 
		{
			//处理请求
			cout << "ConcreteHandlerB HandleRequest()" << endl;
		}
		//请求不满足条件,则转发请求
		else 
		{
			this->successor->HandleRequest(request);  
		}
	}
};

//客户调用
int main()
{
	//多个具体处理者应不同
	Handler *handler1 = new ConcreteHandlerA();
	Handler *handler2 = new ConcreteHandlerB();
	
	//将handle2链接为handle1的下一个处理对象
	handler1->SetSuccessor(handler2);

	Request *request = new Request();
	request->SetValue(0);
	handler1->HandleRequest(request);

	request->SetValue(1);
	handler1->HandleRequest(request);

	return 0;
}
