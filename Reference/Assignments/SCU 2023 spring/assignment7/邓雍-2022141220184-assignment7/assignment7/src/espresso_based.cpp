#include "espresso_based.h"

EspressoBased::EspressoBased( ) = default;

EspressoBased::~EspressoBased()
{
    for(auto i : ingredients) delete i;
    ingredients.clear();
    name.clear();
}

EspressoBased::EspressoBased(const EspressoBased& esp)
{
    for(auto i : esp.ingredients) ingredients.push_back(new Ingredient(*i));
    name=esp.name;
}

void EspressoBased::operator=(const EspressoBased& esp)
{
    if(this==&esp) return ;
    for(auto i : ingredients) delete i;
    ingredients.clear();
    for(auto i : esp.ingredients) ingredients.push_back(new Ingredient(*i));
    name=esp.name;
}

std::vector<Ingredient*>& EspressoBased::get_ingredients()
{
    return ingredients;
}