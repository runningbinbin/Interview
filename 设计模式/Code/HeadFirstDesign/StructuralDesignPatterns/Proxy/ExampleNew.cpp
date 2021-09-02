/*
* @Description: 使用“代理模式”设计的收费商用查询系统
*/

#include <stdio.h>
#include <iostream>

using namespace std;


//身份验证
class AccessValidator
{
public: 
	//模拟实现登录验证
	bool Validate(string user_id) 
    {
	    cout << "在数据库中验证用户中..." << endl;

	    if (user_id == "杨过") 
	    {
		    cout << "登录成功！" << endl;
		    return true;
	    }
	    else 
	    {
            cout << "登录失败！" << endl;
		    return false;
	    }
    }
};

//日志类
class Logger
{
public: 
	//模拟实现日志记录
	void Log(string user_id) 
	{
        cout << "更新数据库，查询次数加1！" << user_id << endl;
    }
};

//抽象查询-抽象主题
class Searcher
{
public:	
	//查询信息
    virtual string DoSearch(string user_id, string keyword) = 0;
};

//具体查询-真实主题
class RealSearcher : public Searcher
{
public:
	//模拟查询商务信息
 	string DoSearch(string user_id, string keyword) 
 	{
        cout << "用户" << user_id << "使用关键词" << keyword <<"查询商务信息" << endl;
	    
	    return "返回具体内容";
    }
};

//代理查询-代理主题
class ProxySearcher : public Searcher
{
public:
	ProxySearcher()
	{
		//维持一个对真实主题的引用
		searcher = new RealSearcher(); 
	}

public:
    string DoSearch(string user_id, string keyword) 
    {
        //如果身份验证成功，则执行查询
        if (Validate(user_id))
        {
        	//调用真实主题对象的查询方法
            string result = searcher->DoSearch(user_id, keyword); 
            //记录查询日志
            Log(user_id); 

            return result; 
        }
        else
        {
            return NULL;
        }
    }

    //创建访问验证对象并调用其Validate()方法实现身份验证
    bool Validate(string user_id)
    {
        return validator.Validate(user_id);
    }

    //创建日志记录对象并调用其Log()方法实现日志记录
    void Log(string user_id)
    {
        logger.Log(user_id);
    }

private:
	RealSearcher *searcher;
	Logger logger;
	AccessValidator validator;  
};

//客户调用
int main()
{
	Searcher *searcher = new ProxySearcher();
	searcher->DoSearch("杨过","玉女心经");

	return 0;
}