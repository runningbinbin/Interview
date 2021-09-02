/*
* @Description: 使用“迭代器模式”设计的 “煎饼屋”和“餐厅”的合并
*/

#include <stdio.h>
#include <stdbool.h>
#include <iostream>
#include <string>
#include <list>

using namespace std;

#define MAX_ITEMS	6

//单个菜单项目
class MenuItem
{
public:
	MenuItem(string name = "", string description = "", double price = 0) 
	{	
		if (name != "")
			this->name = name;

		if (description != "")
			this->description = description;

		if (0 != price)
			this->price = price;
	}

public:
	string GetName()
	{
		return this->name;
	}

	string GetDescription()
	{
		return this->description;
	}

	double GetPrice()
	{
		return this->price;
	}

private:
	string name;			//菜名
	string description;		//描述
	double price;			//价格
};


//抽象迭代器
class Iterator
{
public:	
	virtual bool HasNext() = 0;
	virtual MenuItem* Next() = 0;
};

//菜单接口
class Menu
{
public:
	virtual Iterator* CreateIterator() = 0;
};

//煎饼屋菜单-声明
class PancakeHouseMenu : public Menu  
{
public:
	PancakeHouseMenu();
	~PancakeHouseMenu();

public:
	void AddItem(string Name, string Description, double Price);
	Iterator* CreateIterator();
	list<MenuItem> *GetMenuitems();

private:
	list<MenuItem> menu_items; 
	Iterator* iter; 			//方便释放	
};

//添加迭代器的餐厅菜单
class DinerMenu : public Menu
{
public:
	DinerMenu();
	~DinerMenu();

public:
	void AddItem(string Name, string Description, double Price);
	Iterator* CreateIterator();
	MenuItem* GetMenuItems();

private:	
	MenuItem *menu_items;
	int num;
	Iterator* iter; 		//方便释放	
};


//煎饼屋迭代器声明-具体迭代器
class PancakeHouseMenuIterator : public Iterator
{
public:
	PancakeHouseMenuIterator(PancakeHouseMenu *pancake_house_menu);

public:	
	bool HasNext();
	MenuItem* Next();

private:	
	list<MenuItem> *menu_items; 
	list<MenuItem>::iterator it; 		//迭代器，记录当前位置
};


//餐厅迭代器声明-具体迭代器
class DinerMenuIterator : public Iterator
{
public:
	DinerMenuIterator(DinerMenu *diner_menu);

public:
	bool HasNext();
	MenuItem* Next();
	

private:
	MenuItem *menu_items;	
	int index;
};


//煎饼屋菜单-定义
PancakeHouseMenu::PancakeHouseMenu()
{
	iter = NULL;
	AddItem("K&B Pacake Breakfast","Pancakes with scrambled eggs, and toast", 2.99);
	AddItem("Regular Pacake Breakfast","Pancakes with fried eggs, and sausage", 2.99);
	AddItem("Blueberry Pacake Breakfast","Pancakes with fresh blueberries", 3.49);
	AddItem("Waffles Pacake Breakfast","Waffles with you choice of blueburries", 3.59);
}
PancakeHouseMenu::~PancakeHouseMenu()
{
	if (iter)
		delete iter;
}
void PancakeHouseMenu::AddItem(string Name, string Description, double Price)
{
	MenuItem MenuItem(Name, Description, Price);
	menu_items.push_back(MenuItem);
}
Iterator* PancakeHouseMenu::CreateIterator()
{
	if (NULL == iter)
		iter = new PancakeHouseMenuIterator(this);

	return iter;
}
list<MenuItem> *PancakeHouseMenu::GetMenuitems()
{
	return &menu_items;
}


//餐厅菜单-定义
DinerMenu::DinerMenu()
{	
	num = 0;
	this->menu_items = new MenuItem[MAX_ITEMS]();
	iter = NULL;
	AddItem("Vegetarian BLT","Bacon with lettuce & tomato on whole wheat", 2.99);
	AddItem("BLT","Bacon with lettuce & tomato on whole wheat", 2.99);
	AddItem("Soup of the day","Soup of the day, with a side of potato salad", 3.29);
	AddItem("Hotdog","A hot dog with saurkraut, relish, onions, topped with cheese", 3.05);
}
DinerMenu::~DinerMenu()
{
	delete [] this->menu_items;
	if (iter)
		delete iter;
	iter = NULL;
}
void DinerMenu::AddItem(string Name, string Description, double Price)
{
	MenuItem MenuItem(Name, Description, Price);
	if (MAX_ITEMS <= this->num)
	{
		cout << "sorry, menu is full! Can not add item to menu" << endl;
	}	
	else 
	{
		this->menu_items[this->num] = MenuItem;
		this->num++;
	}
}
Iterator* DinerMenu::CreateIterator()
{
	if (NULL == iter)
		iter = new DinerMenuIterator(this);

	return iter;
}
MenuItem* DinerMenu::GetMenuItems()
{
	return menu_items;
}

//煎饼屋迭代器定义
PancakeHouseMenuIterator::PancakeHouseMenuIterator(PancakeHouseMenu *pancake_house_menu)
{
	this->menu_items = pancake_house_menu->GetMenuitems();
	it = this->menu_items->begin();
}
bool PancakeHouseMenuIterator::HasNext()
{
	if (it == menu_items->end())
		return false;
	else
		return true; 
}
MenuItem* PancakeHouseMenuIterator::Next()
{
	return &(*this->it++);
}

//餐厅迭代器定义
DinerMenuIterator::DinerMenuIterator(DinerMenu *diner_menu)
{
	this->menu_items = diner_menu->GetMenuItems();
	index = 0;
}
bool DinerMenuIterator::HasNext()
{
	if (MAX_ITEMS <= this->index || "" == this->menu_items[this->index].GetName())
		return false;
	else
		return true; 
}
MenuItem* DinerMenuIterator::Next()
{
	MenuItem* menu_item = &menu_items[this->index];
	this->index++;
	return menu_item;
}


class Waiter
{
public:
	void AddMenu(Menu *menu)
	{
		menus.push_back(menu);
	}

	//打印菜单
	void PrintMenu()
	{
		for (auto &m : menus)
		{
			PrintMenu(m->CreateIterator());
		}
	}

	void PrintMenu(Iterator* Iterator)
	{
		while(Iterator->HasNext())
		{
			MenuItem *p = (MenuItem*)Iterator->Next();
			cout << p->GetName() << " " << p->GetPrice() << " " << p->GetDescription() << endl; 
		}
	}

private:	
	list <Menu *> menus;
};

//客户调用
int main()
{
	Waiter Waiter;
	Waiter.AddMenu(new PancakeHouseMenu());
	Waiter.AddMenu(new DinerMenu());
	Waiter.PrintMenu();

	return 0;
}