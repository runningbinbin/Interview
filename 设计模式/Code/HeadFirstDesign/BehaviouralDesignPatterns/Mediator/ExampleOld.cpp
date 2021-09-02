/*
* @Description:	客户信息管理系统初步设计
*/

#include <iostream>

using namespace std;




class List;
class ComboBox;
class TextBox;

//按钮类-声明
class Button 
{
public:
    //界面组件的交互
	void Change();
	void Update(); 
	void Set(List *list,ComboBox *cb,TextBox *tb);

private:
	List *list;
	ComboBox *cb;
	TextBox *tb;
};

//列表框类-声明
class List 
{
public:
	//界面组件的交互
	void Change(); 
	void Update(); 
	void Set(ComboBox *cb,TextBox *tb);

private:
	ComboBox *cb;
	TextBox *tb;
};

//组合框类-声明
class ComboBox 
{
public:
	//界面组件的交互
	void Change(); 
	void Update(); 
	void Set(List *list,TextBox *tb);

private: 
	List *list;
	TextBox *tb;
};

//文本框类-声明
class TextBox 
{
public: 
	void Update();	
};

//按钮类-定义
void Button::Change() 
{
	list->Update();
	cb->Update();
	tb->Update();
}
void Button::Update() 
{
	cout << "Button Update" << endl;
}

void Button::Set(List *list,ComboBox *cb,TextBox *tb)
{
	this->list = list;
	this->cb = cb;
	this->tb = tb;
}

//列表框-定义
void List::Change() 
{
	cb->Update();
	tb->Update();
}
void List::Update() 
{
	cout << "List Update" << endl;
}
void List::Set(ComboBox *cb,TextBox *tb)
{
	this->cb = cb;
	this->tb = tb;
}

//组合框-定义
void ComboBox::Change() 
{
	list->Update();
	tb->Update();
}
void ComboBox::Update() 
{
	cout << "ComboBox Update" << endl;
}
void ComboBox::Set(List *list,TextBox *tb)
{
	this->list = list;
	this->tb = tb;
}

//文本框-定义
void TextBox::Update() 
{
	cout << "TextBox Update" << endl;
}

int main()
{
	Button *b = new Button();
	List *l = new List();
	ComboBox *c = new ComboBox();
	TextBox *t = new TextBox();

	b->Set(l,c,t);
	l->Set(c,t);
	c->Set(l,t);

	b->Change();
	l->Change();
	c->Change();

	return 0;	
}