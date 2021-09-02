/*
* @Description:	“解释器模式”标准模式,以解析字符串“1 + 1”为例
*/

#include <iostream>
#include <map>
#include <stack>
#include <stdlib.h>
#include <string.h>
#include <vector>

using namespace std;


//环境类
class Context 
{
public: 
	//解析字符串到words，空格为间隔符
    Context(char *str)
	{
		const char *delim = " ";
		char *p = strtok(str,delim);
		while(p)
		{
			words.push_back(p);	
			p = strtok(NULL,delim);
		}
	}

	vector<string> &GetWords()
	{
		return words;
	}

public: 
	vector<string> words;
};

//抽象表达式
class Expression 
{
public:  
    virtual int Interpret(Context *ctx) = 0;
};

//终结符表达式
class TerminalExpression : public Expression 
{
public:  
	TerminalExpression(string value)
	{
		this->value = value;
	}

	int Interpret(Context *ctx) 
	{
        //终结符表达式的解释操作
        return atoi(value.c_str());
    } 

private:
	string value;    
};

//非终结符表达式(以加法为例)
class NonterminalExpression : public Expression 
{
public:  
   	NonterminalExpression(Expression *left,Expression *right) 
   	{
      	this->left = left;
      	this->right = right;
   	}

	int Interpret(Context *ctx) 
	{
		int sum = left->Interpret(ctx) + right->Interpret(ctx);
    	//递归调用每一个组成部分的Interpret()方法
      	//在递归调用时指定组成部分的连接方式，即非终结符的功能
      	cout << left->Interpret(ctx) << "+" << right->Interpret(ctx) << "=" << sum << endl;
		return sum; 
	}

private:  
	Expression *left;
	Expression *right;
};

//客户调用(解析字符串“1+1”为例)
int main()
{
	char buf[100] = "1 + 1";
	Context *context = new Context(buf);

	stack<Expression *> stacks; 				//声明一个栈对象用于存储抽象语法树
	Expression *left = NULL;

	vector<string> &words = context->GetWords();

	for (int i = 0; i < words.size(); i++) 
	{	
		cout << words[i] << endl;
		if (words[i] == "+")
		{
 			left = (Expression *)stacks.top(); 	//弹出栈顶表达式作为左表达式
			stacks.pop();

			stacks.push(new NonterminalExpression(left,new TerminalExpression(words[++i]))); //将新表达式压入栈中
		}
		else
		{
			stacks.push(new TerminalExpression(words[i])); //将新表达式压入栈中
		}
	}	

	Expression *expression = (Expression*)stacks.top(); //将全部表达式从栈中弹出
	expression->Interpret(context);

	return 0;
}