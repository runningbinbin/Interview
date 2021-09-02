/*
* @Description:	使用“状态模式”设计的糖果机软件 
*/

#include <stdio.h>
#include <iostream>

using namespace std;


class GumballMachine;
//糖果机抽象状态定义-抽象状态
class State
{
public:
	State(GumballMachine *gumball_machine)
	{
		this->gumball_machine = gumball_machine;
	}

	//投入25分
	virtual void InsertQuater() = 0;

	//退回25分
	virtual void EjectQuater() = 0;

	//转动曲柄
	virtual void TurnCrank() = 0;

	//发放糖果
	virtual void Dispense() = 0;

public:
	string GetName()
	{
		return name;
	}

protected:
	string name;						//状态名称	
	GumballMachine *gumball_machine;	//糖果机引用，方便后期根据糖果数量更改状态
};

//糖果机定义-环境类
class GumballMachine
{
public:
	GumballMachine(int count);

public:
	void InsertQuater();
	void EjectQuater();
	void TurnCrank();
	void ReleaseBall();

	void SetState(State *state);
	State* GetNoQuarterState();
	State* GetHasQuarterState();
	State* GetSoldState();
	State* GetSoldOutState();
	string GetState();
	int GetCount();

private:
	State *state;
	State *no_quarter_state;
	State *has_quarter_state;
	State *sold_state;
	State *soldout_state;

	int count;					//糖果数量
};


//没有25分状态-具体状态
class NoQuarterState : public State
{
public:
	NoQuarterState(GumballMachine *gumball_machine) : State(gumball_machine)
	{
		this->name = "NoQuarterState";
	}

public:
	void InsertQuater()
	{
		cout << "you insert a quarter" << endl;
		gumball_machine->SetState(gumball_machine->GetHasQuarterState());
	}
	void EjectQuater() 
	{
		cout << "you are not insert a quarter" << endl;
	}
	void TurnCrank() 
	{
		cout << "you turned, but there is no a quarter" << endl;
	}
	void Dispense()
	{
		cout << "you need pay first" << endl;
	} 
};

//有25分状态-具体状态
class HasQuarterState : public State
{
public:
	HasQuarterState(GumballMachine *gumball_machine) : State(gumball_machine)
	{
		this->name = "HasQuarterState";
	}

public:
	void InsertQuater()
	{
		cout << "you have not insert another quarter" << endl;
	}
	void EjectQuater() 
	{
		cout << "quarter returned" << endl;
		gumball_machine->SetState(gumball_machine->GetNoQuarterState());
	}
	void TurnCrank() 
	{
		cout << "you turned..." << endl;
		gumball_machine->SetState(gumball_machine->GetSoldState());
	}
	void Dispense()
	{
		cout << "no gumball dispense" << endl;
	} 
};

//售出糖果状态-具体状态
class SoldState : public State
{
public:
	SoldState(GumballMachine *gumball_machine) : State(gumball_machine)
	{
		this->name = "Soldstate";
	}

public:
	void InsertQuater()
	{
		cout << "please wait,we are already giving you another a gumball" << endl;
	}
	void EjectQuater() 
	{
		cout << "sorry,you already turned the crank" << endl;
	}
	void TurnCrank() 
	{
		cout << "turn crank twice does not get you another gumball" << endl;
	}
	void Dispense()
	{
		this->gumball_machine->ReleaseBall();
		if (0 < gumball_machine->GetCount())
		{
			gumball_machine->SetState(gumball_machine->GetNoQuarterState());
		}
		else 
		{
			cout << "oops, out of gumball" << endl;
			gumball_machine->SetState(gumball_machine->GetSoldOutState());
		}
		
	} 
};
//糖果售罄状态-具体状态
class SoldOutState : public State
{
public:
	SoldOutState(GumballMachine *gumball_machine) : State(gumball_machine)
	{
		this->name = "SoldOutstate";
	}

public:
	void InsertQuater()
	{
		cout << "you have not insert a quarter, the machine is sold out" << endl;
	}
	void EjectQuater() 
	{
		cout << "you can not eject,you have not inserted a quarter yet" << endl;
	}
	void TurnCrank() 
	{
		cout << "you turned, but there is no gumball" << endl;
	}
	void Dispense()
	{
		cout << "no gumball dispense" << endl;
	} 
};

//糖果机实现
GumballMachine::GumballMachine(int count)
{
	this->count = count;
	this->no_quarter_state = new NoQuarterState(this);
	this->has_quarter_state = new HasQuarterState(this);
	this->sold_state = new SoldState(this);
	this->soldout_state = new SoldOutState(this);

	//只要有糖果，就将及其状态设置成，没有25分状态
	if (0 < this->count)
	{
		this->state = this->no_quarter_state;
	}
}
void GumballMachine::InsertQuater()
{
	state->InsertQuater();
}
void GumballMachine::EjectQuater()
{
	state->EjectQuater();
}
void GumballMachine::TurnCrank()
{
	state->TurnCrank();

	//“发放糖果时内部动作，用户不可以直接要求机器发放糖果”
	state->Dispense();
}
void GumballMachine::ReleaseBall()
{
	cout << "a gumball comes rolling out the slot" << endl;
	if (0 != count)
		count--;
}

void GumballMachine::SetState(State *state)
{
	this->state = state;
}

State* GumballMachine::GetNoQuarterState()
{
	return no_quarter_state;
}
State* GumballMachine::GetHasQuarterState()
{
	return has_quarter_state;
}
State* GumballMachine::GetSoldState()
{
	return sold_state;
}
State* GumballMachine::GetSoldOutState()
{
	return soldout_state;
}

string GumballMachine::GetState()
{
	return state->GetName();
}

int GumballMachine::GetCount()
{
	return count;
}

//客户调用
int main()
{
	//优点：
	//	1.将每个状态的行为局部化到它自己的类中；
	//	2.将容易产生问题的if语句删除，以便日后的维护；
	//	3.让每个状态“对修改关闭”，让糖果机“对扩展开放”，可以轻易的加入新的状态；
	//	4.创建一个新的代码基和类结构,这更能映射万能糖果公司的图,而且更容易阅读和理解。
	GumballMachine gumball_machine(5);
	gumball_machine.InsertQuater();
	cout << "state: " << gumball_machine.GetState() << endl;
	gumball_machine.TurnCrank();
	cout << "state: " << gumball_machine.GetState() << endl;
	gumball_machine.InsertQuater();
	gumball_machine.TurnCrank();
	cout << "state: " << gumball_machine.GetState() << endl;

	return 0;
}
