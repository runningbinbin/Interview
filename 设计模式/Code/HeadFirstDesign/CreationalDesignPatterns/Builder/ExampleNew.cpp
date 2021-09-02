/*
* @Description:	使用“构建者模式”的游戏角色设计
*/

#include <stdio.h>
#include <iostream>
#include <list>

using namespace std;
	

//概念示例
//角色-产品
class Actor
{
public:
	void SetType(string type)
	{
		this->type = type;
	}
	string GetType()
	{
		return type;
	}

	void SetSex(string sex)
	{
		this->sex = sex;
	}
	string GetSex()
	{
		return sex;
	}

	void SetFace(string face)
	{
		this->face = face;
	}
	string GetFace()
	{
		return face;
	}

	void SetCustome(string custome)
	{
		this->custome = custome;
	}
	string GetCustome()
	{
		return custome;
	}
	void SetHairstyle(string hairstyle)
	{
		this->hairstyle = hairstyle;
	}
	string Gethairstyle()
	{
		return hairstyle;
	}

	void DisplayAll()
	{
		cout << type << "\n" \
		<< sex << "\n" \
		<< face << "\n" \
		<< custome << "\n"\
		<< hairstyle << endl;
	}

private:
	string type;			
	string sex;
	string face;
	string custome;
	string hairstyle;
};

//创建者-抽象创建者
class Builder
{
public:
	Builder()
	{
		actor = new Actor();
	}
	~Builder()
	{
		if (actor)
			delete actor;
	}

	virtual void BuildType() = 0;	
	virtual void BuildSex() = 0;	
	virtual void BuildFace() = 0;	
	virtual void BuildCustome() = 0;	
	virtual void BuildHairstyle() = 0;

	//钩子方法
	bool isBareheaded()
    {
        return false;
    }

	Actor* GetActor()
	{
		return actor;	
	}

protected:
	Actor *actor;	
};


//天使-具体创建者
class AngelBuilder : public Builder
{
public:
	void BuildType()
	{
		actor->SetType("Angle");
	}
	void BuildSex()
	{
		actor->SetSex("Women");
	}
	void BuildFace()
	{
		actor->SetFace("Beautiful");
	}
	void BuildCustome()
	{
		actor->SetCustome("White Dress");
	}
	void BuildHairstyle()
	{
		actor->SetHairstyle("Long Hair");
	}
};

//恶魔-具体创建者
class DevilBuilder : public Builder
{
public:
	void BuildType()
	{
		actor->SetType("Devil");
	}
	void BuildSex()
	{
		actor->SetSex("Man");
	}
	void BuildFace()
	{
		actor->SetFace("Ugly");
	}
	void BuildCustome()
	{
		actor->SetCustome("Dark Coat");
	}
	void BuildHairstyle()
	{
		actor->SetHairstyle("no Hair");
	}
};

//主管(构建算法管理)
class Director
{
public:
	Director(Builder *builder)
	{
		this->builder = builder;
	}

	void SetBuilder(Builder *builder)
	{
		this->builder = builder;
	}

	Actor* ConstructActor()
	{
		builder->BuildType();
		builder->BuildSex();
		builder->BuildFace();
		builder->BuildCustome();
		builder->BuildHairstyle();

		return builder->GetActor();
	}

public:	
	Builder *builder;
};


//客户调用
int main()
{
	Director *director = new Director(new AngelBuilder());	
	Actor *angel = director->ConstructActor();

	angel->DisplayAll();
	
	director->SetBuilder(new DevilBuilder());
	Actor *devil = director->ConstructActor();
	
	devil->DisplayAll();

	return 0;
}