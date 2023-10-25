#include "../include/cappuccino.h"
#include "../include/sub_ingredients.h"
#include <iostream>

Cappuccino::Cappuccino() {
    this->name = "Cappuccino";
    this->ingredients.push_back(new Espresso(2));
    this->ingredients.push_back(new Milk(2));
    this->ingredients.push_back(new MilkFoam(1));
}

Cappuccino::Cappuccino(const Cappuccino& esp) {
    this->name = esp.name;
    for (auto i : esp.ingredients) {
        this->ingredients.push_back(new Ingredient(*i));
    }
    for (auto i : esp.side_items){
        this->side_items.push_back(new Ingredient(*i));
    }
}

void Cappuccino::operator=(const Cappuccino& esp) {
    if (this != &esp) {
        this->name = esp.name;
        for(const auto& i :ingredients)
            delete i;
         for(const auto& i :side_items)
            delete i;
        ingredients.clear();
        side_items.clear();
        for (auto i : esp.ingredients) {
            this->ingredients.push_back(new Ingredient(*i));
        }
        for (auto i : esp.side_items){
            this->side_items.push_back(new Ingredient(*i));
        }
    }
}

Cappuccino::~Cappuccino(){
    for(const auto& i :ingredients)
        delete i;
    for(const auto& i :side_items)
        delete i;
    ingredients.clear();
    side_items.clear();
}

std::string Cappuccino::get_name(){
    return name;
}

double Cappuccino::price(){
    double price=0;
    for (auto i : ingredients){
        price += (*i).price();
    }
    for (auto i : side_items){
        price += (*i).price();
    }
    return price;
}

void Cappuccino::add_side_item(Ingredient* side){
    side_items.push_back(side);
}

std::vector<Ingredient*>& Cappuccino::get_side_items(){
    return side_items;
}