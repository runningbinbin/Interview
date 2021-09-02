/*
* @Description:	使用“解释器模式”设计的“解析机器人控制指令软件”
*/
#include <iostream>
#include <vector>
#include <stack>

#include <string.h>
using namespace std;

//注：本实例对机器人控制指令的输出结果进行模拟，将英文指令翻译为中文指令，实际情况是调用不同的控制程序进行机器人的控制，包括对移动方向、方式和距离的控制等
 
//抽象表达式
class Node 
{
public:
	virtual string Interpret() = 0;
};
 
//And解释-非终结符表达式
class AndNode : public Node 
{
public: 
	AndNode(Node *left, Node *right) 
	{
		this->left = left;
		this->right = right;
	}
    
    //And表达式解释操作
	string Interpret() 
	{
		return left->Interpret() + "再" + right->Interpret();
	}

private: 
	Node *left; 	//And的左表达式
	Node *right; 	//And的右表达式	
};
 
//简单句子解释-非终结符表达式
class SentenceNode : public Node 
{
public: 
	SentenceNode(Node *direction,Node *action,Node *distance) 
	{
		this->direction = direction;
		this->action = action;
		this->distance = distance;
	}
    
    //简单句子的解释操作
	string Interpret() 
	{
		return direction->Interpret() + action->Interpret() + distance->Interpret();
	}

private: 
	Node *direction;
	Node *action;
	Node *distance;		
};
 
//方向解释-终结符表达式
class DirectionNode : public Node 
{	
public: 
	DirectionNode(string direction) 
	{
		this->direction = direction;
	}
	
    //方向表达式的解释操作
public: 
	string Interpret() 
	{
		if (direction == "up") 
		{
			return "向上";
		}
		else if (direction == "down") 
		{
			return "向下";
		}
		else if (direction == "left") 
		{
			return "向左";
		}
		else if (direction == "right") 
		{
			return "向右";
		}
		else 
		{
			return "无效指令";
		}
	}

private: 
	string direction;	
};
 
//动作解释-终结符表达式
class ActionNode : public Node 
{
public: 
	ActionNode(string action) 
	{
		this->action = action;
	}
	
    //动作（移动方式）表达式的解释操作
	string Interpret() 
	{
		if (action == "move") 
		{
			return "移动";
		}
		else if (action == "run") 
		{
			return "快速移动";
		}
		else 
		{
			return "无效指令";
		}
	}

private: 
	string action;	
};
 
//距离解释-终结符表达式
class DistanceNode : public Node 
{
public: 
	DistanceNode(string distance) 
	{
		this->distance = distance;
	}
	
	//距离表达式的解释操作
	string Interpret() 
	{
		return this->distance;
	}	

private: 
	string distance;	
};
 
void Split(char *str, vector<string> &arr)
{
	int i = 0;	
	const char *delim = " ";
	char *p = strtok(str,delim);
	while(p)
	{
		cout << p << endl;
		
		arr.push_back(p);	
		p = strtok(NULL,delim);
	}
}


//指令处理类：工具类
class InstructionHandler 
{
public: 
   	void Handle(char *instruction) 
   	{
    	Node *left = NULL;
    	Node *right = NULL;

    	Node *direction = NULL;
    	Node *action = NULL;
    	Node *distance = NULL;

    	stack<Node *> stacks; 				//声明一个栈对象用于存储抽象语法树
    	vector<string> words;

    	Split(instruction,words);					//以空格分隔指令字符串
    	for (int i = 0; i < words.size(); i++) 
    	{
			//本实例采用栈的方式来处理指令，如果遇到“and”，则将其后的三个单词作为三个终结符表达式连成一个简单句子SentenceNode作为“and”的右表达式，而将从栈顶弹出的表达式作为“and”的左表达式，最后将新的“and”表达式压入栈中。    		        
    		if (words[i] == "and") 
    		{
    			left = (Node *)stacks.top(); 	//弹出栈顶表达式作为左表达式
    			stacks.pop();

    		    string word1= words[++i];
    		    direction = new DirectionNode(word1);
    		    string word2 = words[++i];
    		    action = new ActionNode(word2);
    		    string word3 = words[++i];
    		    distance = new DistanceNode(word3);
    		    right = new SentenceNode(direction,action,distance); //右表达式
    			stacks.push(new AndNode(left,right)); //将新表达式压入栈中
    		}
            //如果是从头开始进行解释，则将前三个单词组成一个简单句子SentenceNode并将该句子压入栈中
    		else 
    		{
    		    string word1 = words[i];
    		    direction = new DirectionNode(word1);
    		    string word2 = words[++i];
    		    action = new ActionNode(word2);
    		    string word3 = words[++i];
    		    distance = new DistanceNode(word3);
    		    left = new SentenceNode(direction,action,distance);
    		    stacks.push(left); //将新表达式压入栈中
    		}
    	}
    	this->node = (Node*)stacks.top(); //将全部表达式从栈中弹出
    	stacks.pop();
    }	
	
	string Output() 
	{
		string result = node->Interpret(); //解释表达式
		return result;
	}

private: 
	Node *node;	
};

//客户调用
int main()
{
	char instruction[] = "up move 5 and down run 10 and left move 5";
	InstructionHandler handler;
	handler.Handle(instruction);
	cout << handler.Output() << endl;

	return 0;
}