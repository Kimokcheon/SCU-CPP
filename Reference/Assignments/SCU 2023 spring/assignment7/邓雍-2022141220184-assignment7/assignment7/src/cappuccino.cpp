#include "cappuccino.h"
#include "sub_ingredients.h"

std::vector<Ingredient*>& Cappuccino::get_side_items(){return side_items;}

std::string Cappuccino::get_name(){return name;}

Cappuccino::~Cappuccino()
{
    for(auto i : side_items) delete i;
    side_items.clear();
}

Cappuccino::Cappuccino()
{
    Ingredient* ptr=new Espresso(2);
    ingredients.push_back(new Espresso(2));
    ingredients.push_back(new Milk(2));
    ingredients.push_back(new MilkFoam(1));
    name="Cappuccino";
}

Cappuccino::Cappuccino(const Cappuccino& cap):EspressoBased(cap)
{
    for(auto i : cap.side_items){side_items.push_back(new Ingredient(*i));}
}

void Cappuccino::operator=(const Cappuccino& cap)
{
    if(this==&cap) return ;
    EspressoBased::operator=(cap);
    for(auto i : side_items) {delete i;}
    side_items.clear();
    for(auto i : cap.side_items){side_items.push_back(new Ingredient(*i));}
}

double Cappuccino::price()
{
    double Price=0;
    for(auto i : ingredients) Price+=i->price();
    for(auto i : side_items) Price+=i->price();
    return Price;
}

void Cappuccino::add_side_item(Ingredient* side)
{
    side_items.push_back(side);
}