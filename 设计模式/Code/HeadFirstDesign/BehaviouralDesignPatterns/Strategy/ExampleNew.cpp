/*
* @Description: 使用“策略模式”的影院售票系统 
*/
#include <iostream>

using namespace std;

//抽象折扣类-抽象策略
class Discount 
{
public:
 	virtual double Calculate(double price) = 0; 
};

class StudentDiscount : public Discount 
{
public:	
    double Calculate(double price) 
    {
    	return price * 0.8;
    }
};

//儿童折扣类-具体策略
class ChildrenDiscount : public Discount 
{
public:	
    double Calculate(double price) 
    {
    	if (price > 20)
    	{
    		price  = price - 10;
    	}

    	return price;
    }
};

//VIP折扣类-具体策略
class VipDiscount : public Discount 
{
public:	
    double Calculate(double price) 
    {
    	return price * 0.5;
    }
};

//电影票-环境类
class MovieTicket 
{
public: 
	//设置原始票价
	void SetPrice(double price) 
	{
		this->price = price;
	}
	//获取折扣后的价格
	double GetPrice() 
	{
		return this->Calculate();
	}

	void SetDiscount(Discount *discount) 
	{
        this->discount = discount;
    }
 
    //调用策略类中的算法
    double Calculate() 
    {
        return discount->Calculate(price);
    }

private:
 	Discount *discount;     	//维持一个对抽象策略类的引用
 	double price; 				//电影票价格
};

//客户调用
int main()
{
	MovieTicket *movie_ticket = new MovieTicket();
	double original_price = 60.0;
	movie_ticket->SetPrice(original_price);
	movie_ticket->SetDiscount(new StudentDiscount());
	cout << "原始价：" << original_price << "折扣后价：" << movie_ticket->GetPrice() << endl;

	movie_ticket->SetDiscount(new ChildrenDiscount());
	cout << "原始价：" << original_price << "折扣后价：" << movie_ticket->GetPrice() << endl;

	movie_ticket->SetDiscount(new VipDiscount());
	cout << "原始价：" << original_price << "折扣后价：" << movie_ticket->GetPrice() << endl;

	return 0;
}