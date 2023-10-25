#include "../include/espresso_based.h"

EspressoBased::~EspressoBased(){
    for(const auto& i : ingredients)
        delete i;
    ingredients.clear();
}

std::vector<Ingredient*>& EspressoBased::get_ingredients(){
    return ingredients;
}

EspressoBased::EspressoBased(const EspressoBased& esp){
    for(const auto& i : ingredients)
        delete i;
    ingredients.clear();

    for(auto it:esp.ingredients){
        ingredients.push_back(it->newtype());
    }
}

void EspressoBased::operator=(const EspressoBased& esp){
    for(const auto& i : ingredients)
        delete i;
    ingredients.clear();
    
    for(auto it:esp.ingredients){
        ingredients.push_back(it->newtype());
    }
    this->name=esp.name;
}