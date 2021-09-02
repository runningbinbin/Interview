/*
* @Description:	采用“命令模式”设计的家电自动化API
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

//打开电灯命令-具体命令
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

private:	
	Light *light;
};

//关闭电灯命令-具体命令
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

private:	
	Light *light;
};

//车库门开命令-具体命令
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

private:
	Garage *garage;
};

//车库门关命令-具体命令
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


//实现遥控器
//空命令-具体命令
class NoCommand : public Command
{
public:
	void Execute()
	{
		cout << "no command" << endl;
	}
	void Undo()
	{
		cout << "no command" << endl;
	}
};


//遥控器-调用者
class CRemoteControl
{
public:
	CRemoteControl()
	{
		for (int i = 0;i < 7;i++)
		{
			on_commands[i] = new NoCommand();
			off_commands[i] = new NoCommand();
		}
	}

public:
	void SetCommand(int slot,Command *on_command,Command *off_command)
	{
		on_commands[slot] = on_command;
		off_commands[slot] = off_command;
	}

	void OnButtonWasPressed(int slot)
	{
		on_commands[slot]->Execute();
		undo_command = this->on_commands[slot];
	}

	void OffButtonWasPressed(int slot)
	{
		off_commands[slot]->Execute();
		undo_command = this->off_commands[slot];
	}

	void UndoButtonWasPressed()
	{
		undo_command->Undo();
	}

public:
	Command *on_commands[7];
	Command *off_commands[7];
	Command *undo_command;			//保存最后一次的命令，以便撤销,如果需要撤销多步，可以定义一个栈，

};

//客户调用
int main()
{
	//将所有插槽绑定命令对象
	//将动作的和接收者包进命令对象,
	Light *light = new Light();
	LightOnCommand *lighton_command = new LightOnCommand(light); 
	LightOffCommand *lightoff_command = new LightOffCommand(light); 

	Garage *garage = new Garage();
	GarageDoorOpenCommand *garagedooropen_command = new GarageDoorOpenCommand(garage);
	GarageDoorCloseCommand *garagedoorclose_command = new GarageDoorCloseCommand(garage);

	CRemoteControl remote_control;
	remote_control.SetCommand(0, lighton_command, lightoff_command);
	remote_control.SetCommand(1, garagedooropen_command, garagedoorclose_command);	


	remote_control.OnButtonWasPressed(0);
	remote_control.OffButtonWasPressed(0);
	remote_control.OnButtonWasPressed(1);
	remote_control.OffButtonWasPressed(1);
	remote_control.UndoButtonWasPressed();
	remote_control.OffButtonWasPressed(2);

	return 0;
}