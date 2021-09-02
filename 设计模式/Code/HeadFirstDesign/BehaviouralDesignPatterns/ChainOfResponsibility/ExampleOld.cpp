/*
* @Description:	分级审批最初设计
*/

#include <iostream>

using namespace std;

//采购请求类
class PurchaseRequest
{
public:
	PurchaseRequest(int mount)
	{
		this->mount = mount;
	}	

	//获取金额
	int GetAmount()
	{
		return mount;
	}

private:
	int mount;			//金额
};

//采购单处理类
class PurchaseRequestHandler 
{
public:
	//递交采购单给主任
	void SendRequestToDirector(PurchaseRequest *request) 
	{
		if (request->GetAmount() < 50000) 
		{
			//主任可审批该采购单
			this->HandleByDirector(request);
		}
		else if (request->GetAmount() < 100000) {
			//副董事长可审批该采购单
			this->HandleByVicePresident(request);
		}
		else if (request->GetAmount() < 500000) {
			//董事长可审批该采购单
			this->HandleByPresident(request);
		}
		else {
			//董事会可审批该采购单
			this->HandleByCongress(request);
		}
	}
	
	//主任审批采购单
	void HandleByDirector(PurchaseRequest *request) 
	{
		//代码省略
	}
	
	//副董事长审批采购单
	void HandleByVicePresident(PurchaseRequest *request) 
	{
		//代码省略
	}
	
	//董事长审批采购单
	void HandleByPresident(PurchaseRequest *request) 
	{
		//代码省略
	}
	
	//董事会审批采购单
	void HandleByCongress(PurchaseRequest *request) 
	{
		//代码省略
	}
};

//客户调用
int main()
{
	PurchaseRequestHandler *handle = new PurchaseRequestHandler();
	handle->SendRequestToDirector(new PurchaseRequest(5000));

	return 0;
}