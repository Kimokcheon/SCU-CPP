#include "../include/cappuccino.h"

void Cappuccino::add_side_item(Ingredient* side){
    side_items.push_back(side);
}

std::vector<Ingredient*>& Cappuccino::get_side_items(){
    return side_items;
}

std::string Cappuccino::get_name(){
    return name;
}

double Cappuccino::price(){
    double ret;
    for(auto it:ingredients){
        ret+=it->price();
    }
    for(auto it:side_items){
        ret+=it->price();
    }
    return ret;
}

Cappuccino::Cappuccino(){
    name="Cappuccino";
    ingredients.push_back(new Espresso(2));
    ingredients.push_back(new Milk(2));
    ingredients.push_back(new MilkFoam(1));
}

Cappuccino::~Cappuccino(){
    for(const auto& it:side_items)
        delete it;
    side_items.clear();
}

Cappuccino::Cappuccino(const Cappuccino& cap):EspressoBased(cap){
    // Cappuccino::~Cappuccino();//在拷贝中避免使用析构函数

    for(const auto& it:side_items)
        delete it;
    side_items.clear();

    name=cap.name;

    for(auto it:cap.side_items){
        side_items.push_back(it->newtype());
    }
}

void Cappuccino::operator=(const Cappuccino& cap){
    //在重载等号的时候不好调用父类重载的等号，
    //因为有tmp=tmp的情况，所以先要被自己复制到一个实例中，再清空自己，
    //所以不好调用父类的重载的等号，
    //所以父类的等号其实没必要写
    Cappuccino tmp(cap);
    // Cappuccino::~Cappuccino();//在拷贝中避免使用析构函数

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