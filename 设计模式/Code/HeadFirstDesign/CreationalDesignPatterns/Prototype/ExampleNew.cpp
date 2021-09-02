/*
* @Description:	使用“原型模式”设计的工作周报
*/

#include <stdio.h>
#include <iostream>

using namespace std;


//抽象日志-抽象原型
class Prototype
{
public:
	virtual string GetName() = 0;	
	virtual void SetName(string attr) = 0;

	virtual string GetDate() = 0;	
	virtual void SetDate(string date) = 0;

	virtual string GetContent() = 0;	
	virtual void SetContent(string content) = 0;

	virtual Prototype *Clone() = 0;	
};

//具体日志-具体原型
class WeeklyLogProrotype : public Prototype
{
public:
	string GetName()
	{
		return name;
	}
	void SetName(string name)
	{
		this->name = name;
	}

	string GetDate()
	{
		return date;
	}
	void SetDate(string date)
	{
		this->date = date;
	}

	string GetContent()
	{
		return content;
	}

	void SetContent(string content)
	{
		this->content = content;
	}

	//复制自身
	Prototype *Clone()
	{	
		Prototype *proto_type = new WeeklyLogProrotype(); 
		proto_type->SetName(name);
		proto_type->SetDate(date);
		proto_type->SetContent(content);

		return  proto_type;
	}

private:
	string name;
	string date;
	string content;	
};

//客户调用
int main()
{
	//先前的工作周报
	Prototype *log_pre = new WeeklyLogProrotype();
	log_pre->SetName("Lily");
	log_pre->SetDate("first week");
	log_pre->SetContent("this week is very busy!!!");
	cout << log_pre->GetName() << log_pre->GetDate() << log_pre->GetContent() << endl;

	//在先前的工作周报的基础上写现在的工作周报
	Prototype *log_aft = log_pre->Clone();
	log_aft->SetDate("second week");
	log_aft->SetContent("this week is very vacancy!!!");
	cout << log_aft->GetName() << log_aft->GetDate() << log_aft->GetContent() << endl;

	return 0;
}
