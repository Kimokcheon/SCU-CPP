#include "espresso_based.h"
EspressoBased::~EspressoBased()
{
    for(const auto& i : ingredients){
        delete i;
    }
    ingredients.clear();
}

std::vector<Ingredient*>& EspressoBased:: get_ingredients(){
    return ingredients;
}

EspressoBased::EspressoBased(){}

EspressoBased::EspressoBased(const EspressoBased& esp){
    this->name=esp.name;
    for(auto i : esp.ingredients){
        this->ingredients.push_back(i->Copy());
    }
}

void EspressoBased::operator=(const EspressoBased& esp){
    if((&esp)==this) return;
    this->name=esp.name;
    this->ingredients.clear();
    for(auto i : esp.ingredients){
        this->ingredients.push_back(i->Copy());
    }
}

void EspressoBased::brew(){

}