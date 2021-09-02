/*
* @Description:	“备忘录模式”标准代码
*/

#include <iostream>

using namespace std;

class Originator;

//备忘录声明
class Memento
{
private: 
    Memento(string state); 
    void SetState(string state); 
    string GetState(); 

public:
	friend class Originator;
	   
private: 
	string state;
};

//原发器
class Originator
{
public:
	//创建一个备忘录对象
    Memento* CreateMemento() 
    {
    	return new Memento(state);
    }

    // 根据备忘录对象恢复原发器状态
    void RestoreMemento(Memento *m) 
    {
    	state = m->GetState();
    }
 
    void SetState(string state) 
    {
    	this->state = state;
    }
 
    string GetState() 
    {
    	return state;
    }

private: 
	string state;    
};

//备忘录实现
Memento::Memento(string state) 
{
	this->state = state;
}

void Memento::SetState(string state) 
{
    this->state = state;
}

string Memento::GetState() 
{
    return this->state;
}


//负责人
class Caretaker 
{
public: 
	Memento* GetMemento() 
	{
		return memento;
	}
 
	void SetMemento(Memento *memento) 
	{
		this->memento = memento;
	}

private: 
	Memento *memento;	
};

//客户调用
int main()
{
	//创建原发器
	Originator *originator = new Originator();
	originator->SetState("1");
	//通过原发器创建备忘录
	Memento *memento = originator->CreateMemento();

	cout << originator->GetState() << endl;

	//创建负责人并保存备忘录
	Caretaker *caretaker = new Caretaker();
	caretaker->SetMemento(memento);

	//更改原发器状态
	originator->SetState("2");
	cout << originator->GetState() << endl;
	
	//通过备忘录恢复原发器之前的状态
	originator->RestoreMemento(caretaker->GetMemento());
	cout << originator->GetState() << endl;

	return 0;
}