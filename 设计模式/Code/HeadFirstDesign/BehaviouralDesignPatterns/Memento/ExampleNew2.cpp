/*
* @Description:	采用“备忘录模式”设计的 “支持多步可撤销的象棋软件”
*/

#include <iostream>
#include <list>

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
		this->mementos.push_back(memento);
	}	

	ChessmanMemento *GetMemento(int index)
	{
		list <ChessmanMemento *>::iterator iter = mementos.begin();

		for (int i = 0;i < index;i++)
		{
			iter++;	
		}

		return *iter;
	}

private:
	list <ChessmanMemento *> mementos;	
};


//客户端
class Client
{
public:
	//下棋
	static void Play(Chessman *chess)
	{
		mc->SetMemento(chess->CreateMemento());

		index++;

		cout << "棋子" << chess->GetLabel() << \
		",当前位置" << "第" << chess->GetX() << "行,\
		"<< "第" << chess->GetY() << "列" << endl;
	}

	//悔棋
	static void Undo(Chessman *chess) 
	{
		cout << "悔棋" << endl;
		
		index--;

		//撤销到上一个备忘录
		chess->RestoreMemento(mc->GetMemento(index));
		
		cout << "棋子" << chess->GetLabel() << \
		",当前位置" << "第" << chess->GetX() << "行,\
		"<< "第" << chess->GetY() << "列" << endl;
	}

	//撤销悔棋
	static void Redo(Chessman *chess) 
	{
		cout << "撤销悔棋" << endl;
		
		index++;

		//恢复到下一个备忘录
		chess->RestoreMemento(mc->GetMemento(index));
		
		cout << "棋子" << chess->GetLabel() << \
		",当前位置" << "第" << chess->GetX() << "行,\
		"<< "第" << chess->GetY() << "列" << endl;
	}

	//测试
	void Test()
	{
		//创建象棋
		Chessman *chess = new Chessman("车",1,1);
		Play(chess);

		//更改象棋状态
		chess->SetY(4);
		Play(chess);

		//更改象棋状态
		chess->SetX(5);
		Play(chess);

		Undo(chess);
		Undo(chess);
		Redo(chess);
		Redo(chess);
	}

private:
	static 	MementoCaretaker *mc;		//负责人
	static int index;					//备忘录当前位置		
};

MementoCaretaker* Client::mc = new MementoCaretaker();
int Client::index = -1;

int main()
{
	
	Client c;
	c.Test();

	return 0;
}