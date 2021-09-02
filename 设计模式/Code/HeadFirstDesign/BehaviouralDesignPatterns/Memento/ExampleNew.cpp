/*
* @Description:	采用“备忘录模式”设计的“支持单步可撤销的象棋软件”
*/

#include <iostream>

using namespace std;

class Chessman;

//象棋备忘录
class ChessmanMemento
{
private:
	ChessmanMemento(string label,int x,int y)
	{
		this->label = label;
		this->x = x;
		this->y = y;
	}	

private:
	void SetLabel(string label)
	{
		this->label = label;
	}
	string GetLabel()
	{
		return label;
	}

	void SetX(int x)
	{
		this->x = x;
	}
	int GetX()
	{
		return x;
	}

	void SetY(int y)
	{
		this->y = y;
	}
	int GetY()
	{
		return y;
	}

public:
	friend class Chessman;
private:
	string label;
	int x;
	int y;	
};

//象棋类-原发器
class Chessman
{
public:
	Chessman(string label,int x,int y)
	{
		this->label = label;
		this->x = x;
		this->y = y;
	}	

public:
	//创建备忘录
	ChessmanMemento *CreateMemento()
	{
		return new ChessmanMemento(label,x,y);
	} 

	//恢复之前的状态
	void RestoreMemento(ChessmanMemento *memento)
	{
		this->label = memento->label;
		this->x = memento->x;
		this->y = memento->y;
	}

	void SetLabel(string label)
	{
		this->label = label;
	}
	string GetLabel()
	{
		return label;
	}

	void SetX(int x)
	{
		this->x = x;
	}
	int GetX()
	{
		return x;
	}

	void SetY(int y)
	{
		this->y = y;
	}
	int GetY()
	{
		return y;
	}

private:
	string label;
	int x;
	int y;	
};

//备忘录负责人
class MementoCaretaker
{
public:
	void SetMemento(ChessmanMemento *memento)
	{
		this->memento = memento;
	}	

	ChessmanMemento *GetMemento()
	{
		return this->memento;
	}

private:
	ChessmanMemento *memento;	
};

void Display(Chessman *chess)
{
	cout << "棋子" << chess->GetLabel() << \
	",当前位置" << "第" << chess->GetX() << "行,\
	"<< "第" << chess->GetY() << "列" << endl;
}

//客户调用
int main()
{
	//创建象棋
	Chessman *chess = new Chessman("车",1,1);
	Display(chess);

	//创建负责人，并保存备忘录
	MementoCaretaker *mc = new MementoCaretaker();
	mc->SetMemento(chess->CreateMemento());

	//更改象棋状态
	chess->SetY(4);
	Display(chess);

	//恢复象棋上次状态
	chess->RestoreMemento(mc->GetMemento());
	Display(chess);

	return 0;
}