#include "espresso_based.h"
#include "sub_ingredients.h"

EspressoBased::~EspressoBased(){
    for(const auto& i : ingredients)
        delete i;
    ingredients.clear();
}

std::vector<Ingredient*>& EspressoBased::get_ingredients(){
    return ingredients;
}

EspressoBased::EspressoBased() {
}

EspressoBased::EspressoBased(const EspressoBased &esp) {
    this->ingredients = esp.ingredients;
    this->name = esp.name;
}

EspressoBased& EspressoBased::operator=(const EspressoBased &esp) {
    this->ingredients = esp.ingredients;
    this->name = esp.name;
    return *this;
}

void EspressoBased::brew() {

}
