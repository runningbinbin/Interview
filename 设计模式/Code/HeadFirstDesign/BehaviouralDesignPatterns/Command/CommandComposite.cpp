/*
* @Description:	命令模式和组合模式示例
*/

#include <stdio.h>
#include <iostream>

using namespace std;


//开灯厂商类-命令接收者
class Light
{
public:
	void On()
	{
		cout << "light on" << endl;
	}	

	void Off()
	{
		cout << "light off" << endl;
	}	
};

//车库门厂商类-命令接收者
class Garage
{
public:
	void Open()
	{
		cout << "garage open" << endl;
	}

	void Close()
	{
		cout << "garage close" << endl;
	}

	void Down()
	{
		cout << "garage down" << endl;
	}
public:	
};

//抽象命令
class Command
{
public:
	virtual void Execute() = 0;	
	virtual void Undo() = 0;
};

//打开电灯-具体命令
class LightOnCommand : public Command 
{
public:
	LightOnCommand(Light *light)
	{
		this->light = light;
	}

public:
	void Execute()
	{
		light->On();
	}	

	void Undo()
	{
		light->Off();
	}	

public:	
	Light *light;
};

//关闭电灯-具体命令
class LightOffCommand : public Command 
{
public:
	LightOffCommand(Light *light)
	{
		this->light = light;
	}

public:
	void Execute()
	{
		light->Off();
	}	
	void Undo()
	{
		light->On();
	}	

public:	
	Light *light;
};

//车库门开-具体命令
class GarageDoorOpenCommand : public Command
{
public:
	GarageDoorOpenCommand(Garage *garage)
	{
		this->garage = garage;
	}

public:
	void Execute()
	{
		garage->Open();
	}
	void Undo()
	{
		garage->Close();
	}

public:
	Garage *garage;
};

//车库门关-具体命令
class GarageDoorCloseCommand : public Command
{
public:
	GarageDoorCloseCommand(Garage *garage)
	{
		this->garage = garage;
	}

public:
	void Execute()
	{
		garage->Close();
	}
	void Undo()
	{
		garage->Open();
	}

public:
	Garage *garage;
};

//具备“party模式”的遥控器,按下一个按键，做多个操作
class MacroCommand : public Command
{
public:
	MacroCommand(Command **commands, int num)
	{	
		this->commands = commands;	
		this->num = num;
	}

public:
	void Execute()
	{
		for (int i = 0;i < num;i++)
		{
			this->commands[i]->Execute();
		}
	}
	void Undo()
	{
		;
	}
public:		
	Command **commands;
	int num;
};

//客户调用
int main()
{

	//通过宏命令完成一组动作
	Light *light = new Light();
	LightOnCommand *lighton_command = new LightOnCommand(light); 
	LightOffCommand *lightoff_command = new LightOffCommand(light); 

	Garage *garage = new Garage();
	GarageDoorOpenCommand *garagedooropen_command = new GarageDoorOpenCommand(garage);
	GarageDoorCloseCommand *garagedoorclose_command = new GarageDoorCloseCommand(garage);

	
	Command *party_on[7] = {lighton_command,garagedooropen_command};
	MacroCommand macro_command(party_on,2);
	macro_command.Execute();

	Command *party_off[7] = {lightoff_command,garagedoorclose_command,&macro_command};
	MacroCommand macro_command2(party_off,3);
	macro_command2.Execute();

	return 0;
}