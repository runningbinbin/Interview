/*
* @Description:	采用“职责链模式”的分级审批
*/

#include <iostream>

using namespace std;

//请求类
class PurchaseRequest
{
public:
	PurchaseRequest(double mount,int number,string purpose)
	{
		this->mount = mount;
		this->number = number;
		this->purpose = purpose;
	}

	void SetMount(double mount)
	{
		this->mount = mount;
	}
	double GetMount()
	{
		return this->mount;
	}

	void SetNumber(int number)
	{
		this->number = number;
	}
	int GetNumber()
	{
		return this->number;
	}

	void SetPurpose(string purpose)
	{
		this->purpose = purpose;
	}
	string GetPurpose()
	{
		return this->purpose;
	}

public:
	double mount;
	int number;
	string purpose;
};

//抽象处理者
class Approver
{
public:	
	Approver(string name)
	{
		this->name = name;
	}

	void SetSuccessor(Approver *successor)
	{
		this->successor = successor;
	}

	virtual void ProcessRequest(PurchaseRequest *request) = 0;

public:
	Approver *successor;
	string name;	
};


//具体处理者-主任
class Director : public Approver
{
public:
	Director(string name) : Approver(name)
	{

	}

	void ProcessRequest(PurchaseRequest *request)
	{
		if (request->GetMount() < 50000) 
		{
			cout << "主任" << name << "审批采购单" << request->GetNumber() <<\
			 "金额" <<  request->GetMount() << "采购目的" << request->GetPurpose() << endl;	
		}
		else 
		{
			successor->ProcessRequest(request);
		}
	}

};

//具体处理者-副董事
class VicePresident : public Approver
{
public:
	VicePresident(string name) : Approver(name)
	{

	}

	void ProcessRequest(PurchaseRequest *request)
	{
		if (request->GetMount() < 100000) 
		{
			cout << "副董事" << name << "审批采购单" << request->GetNumber() <<\
			 "金额" <<  request->GetMount() << "采购目的" << request->GetPurpose() << endl;	
		}
		else 
		{
			successor->ProcessRequest(request);
		}
	}
};

//具体处理者-董事
class President : public Approver
{
public:
	President(string name) : Approver(name)
	{

	}

	void ProcessRequest(PurchaseRequest *request)
	{
		if (request->GetMount() < 500000) 
		{
			cout << "董事" << name << "审批采购单" << request->GetNumber() <<\
			 "金额" <<  request->GetMount() << "采购目的" << request->GetPurpose() << endl;	
		}
		else 
		{
			successor->ProcessRequest(request);
		}
	}
};

//具体处理者-董事会
class Congress : public Approver
{
public:
	Congress(string name) : Approver(name)
	{

	}

	void ProcessRequest(PurchaseRequest *request)
	{
		cout << "董事会" << name << "审批采购单" << request->GetNumber() <<\
			"金额" <<  request->GetMount() << "采购目的" << request->GetPurpose() << endl;	
	}
};

//客户调用
int main()
{
	Approver *wuji = new Director("张无忌");
	Approver *yangguo = new VicePresident("杨过");
	Approver *guojing = new President("郭靖");
	Approver *meeting = new Congress("董事会");

	wuji->SetSuccessor(yangguo);
	yangguo->SetSuccessor(guojing);
	guojing->SetSuccessor(meeting);

	
	wuji->ProcessRequest(new PurchaseRequest(45000,10001,"购买倚天剑"));

	wuji->ProcessRequest(new PurchaseRequest(60000,10002,"购买《葵花宝典》"));
	wuji->ProcessRequest(new PurchaseRequest(160000,10003,"购买《金刚经》"));
	wuji->ProcessRequest(new PurchaseRequest(800000,10004,"购买倚《桃花岛》"));

	return 0;
}