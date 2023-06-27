#include "cappuccino.h"
Cappuccino::Cappuccino()
{
	this->name = "Cappuccino";
	auto* espresso = new Espresso(2);
	auto* milk = new Milk(2);
	auto* milkfoam = new MilkFoam(1);
	ingredients.push_back(espresso);
	ingredients.push_back(milk);
	ingredients.push_back(milkfoam);
}
Cappuccino::Cappuccino(const Cappuccino& cap)
{
	//深拷贝
	this->name = cap.name;
	for(const auto& i : cap.ingredients)
	{
		Ingredient* temp = nullptr;
		if(i->get_name() == "Espresso")
		{
			temp = new Espresso(*dynamic_cast<Espresso*>(i));
		}
		else if(i->get_name() == "Milk")
		{
			temp = new Milk(*dynamic_cast<Milk*>(i));
		}
		else if(i->get_name() == "MilkFoam")
		{
			temp = new MilkFoam(*dynamic_cast<MilkFoam*>(i));
		}
		ingredients.push_back(temp);
	}
	for(const auto& i : cap.side_items)
	{
		Ingredient* temp = nullptr;
		if(i->get_name() == "Cinnamon")
		{
			temp = new Cinnamon(*dynamic_cast<Cinnamon*>(i));
		}
		else if(i->get_name() == "Chocolate")
		{
			temp = new Chocolate(*dynamic_cast<Chocolate*>(i));
		}
		else if(i->get_name() == "Sugar")
		{
			temp = new Sugar(*dynamic_cast<Sugar*>(i));
		}
		else if(i->get_name() == "Cookie")
		{
			temp = new Cookie(*dynamic_cast<Cookie*>(i));
		}
		else if(i->get_name() == "Espresso")
		{
			temp = new Espresso(*dynamic_cast<Espresso*>(i));
		}
		else if(i->get_name() == "Milk")
		{
			temp = new Milk(*dynamic_cast<Milk*>(i));
		}
		else if(i->get_name() == "MilkFoam")
		{
			temp = new MilkFoam(*dynamic_cast<MilkFoam*>(i));
		}
		else if(i->get_name() == "Water")
		{
			temp = new Water(*dynamic_cast<Water*>(i));
		}
		side_items.push_back(temp);
	}
}
double Cappuccino::price()
{
	double res = 0;
	for(const auto& i : ingredients)
	{
		if (i != nullptr)
			res += i->get_price_unit() * (double)i->get_units();
	}
	for(const auto& i : side_items)
	{
		if(i != nullptr)
			res += i->get_price_unit() * (double)i->get_units();
	}
	return res;
}
std::string Cappuccino::get_name()
{
	return name;
}
std::vector<Ingredient*>& Cappuccino::get_side_items()
{
	return side_items;
}
void Cappuccino::add_side_item(Ingredient* side)
{
	side_items.push_back(side);
}
Cappuccino::~Cappuccino()
{
	side_items.clear();
//	std::cout << "Cappuccino destructor called" << std::endl;
}
void Cappuccino::operator=(const Cappuccino& cap)
{
	if(this == &cap) return;
	this->side_items.clear();
	this->ingredients.clear();
	this->name = cap.name;
	for(const auto& i : cap.ingredients)
	{
		Ingredient* temp = nullptr;
		if(i->get_name() == "Espresso")
		{
			temp = new Espresso(*dynamic_cast<Espresso*>(i));
		}
		else if(i->get_name() == "Milk")
		{
			temp = new Milk(*dynamic_cast<Milk*>(i));
		}
		else if(i->get_name() == "MilkFoam")
		{
			temp = new MilkFoam(*dynamic_cast<MilkFoam*>(i));
		}
		ingredients.push_back(temp);
	}
	for(const auto& i : cap.side_items)
	{
		Ingredient* temp = nullptr;
		if(i->get_name() == "Cinnamon")
		{
			temp = new Cinnamon(*dynamic_cast<Cinnamon*>(i));
		}
		else if(i->get_name() == "Chocolate")
		{
			temp = new Chocolate(*dynamic_cast<Chocolate*>(i));
		}
		else if(i->get_name() == "Sugar")
		{
			temp = new Sugar(*dynamic_cast<Sugar*>(i));
		}
		else if(i->get_name() == "Cookie")
		{
			temp = new Cookie(*dynamic_cast<Cookie*>(i));
		}
		else if(i->get_name() == "Espresso")
		{
			temp = new Espresso(*dynamic_cast<Espresso*>(i));
		}
		else if(i->get_name() == "Milk")
		{
			temp = new Milk(*dynamic_cast<Milk*>(i));
		}
		else if(i->get_name() == "MilkFoam")
		{
			temp = new MilkFoam(*dynamic_cast<MilkFoam*>(i));
		}
		else if(i->get_name() == "Water")
		{
			temp = new Water(*dynamic_cast<Water*>(i));
		}
		side_items.push_back(temp);
	}
}