#include "mocha.h"
#include "sub_ingredients.h"

std::vector<Ingredient*>& Mocha::get_side_items(){return side_items;}

std::string Mocha::get_name(){return name;}

Mocha::~Mocha()
{
    for(const auto& i : side_items)
        delete i;
    side_items.clear();
}

Mocha::Mocha()
{
    Ingredient* ptr=new Espresso(2);
    ingredients.push_back(new Espresso(2));
    ingredients.push_back(new Milk(2));
    ingredients.push_back(new MilkFoam(1));
    ingredients.push_back(new Chocolate(1));
    name="Mocha";
}

Mocha::Mocha(const Mocha& cap)
{
    for(auto i : cap.side_items){side_items.push_back(new Ingredient(*i));}
}

void Mocha::operator=(const Mocha& cap)
{
    if(this==&cap) return ;
    EspressoBased::operator=(cap);
    for(auto i : side_items) {delete i;}
    side_items.clear();
    for(auto i : cap.side_items){side_items.push_back(new Ingredient(*i));}
}

double Mocha::price()
{
    double Price=0;
    for(auto i : ingredients) Price+=i->price();
    for(auto i : side_items) Price+=i->price();
    return Price;
}

void Mocha::add_side_item(Ingredient* side)
{
    side_items.push_back(side);
}