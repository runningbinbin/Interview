/*
* @Description:	使用“抽象工厂模式”设计的“面向不同地区不同原料的统一原料工厂”
*/

#include <stdio.h>
#include <iostream>

using namespace std;
	
//饼	-抽象产品
class Dough
{
public:
	Dough()
	{

	}
};

//薄饼-具体产品	
class ThinCrustDough : public Dough
{
public:
	ThinCrustDough()
	{
		printf("ThinCrustDough\n");
	}
};
//厚饼-具体产品	
class ThickCrustDough : public Dough
{
public:
	ThickCrustDough()
	{
		printf("ThickCrustDough\n");
	}	
};


//酱料-抽象产品	
class Sauce
{
public:	
	Sauce()
	{

	}
};	
//Marinara酱料-具体产品	
class MarinaraSauce : public Sauce
{
public:	
	MarinaraSauce()
	{
		printf("MarinaraSauce\n");
	}	
};
//大蒜番茄酱料-具体产品	
class PlumTomatoSauce : public Sauce
{
public:	
	PlumTomatoSauce()
	{
		printf("PlumTomatoSauce\n");
	}	
};

//奶酪-抽象产品	
class Cheese
{
public:	
	Cheese()
	{

	}
};	
//Reggian奶酪-具体产品	
class ReggianCheese : public Cheese
{
public:	
	ReggianCheese()
	{
		printf("ReggianCheese\n");
	}
};
//Mozzarella奶酪	-具体产品
class MozzarellaCheese : public Cheese
{
public:	
	MozzarellaCheese()
	{
		printf("MozzarellaCheese\n");
	}	
};


//蔬菜-抽象产品
class Veggies
{
public:	
	Veggies()
	{

	}
};		

//大蒜-具体产品
class Garlic : public Veggies
{
public:	
	Garlic()
	{
		printf("Garlic\n");
	}
};
//蘑菇-具体产品
class Mushroom : public Veggies
{
public:	
	Mushroom()
	{
		printf("Mushroom\n");
	}	
};


//辣肠-抽象产品	
class Pepperoni
{
public:	
	Pepperoni()
	{

	}
};	
//切片辣肠-具体产品	
class SlicedPepperoni : public Pepperoni
{
public:	
	SlicedPepperoni()
	{
		printf("SlicedPepperoni\n");
	}	
};
//甜辣肠-具体产品	
class SweetPepperoni : public Pepperoni
{
public:	
	SweetPepperoni()
	{
		printf("SweetPepperoni\n");
	}	
};

//蛤蜊-抽象产品	
class Clam
{
public:	
	Clam()
	{

	}
};	
//新鲜蛤蜊-具体产品
class FreshClams : public Clam
{
public:	
	FreshClams()
	{
		printf("FreshClams\n");
	}	
};
//冷冻蛤蜊-具体产品
class FrozenClams : public Clam
{
public:	
	FrozenClams()
	{
		printf("FrozenClams\n");
	}	
};


//披萨原料工厂-抽象工厂
class PizzaIngredientFactory
{
public:
	virtual Dough* CreateDough() = 0;
	virtual Sauce* CreateSauce() = 0;
	virtual Cheese* CreateCheese() = 0;
	virtual Veggies* CreateVeggies() = 0;
	virtual Pepperoni* CreatePepperoni() = 0;
	virtual Clam* CreateClam() = 0;
};

//纽约原料工厂-具体工厂
class NYPizzaIngredientFactory : public PizzaIngredientFactory
{
	Dough* CreateDough()
	{
		return new ThinCrustDough();
	}

	Sauce* CreateSauce()
	{
		return new MarinaraSauce();
	}

	Cheese* CreateCheese()
	{
		return new ReggianCheese();
	}

	Veggies* CreateVeggies() 
	{
		return new Mushroom();
 	}

	Pepperoni* CreatePepperoni()
	{
		return new SlicedPepperoni();
	}

	Clam* CreateClam()
	{
		return new FreshClams();
	}
};


//芝加哥原料工-具体工厂
class ChicagoPizzaIngredientFactory : public PizzaIngredientFactory
{
	Dough* CreateDough()
	{
		return new ThickCrustDough();
	}

	Sauce* CreateSauce()
	{
		return new PlumTomatoSauce();
	}

	Cheese* CreateCheese()
	{
		return new MozzarellaCheese();
	}

	Veggies* CreateVeggies() 
	{
		return new Garlic();
 	}

	Pepperoni* CreatePepperoni()
	{
		return new SweetPepperoni();
	}

	Clam* CreateClam()
	{
		return new FrozenClams();
	}
};

//抽象披萨
class Pizza
{
public:
	Pizza()
	{
		//printf("pizza\n");
	}

public:
	//准备
	//收集所需原料
	virtual void prepare() = 0;

	//烘焙
	void bake()
	{
		printf("bake...\n");	
	}

	//切片
	void cut()
	{
		printf("cut...\n");	
	}

	//包装
	void box()
	{
		printf("box...\n");	
	}

	//设置名字
	void SetName(string Name)
	{
		this->name = Name;	
	}

	//获取名字
	string GetName()
	{
		return this->name;	
	}


public:	
	string name;			//名称
	Dough *dough;			//饼
	Sauce *sauce;			//酱料
	Veggies *veggies;		//蔬菜
	Cheese *cheese;			//奶酪
	Pepperoni *pepperoni;	//腊肠
	Clam *clam;				//蛤蜊			  
};

//奶酪披萨
class CheesePizza : public Pizza
{
public:	
	CheesePizza(PizzaIngredientFactory *pizza_ingredient_factory)
	{
		this->pizza_ingredient_factory = pizza_ingredient_factory;
	}

public:	
	void prepare()
	{
		cout << "preparing " << this->name << endl;
		this->dough = pizza_ingredient_factory->CreateDough();
		this->sauce = pizza_ingredient_factory->CreateSauce();
		this->cheese = pizza_ingredient_factory->CreateCheese();
	}	

public:	
	PizzaIngredientFactory *pizza_ingredient_factory;
};

//蛤蜊披萨
class ClamPizza : public Pizza
{
public:	
	ClamPizza(PizzaIngredientFactory *pizza_ingredient_factory)
	{
		this->pizza_ingredient_factory = pizza_ingredient_factory;
	}

public:	
	void prepare()
	{
		cout << "preparing " << this->name << endl;
		this->dough = pizza_ingredient_factory->CreateDough();
		this->sauce = pizza_ingredient_factory->CreateSauce();
		this->cheese = pizza_ingredient_factory->CreateCheese();
		this->clam = pizza_ingredient_factory->CreateClam();
	}	

public:	
	PizzaIngredientFactory *pizza_ingredient_factory;
};

//抽象披萨店-客户调用
class PizzaStore
{
public:
	PizzaStore(PizzaIngredientFactory *pizza_ingredient_factory)
	{
		this->pizza_ingredient_factory = pizza_ingredient_factory;
	}

public:
	//每个子类都会实现CreatePizza，同时使用PizzaStore的OrderPizza的方法
	void OrderPizza(string type)
	{	
		Pizza *pizza;
		pizza = CreatePizza(type);
		pizza->prepare();
		pizza->bake();
		pizza->cut();
		pizza->box();	
	}

	virtual Pizza* CreatePizza(string type) = 0;

public:	
	PizzaIngredientFactory *pizza_ingredient_factory;
};

//具体披萨店-客户调用
class NYPizzaStore : public PizzaStore
{
public:
	NYPizzaStore(PizzaIngredientFactory *pizza_ingredient_factory) : PizzaStore(pizza_ingredient_factory)
	{

	}

public:	
	Pizza* CreatePizza(string type)
	{
		Pizza *pizza = NULL;

	 	if (type == "cheese")
	 	{
	 		pizza = new CheesePizza(pizza_ingredient_factory);
			pizza->SetName("New York Style Cheese Pizza");
	 	}		
		else if (type == "clam")
		{
			pizza = new ClamPizza(pizza_ingredient_factory);
			pizza->SetName("New York Style Clam Pizza");
		}	
		return pizza;
	}
};

//具体披萨店-客户调用
class ChicagoPizzaStore : public PizzaStore
{
public:
	ChicagoPizzaStore(PizzaIngredientFactory *pizza_ingredient_factory) : PizzaStore(pizza_ingredient_factory)
	{

	}

public:	
	 Pizza* CreatePizza(string type)
	 {
	 	Pizza *pizza = NULL;

	 	if (type == "cheese")
	 	{
	 		pizza = new CheesePizza(pizza_ingredient_factory);
			pizza->SetName("Chicago Style Cheese Pizza");
	 	}		
		else if (type == "clam")
		{
			pizza = new ClamPizza(pizza_ingredient_factory);
			pizza->SetName("Chicago Style Clam Pizza");
		}	

		return pizza;
	 }
};


int main()
{
	//背景： 加盟店使用低价原料增加利润，必须采取手段，以免长此以往毁了对象村的品牌
	//纽约、芝加哥、加州的披萨都是使用相同的组件制造而成，但是每个区域对于这些组件却有不同的实现
	//抽象工厂定义：
	//	提供一个接口，用于创建相关或依赖对象的家族,而不需要明确具体类
	PizzaStore *nyPizzaStore = new NYPizzaStore(new NYPizzaIngredientFactory());
	nyPizzaStore->OrderPizza("cheese");

	PizzaStore *chicagoPizzaStore = new ChicagoPizzaStore(new ChicagoPizzaIngredientFactory());
	chicagoPizzaStore->OrderPizza("cheese");

	return 0;
}