/*
* @Description: 影院售票系统最初设计
*/

#include <iostream>

using namespace std;



//电影票类
class MovieTicket 
{
public: 
	//设置原始票价
	void SetPrice(double price) 
	{
		this->price = price;
	}
	
	void SetType(string type) 
	{
		this->type = type;
	}
	//获取折扣后的价格
	double GetPrice() 
	{
		return this->Calculate();
	}
	
    //计算打折之后的票价
	double Calculate() 
	{
        //学生票折后票价计算
		if(this->type == "student") 
		{
			cout << "学生票：" <<endl;
		    return this->price * 0.8;
		}
        //儿童票折后票价计算
		else if((this->type == "children") && this->price >= 20 ) 
		{
			cout << "儿童票：" <<endl;
		    return this->price - 10;
		}
        //VIP票折后票价计算
		else if(this->type == "vip") 
		{
			cout << "VIP票：" << endl;;
		    cout << "增加积分！" <<endl;
			return this->price * 0.5;
		}
		//如果不满足任何打折要求，则返回原始票价
		else 
		{
			return this->price; 
		}
	}

private: 
	double price; 		//电影票价格
	string type; 		//电影票类型	
};

int main()
{
	MovieTicket *movie_ticket = new MovieTicket();
	double original_price = 60.0;
	movie_ticket->SetPrice(original_price);

	movie_ticket->SetType("student");
	cout << "原始价：" << original_price << "折扣后价：" << movie_ticket->GetPrice() << endl;

	movie_ticket->SetType("children");
	cout << "原始价：" << original_price << "折扣后价：" << movie_ticket->GetPrice() << endl;

	movie_ticket->SetType("vip");
	cout << "原始价：" << original_price << "折扣后价：" << movie_ticket->GetPrice() << endl;
	return 0;
}