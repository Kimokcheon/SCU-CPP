#include "../include/mocha.h"

Mocha::Mocha() {
    this->name = "Mocha";
    this->ingredients.push_back(new Espresso(2));
    this->ingredients.push_back(new Milk(2));
    this->ingredients.push_back(new MilkFoam(1));
    this->ingredients.push_back(new Chocolate(1));
}

Mocha::Mocha(const Mocha& esp) {
    this->name = esp.name;
    for (auto i : esp.ingredients) {
        this->ingredients.push_back(new Ingredient(*i));
    }
    for (auto i : esp.side_items){
        this->side_items.push_back(new Ingredient(*i));
    }
}

void Mocha::operator=(const Mocha& esp) {
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

Mocha::~Mocha(){
    for(const auto& i :ingredients)
        delete i;
    for(const auto& i :side_items)
        delete i;
    ingredients.clear();
    side_items.clear();
}

std::string Mocha::get_name(){
    return name;
}

double Mocha::price(){
    double price=0;
    for (auto i : ingredients){
        price += (*i).price();
    }
    for (auto i : side_items){
        price += (*i).price();
    }
    return price;
}

void Mocha::add_side_item(Ingredient* side){
    side_items.push_back(side);
}

std::vector<Ingredient*>& Mocha::get_side_items(){
    return side_items;
}