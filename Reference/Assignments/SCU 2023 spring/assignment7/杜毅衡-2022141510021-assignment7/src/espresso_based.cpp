#include "../include/espresso_based.h"
#include <iostream>

EspressoBased::EspressoBased() {}

EspressoBased::EspressoBased(const EspressoBased& esp) {
    this->name = esp.name;
    for (auto i : esp.ingredients) {
        this->ingredients.push_back(new Ingredient(*i));
    }
}

void EspressoBased::operator=(const EspressoBased& esp) {
    if (this != &esp) {
        this->name = esp.name;
        for(const auto& i : ingredients)
            delete i;
        ingredients.clear();
        for (auto i : esp.ingredients) {
            this->ingredients.push_back(new Ingredient(*i));
        }
    }
}

EspressoBased::~EspressoBased(){
    for(const auto& i : ingredients)
        delete i;
    ingredients.clear();
}

std::string EspressoBased::get_name(){
    return name;
}

double EspressoBased::price(){
    double price=0;
    for (auto i : ingredients){
        price += (*i).price();
    }
    return price;
}

void EspressoBased::brew(){

    
}

std::vector<Ingredient*>& EspressoBased::get_ingredients(){
    return ingredients;
}
