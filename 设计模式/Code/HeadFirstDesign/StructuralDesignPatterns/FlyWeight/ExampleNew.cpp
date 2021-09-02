/*
* @Description: 使用“享元模式”设计的围棋软件中的棋子
*/

#include <iostream>
#include <map>
#include <iterator>

using namespace std;

//坐标类
class Coordinates
{
public:
	Coordinates(int x,int y)
	{
		this->x = x;
		this->y = y;
	}

	int GetX()
	{
		return x;
	}
	int GetY()
	{
		return y;
	}

	void SetX(int x)
	{
		this->x = x;
	}
	void SetY(int x)
	{
		this->y = y;
	}

private:
	int x;			//横坐标
	int y;			//纵坐标		
};

//棋子抽象类-抽象享元类
class IgoChesseman
{
public:
	virtual void Display(Coordinates *coord) = 0;

	virtual string GetColor() = 0;
};

//黑棋子具体类-具体享元类
class BlackIgoChesseman : public IgoChesseman
{
public:
	BlackIgoChesseman()
	{
		this->color = "黑色";
	}
public:
	void Display(Coordinates *coord)
	{
		cout << color << coord->GetX() << coord->GetY() << endl;
	}		

	string GetColor()
	{
		return color;
	}

private:
	//内部状态作为成员变量，同一个享元对象其内部状态一致
	string color;	
};

//白棋子具体类-具体享元类
class WhiteIgoChesseman : public IgoChesseman
{
public:
	WhiteIgoChesseman()
	{
		this->color = "白色";
	}
public:
	void Display(Coordinates *coord)
	{
		cout << color << coord->GetX() << coord->GetY() << endl;
	}		

	string GetColor()
	{
		return color;
	}

private:
	//内部状态作为成员变量，同一个享元对象其内部状态一致
	string color;	
};

//享元工厂类,此处工厂用的是单列模式
class IgoChessemanFactory 
{
private:
	IgoChessemanFactory()
	{
		IgoChessemans.insert(make_pair("b",new BlackIgoChesseman()));
		IgoChessemans.insert(make_pair("w",new BlackIgoChesseman()));
	}

public:
	static IgoChessemanFactory* GetInstance()
	{
		return factory;
	}

 	static IgoChesseman* GetIgoChesseman(string color)
 	{
        //如果对象存在，则直接从享元池获取
        map<string,IgoChesseman*>::iterator iter = IgoChessemans.find(color);
        if(iter != IgoChessemans.end())
        {
           	return iter->second;
        }
    }

private:
	//定义一个map用于存储享元对象，实现享元池
	static map<string,IgoChesseman*> IgoChessemans;

	static IgoChessemanFactory *factory;
};
map<string,IgoChesseman*> IgoChessemanFactory::IgoChessemans;
IgoChessemanFactory* IgoChessemanFactory::factory = new IgoChessemanFactory();;


//客户调用
int main()
{
	IgoChessemanFactory *factory = IgoChessemanFactory::GetInstance();

	IgoChesseman *black1 = factory->GetIgoChesseman("b");
	IgoChesseman *black2 = factory->GetIgoChesseman("b");
	IgoChesseman *black3 = factory->GetIgoChesseman("b");

	IgoChesseman *white1 = factory->GetIgoChesseman("w");
	IgoChesseman *white2 = factory->GetIgoChesseman("w");
	IgoChesseman *white3 = factory->GetIgoChesseman("w");

	black1->Display(new Coordinates(1,2));
	black2->Display(new Coordinates(3,4));
	black3->Display(new Coordinates(5,6));

	white1->Display(new Coordinates(7,8));
	white2->Display(new Coordinates(9,10));

	return 0;
}