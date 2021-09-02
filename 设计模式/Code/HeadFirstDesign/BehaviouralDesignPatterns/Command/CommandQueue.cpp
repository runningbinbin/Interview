/*
* @Description:	命令队列标准代码
*/

#include <iostream>
#include <list>


using namespace std;

//抽象命令
class Command
{
public:
	virtual void Execute() = 0;
};

//具体命令1
class ConcreteCommand1 : public Command
{
public:
	void Execute()
	{
		cout << "ConcreteCommand1 Execute" << endl;
	}
};

//具体命令2
class ConcreteCommand2 : public Command
{
public:
	void Execute()
	{
		cout << "ConcreteCommand2 Execute" << endl;
	}
};
 
//命令队列
class CommandQueue 
{
public: 
	void AddCommand(Command *command) 
	{
		commands.push_back(command);
	}
	
	void RemoveCommand(Command *command) {
		commands.remove(command);
	}
	
    //循环调用每一个命令对象的execute()方法
	void Execute() 
	{
		for (auto &c : commands) 
		{
			c->Execute();
		}
	}

private:
	list<Command *> commands;
};

//调用者
class Invoker 
{
public:	
    //构造注入
	Invoker(CommandQueue *command_queue) 
	{
		this->command_queue = command_queue;
	}
	
    //设值注入
	void SetCommandQueue(CommandQueue *command_queue) 
	{
		this->command_queue = command_queue;
	}
	
	//调用CommandQueue类的execute()方法
	void Call() 
	{
		command_queue->Execute();
	}

private: 
	CommandQueue *command_queue; 
};


//客户调用
int main()
{
	CommandQueue *command_queue = new CommandQueue();
	
	command_queue->AddCommand(new ConcreteCommand1());
	command_queue->AddCommand(new ConcreteCommand2());

	Invoker invoker(command_queue);
	invoker.Call();

	return 0;
}