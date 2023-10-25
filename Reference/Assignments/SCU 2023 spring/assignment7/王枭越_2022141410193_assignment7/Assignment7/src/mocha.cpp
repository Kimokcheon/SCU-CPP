#include "../include/mocha.h"

void Mocha::add_side_item(Ingredient* side){
    side_items.push_back(side);
}

std::vector<Ingredient*>& Mocha::get_side_items(){
    return side_items;
}

std::string Mocha::get_name(){
    return name;
}

double Mocha::price(){
    double ret;
    for(auto it:ingredients){
        ret+=it->price();
    }
    for(auto it:side_items){
        ret+=it->price();
    }
    return ret;
}

Mocha::Mocha(){
    name="Mocha";
    ingredients.push_back(new Espresso(2));
    ingredients.push_back(new Milk(2));
    ingredients.push_back(new MilkFoam(1));
    ingredients.push_back(new Chocolate(1));
}

Mocha::~Mocha(){
    for(const auto& it:side_items)
        delete it;
    side_items.clear();
}

Mocha::Mocha(const Mocha& cap):EspressoBased(cap){
    // Mocha::~Mocha();//在拷贝中避免使用析构函数

    for(const auto& it:side_items)
        delete it;
    side_items.clear();

    name=cap.name;

    for(auto it:cap.side_items){
        side_items.push_back(it->newtype());
    }
}

void Mocha::operator=(const Mocha& cap){
    Mocha tmp(cap);
    // Mocha::~Mocha();//在拷贝中避免使用析构函数

    for(const auto& it:side_items)
        delete it;
    side_items.clear();

    for(const auto& i : ingredients)
        delete i;
    ingredients.clear();

    name=tmp.name;
    // ingredients=cap.ingredients;
    for(auto it:tmp.ingredients){
        ingredients.push_back(it->newtype());
    }
    // side_items=cap.side_items;
    for(auto it:tmp.side_items){
        side_items.push_back(it->newtype());
    }
}