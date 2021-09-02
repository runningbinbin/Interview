/*
* @Description:	糖果机软件最初设计方式
*/

#include <iostream>

using namespace std;

class GumballMachine
{
private:
	//四种状态
	enum State
	{
		SOLD_OUT = 0,		//售罄状态
		NO_QUARTER = 1,		//没有25分钱状态
		HAS_QUARTER = 2,	//有25分钱状态	
		SOLD = 3			//售出状态
	}; 

public:
	GumballMachine(int count)
	{
		this->count = count;
		if (0 < count)
		{
			SetState(NO_QUARTER);
		}
	}

public:
	void SetState(State state)
	{
		this->state = state;
	}

	State GetState()
	{
		return this->state;
	}

	//四种动作
	//投入25分钱
	void InsertQuater()
	{
		if (SOLD_OUT == state)
		{
			cout << "you have not insert a quarter, the machine is sold out" << endl;
		}
		else if (NO_QUARTER == state)
		{
			cout << "you insert a quarter" << endl;
			SetState(HAS_QUARTER);
		}
		else if (HAS_QUARTER == state)
		{
			cout << "you have not insert another quarter" << endl;
		}
		else if (SOLD == state)
		{
			cout << "please wait,we are already giving you another a gumball" << endl;
		}

	}
	//退回25分钱
	void EjectQuater() 
	{
		if (SOLD_OUT == state)
		{
			cout << "you have not insert a quarter, the machine is sold out" << endl;
		}
		else if (NO_QUARTER == state)
		{
			cout << "you are not insert a quarter" << endl;
		}
		else if (HAS_QUARTER == state)
		{
			cout << "quarter returned" << endl;
			SetState(NO_QUARTER);
		}
		else if (SOLD == state)
		{
			cout << "sorry,you already turned the crank" << endl;
		}
	}
	//转动曲柄
	void TurnCrank() 
	{
		if (SOLD_OUT == state)
		{
			cout << "you turned, but there is no gumball" << endl;
		}
		else if (NO_QUARTER == state)
		{
			cout << "you turned, but there is no a quarter" << endl;
		}
		else if (HAS_QUARTER == state)
		{
			cout << "you turned..." << endl;
			SetState(SOLD);
			Dispense();
		}
		else if (SOLD == state)
		{
			cout << "turn crank twice does not get you another gumball" << endl;
		}
	}
	//发放糖果
	void Dispense()
	{
		if (SOLD_OUT == state)
		{
			cout << "no gumball dispense" << endl;
		}
		else if (NO_QUARTER == state)
		{
			cout << "you need pay first" << endl;
		}
		else if (HAS_QUARTER == state)
		{
			cout << "no gumball dispense" << endl;
		}
		else if (SOLD == state)
		{
			if (0 != count)
				count--;

			if (0 == count)
			{
				cout << "oops, out of gumball" << endl;
				SetState(SOLD_OUT);	
			}
			else 
			{
				SetState(NO_QUARTER);	
			}

		}
	} 	

private:
	int count;				//糖果剩余数量
	State state;		 	//糖果机状态
};

int main()
{
	GumballMachine *gumball_machine = new GumballMachine(3);
	gumball_machine->InsertQuater();
	gumball_machine->TurnCrank();
	cout << gumball_machine->GetState() << endl;

	gumball_machine->InsertQuater();
	cout << gumball_machine->GetState() << endl;
	gumball_machine->EjectQuater();
	gumball_machine->TurnCrank();
	cout << gumball_machine->GetState() << endl;

	return 0;
}
