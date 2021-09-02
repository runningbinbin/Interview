/*
* @Description:	采用“中介者模式”设计的客户信息管理系统
*/

#include <iostream>

using namespace std;

class Component;
class Button;
class List;
class ComboBox;
class TextBox;

//抽象中介者-声明
class Mediator
{
public:
	virtual void ComponentChanged(Component *c) = 0;	
};

//具体中介者-声明
class ConcreteMediator : public Mediator
{
public:
	void ComponentChanged(Component *c);
	void SetButton(Button *button);
	void SetList(List *list);
	void SetComboBox(ComboBox *combo_box);
	void SetTextBox(TextBox *text_box);

private:
	Button *button;
	List *list;
	ComboBox *combo_box;
	TextBox *text_box;
};

//抽象同事对象-声明
class Component
{
public:
	void SetMediator(Mediator *mediator);
	void Change();
	virtual void Update() = 0;

private:
	Mediator *mediator;		
};

//具体同事对象-声明
class Button : public Component
{
public:
	void Update();	
};
class List : public Component
{
public:
	void Update();	
	void Select();	
};
class ComboBox : public Component
{
public:
	void Update();	
	void Select();	
};
class TextBox : public Component
{
public:
	void Update();	
};

//具体中介者-定义
void ConcreteMediator::ComponentChanged(Component *c)
{
	if (button == c)
	{
		list->Update();
		combo_box->Update();
		text_box->Update();
	}	
	else if(list == c)
	{
		combo_box->Update();
		text_box->Update();
	}
	else if (combo_box == c)
	{
		list->Update();
		text_box->Update();
	}	
}
void ConcreteMediator::SetButton(Button *button)
{
	this->button= button;
}
void ConcreteMediator::SetList(List *list)
{
	this->list = list;
}
void ConcreteMediator::SetComboBox(ComboBox *combo_box)
{
	this->combo_box = combo_box;
}
void ConcreteMediator::SetTextBox(TextBox *text_box)
{
	this->text_box = text_box;
}

//抽象同事对象-定义
void Component::SetMediator(Mediator *mediator)
{
	this->mediator = mediator;
}
void Component::Change()
{
	mediator->ComponentChanged(this);
}

//具体同事对象-定义
void Button::Update()
{
	//按钮不产生交互
}
void List::Update()
{	
	cout << "List Update" << endl;
}
void List::Select()
{
	cout << "List Select" << endl;
}
void ComboBox::Update()
{
	cout << "ComboBox Update" << endl;
}
void ComboBox::Select()
{
	cout << "ComboBox Select" << endl;
}
void TextBox::Update()
{
	cout << "TextBox Update" << endl;
}


int main()
{
	ConcreteMediator *concrete_mediator = new ConcreteMediator();

	Button *button = new Button();
	List *list = new List();
	ComboBox *combo_box = new ComboBox();
	TextBox *text_box = new TextBox();

	button->SetMediator(concrete_mediator);
	list->SetMediator(concrete_mediator);
	combo_box->SetMediator(concrete_mediator);
	text_box->SetMediator(concrete_mediator);

	concrete_mediator->SetButton(button);
	concrete_mediator->SetList(list);
	concrete_mediator->SetComboBox(combo_box);
	concrete_mediator->SetTextBox(text_box);

	button->Change();
	list->Change();

	return 0;
}