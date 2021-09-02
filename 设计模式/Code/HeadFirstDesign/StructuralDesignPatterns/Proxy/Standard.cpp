/*
* @Description: “代理模式”标准代码
*/

#include <iostream>

using namespace std;

//抽象主题
class Subject
{
public:
 	virtual void Request() = 0;
};

//真实主题
class RealSubject : public Subject
{
public:
 	void Request()
    {
        //业务方法具体实现代码
        cout << "RealSubject Request()" << endl;
    }
};

//代理主题
class Proxy : public Subject
{
public:
	Proxy(Subject *real_subject)
	{
		//维持一个对真实主题对象的引用
		this->real_subject = real_subject;
	}

public: 
    void PreRequest() 
    {
        //请求前代理的操作
        cout << "Proxy PreRequest()" << endl;
    }
 
    void Request() 
    {
        PreRequest();
        //调用真实主题对象的方法
        real_subject->Request(); 
        PostRequest();
    }
 
    void PostRequest() 
    {
        //请求后代理的操作
        cout << "Proxy PostRequest()" << endl;
    }

private:
	Subject *real_subject;
};

//客户调用
int main()
{
	Subject *subject = new Proxy(new RealSubject());
	subject->Request();

	return 0;
}