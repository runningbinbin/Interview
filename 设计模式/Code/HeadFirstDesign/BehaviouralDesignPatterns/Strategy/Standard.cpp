/*
* @Description: “策略模式”标准代码
*/

#include <iostream>

using namespace std;

//抽象策略
class Strategy 
{
public:
	//声明抽象算法
 	virtual void Algorithm() = 0; 
};

//具体策略A
class ConcreteStrategyA : public Strategy 
{
public:	
    //算法的具体实现
    void Algorithm() 
    {
        //算法A
        cout << "ConcreteStrategyA Algorithm()" << endl;
    }
};

//具体策略B
class ConcreteStrategyB : public Strategy 
{
public: 
    //算法的具体实现
    void Algorithm() 
    {
        //算法B
        cout << "ConcreteStrategyB Algorithm()" << endl;
    }
};

//环境类
class Context 
{
public: 
	void SetStrategy(Strategy *strategy) 
	{
        this->strategy= strategy;
    }
 
    //调用策略类中的算法
    void Algorithm() 
    {
        strategy->Algorithm();
    }

private:
 	Strategy *strategy;     	//维持一个对抽象策略类的引用
};

//客户调用
int main()
{
	Context *context = new Context();
	context->SetStrategy(new ConcreteStrategyA());
	context->Algorithm();

    //动态切换算法
    context->SetStrategy(new ConcreteStrategyB());
    context->Algorithm();

	return 0;
}