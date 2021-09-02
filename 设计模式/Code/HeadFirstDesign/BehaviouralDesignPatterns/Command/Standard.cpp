/*
* @Description:	“命令模式”标准代码
*/


#include <iostream>

using namespace std;

//抽象命令
class Command 
{
public: 
	virtual void Execute() = 0;
};

//接收者
class Receiver 
{
public: 
	void Action() 
	{
		//具体操作
		cout << "Receiver Action()" << endl;
	}
};

//具体命令
class ConcreteCommand : public Command 
{
public: 
	ConcreteCommand(Receiver *receiver)
	{
		this->receiver = receiver;
	}

	void Execute() 
	{
		receiver->Action(); //调用请求接收者的业务处理方法action()
	}

private:
	 Receiver *receiver; 	//维持一个对请求接收者对象的引用
};

//调用者
class Invoker 
{
public:	
    //构造注入
	Invoker(Command *command) 
	{
		this->command = command;
	}
	
    //设值注入
	void SetCommand(Command *command) 
	{
		this->command = command;
	}
	
	//业务方法，用于调用命令类的Execute()方法
	void Call() 
	{
		command->Execute();
	}

private: 
	Command *command;	
};


//客户调用
int main()
{
	Invoker *invoker = new Invoker(new ConcreteCommand(new Receiver()));
	invoker->Call();

	return 0;
}