/*
* @Description:	“状态模式”标准代码
*/

#include <iostream>

using namespace std;

#define CLIENT_CHANGE_STATE 			0			//客户负责状态转换
#define CONTEXT_CHANGE_STATE 			1 			//环境类负责转换
#define CONCRETESTATE_CHANGE_STATE 		0 			//具体状态类负责转换

#if CLIENT_CHANGE_STATE
//抽象状态
class State
{
public:
	//声明抽象业务方法，不同的具体状态类可以不同的实现
	virtual void Handle() = 0;
};

//具体状态A
class ConcreteStateA : public State
{
public:
	void Handle()
	{
		cout << "ConcreteStateA Handle()" << endl;
	}
};

//具体状态B
class ConcreteStateB : public State
{
public:
	void Handle()
	{
		cout << "ConcreteStateB Handle()" << endl;
	}
};

//环境类
class Context
{
public:
	void SetState(State *state)
	{
		this->state = state;
	}

	void Request()
	{
		cout << "Context Request()" << endl;
		state->Handle();
	}

private:
	State *state;	
};
#endif 


#if CONTEXT_CHANGE_STATE
class State;
//环境类声明
class Context 
{
public:
	Context();
	void SetValue(int value);
	void SetState(State *state);
	void ChangeState();
	void Request();

private:
	State *state;				//状态引用
	State *concrete_state_a;	//具体状态A
	State *concrete_state_b;	//具体状态B				

	int value;					//其他属性值，该属性值的变化可能会导致对象状态发生变化
};

//抽象状态
class State
{
public:
	//声明抽象业务方法，不同的具体状态类可以不同的实现
	virtual void Handle(Context *context) = 0;
};

//具体状态A
class ConcreteStateA : public State
{
public:
	void Handle(Context *context)
	{
		//此状态下方法具体实现
		cout << "ConcreteStateA Handle" << endl;
		context->SetValue(1);
	}	
};

//具体状态B
class ConcreteStateB : public State
{
public:
	void Handle(Context *context)
	{
		//此状态下方法具体实现
		cout << "ConcreteStateB Handle" << endl;
		context->SetValue(0);
	}	
};

//环境类定义
Context::Context()
{
	value = 0;
	concrete_state_a = new ConcreteStateA();
	concrete_state_b = new ConcreteStateB();
	state = concrete_state_a;
}
void Context::SetValue(int value)
{
	this->value = value;
}

void Context::SetState(State *state)
{
	this->state = state;
}

void Context::ChangeState()
{
	if (0 == value)
		SetState(concrete_state_a);
	else if (1 == value)
		SetState(concrete_state_b);
}

void Context::Request()
{
	//调用状态对象的业务方法
	state->Handle(this);

	//状态切换
	ChangeState();		
}
#endif 


#if CONCRETESTATE_CHANGE_STATE
class Context;
//抽象状态
class State
{
public:
	//声明抽象业务方法，不同的具体状态类可以不同的实现
	virtual void Handle() = 0;

public:
	Context *context;
};

//环境类声明
class Context 
{
public:
	Context();
	void SetValue(int value);
	int GetValue();

	void SetState(State *state);
	void Request();

	State *GetConcreteStateA(); 
	State *GetConcreteStateB(); 

private:
	State *state;				//状态引用
	State *concrete_state_a;		//具体状态1
	State *concrete_state_b;		//具体状态2		

	int value;					//其他属性值，该属性值的变化可能会导致对象状态发生变化
};

//具体状态A
class ConcreteStateA : public State
{
public:
	ConcreteStateA(Context *context)
	{
		this->context = context;
	}
	void ChangeState()
	{
		if (0 == context->GetValue())
			context->SetState(context->GetConcreteStateA());
		else if (1 == context->GetValue())
			context->SetState(context->GetConcreteStateB());
	}

	void Handle()
	{
		//此状态下方法具体实现
		cout << "ConcreteStateA Handle" << endl;
		context->SetValue(1);

		ChangeState();
	}	
};

//具体状态B
class ConcreteStateB : public State
{
public:
	ConcreteStateB(Context *context)
	{
		this->context = context;
	}

	void Handle()
	{
		//此状态下方法具体实现
		cout << "ConcreteStateB Handle" << endl;
		context->SetValue(0);
		ChangeState();
	}	
	void ChangeState()
	{
		if (0 == context->GetValue())
			context->SetState(context->GetConcreteStateA());
		else if (1 == context->GetValue())
			context->SetState(context->GetConcreteStateB());
	}
};

//环境类定义
Context::Context()
{
	value = 0;
	concrete_state_a = new ConcreteStateA(this);
	concrete_state_b = new ConcreteStateB(this);
	state = concrete_state_a;
}
void Context::SetValue(int value)
{
	this->value = value;
}
int Context::GetValue()
{
	return this->value;
}
void Context::SetState(State *state)
{
	this->state = state;
}

void Context::Request()
{
	//调用状态对象的业务方法
	state->Handle();
}
State * Context::GetConcreteStateA()
{
	return this->concrete_state_a;
}
State * Context::GetConcreteStateB()
{
	return this->concrete_state_b;
}
#endif 


//客户调用
int main()
{
	#if CLIENT_CHANGE_STATE
	Context *context = new Context();
	context->SetState(new ConcreteStateA());
	context->Request();
	context->SetState(new ConcreteStateB());
	context->Request();
	#elif CONTEXT_CHANGE_STATE || CONCRETESTATE_CHANGE_STATE
	Context *context = new Context();
	context->Request();
	context->Request();
	#endif 

	return 0;
} 