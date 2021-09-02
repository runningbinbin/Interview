/*
* @Description: “煎饼屋”和“餐厅”的合并 最初设计
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


//煎饼屋菜单 (list存储单个菜单项目)
class PancakeHouseMenu
{
public:
	PancakeHouseMenu()
	{
		AddItem("K&B Pacake Breakfast","Pancakes with scrambled eggs, and toast", 2.99);
		AddItem("Regular Pacake Breakfast","Pancakes with fried eggs, and sausage", 2.99);
		AddItem("Blueberry Pacake Breakfast","Pancakes with fresh blueberries", 3.49);
		AddItem("Waffles Pacake Breakfast","Waffles with you choice of blueburries", 3.59);
	}

public:
	void AddItem(string name, string description, double price)
	{
		MenuItem menu_item(name, description, price);
		this->menu_items.push_back(menu_item);
	}

	list<MenuItem> GetMenuItems()
	{
		return this->menu_items;
	}

private:
	list<MenuItem> menu_items; 
};


//餐厅菜单实现（数组存储单个菜单项目）
class DinerMenu
{
public:
	DinerMenu()
	{	
		num = 0;
		this->menu_items = new MenuItem[MAX_ITEMS]();
		AddItem("Vegetarian BLT","Bacon with lettuce & tomato on whole wheat", 2.99);
		AddItem("BLT","Bacon with lettuce & tomato on whole wheat", 2.99);
		AddItem("Soup of the day","Soup of the day, with a side of potato salad", 3.29);
		AddItem("Hotdog","A hot dog with saurkraut, relish, onions, topped with cheese", 3.05);
	}
	~DinerMenu()
	{
		delete [] this->menu_items;
	}

public:
	void AddItem(string name, string description, double price)
	{
		MenuItem menu_item(name, description, price);
		if (MAX_ITEMS <= this->num)
		{
			cout << "sorry, menu is full! Can not add item to menu" << endl;
		}	
		else 
		{
			this->menu_items[this->num] = menu_item;
			this->num++;
		}
	}

	MenuItem * GetMenuItems()
	{
		return menu_items;
	}

	int GetNum()
	{
		return num;
	}


private:	
	MenuItem *menu_items;
	int num;		
};


//合并的餐厅和煎饼屋
class Waiter
{
public:
	Waiter(PancakeHouseMenu *pancake_house_menu,DinerMenu *diner_menu)
	{
		this->pancake_house_menu = pancake_house_menu;
		this->diner_menu = diner_menu;
	}

public:
	//打印菜单
	void PrintMenu()
	{
		list<MenuItem> breakfast_items = this->pancake_house_menu->GetMenuItems(); 
		MenuItem *LunchItems = this->diner_menu->GetMenuItems();

		list<MenuItem>::iterator it; 	
		for (it = breakfast_items.begin(); it != breakfast_items.end(); it++)
		{
			cout << it->GetName() << " " << it->GetPrice() << " " << it->GetDescription() << endl; 
		}

		for (int i = 0; i < diner_menu->GetNum();i++)
		{
			MenuItem *p = &LunchItems[i];
			cout << p->GetName() << " " << p->GetPrice() << " " << p->GetDescription() << endl; 
		} 
	}

private:	
	PancakeHouseMenu *pancake_house_menu;
	DinerMenu *diner_menu;
};

int main()
{
	Waiter waiter(new PancakeHouseMenu(), new DinerMenu());
	waiter.PrintMenu();

	return 0;
}