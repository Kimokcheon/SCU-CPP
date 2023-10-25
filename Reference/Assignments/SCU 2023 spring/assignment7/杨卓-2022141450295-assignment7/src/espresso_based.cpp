#include "../include/espresso_based.h"
#include "../include/ingredient.h"

#include <vector>

// constructors

EspressoBased::EspressoBased(const EspressoBased& esp) {
    this->name = esp.get_name();
    for (auto e : esp.ingredients) {
        this->ingredients.push_back(e->Newself());
    }
}

// destructor

EspressoBased::~EspressoBased() {
    for (const auto& v : ingredients) {
        delete v;
    }
    ingredients.clear();
}

// copy constructor
void EspressoBased::operator=(const EspressoBased& esp) {
    this->name = esp.get_name();
    for (auto e : esp.ingredients) {
        this->ingredients.push_back(e->Newself());
    }
}

// member function
std::vector<Ingredient*>& EspressoBased::get_ingredients() {
    return this->ingredients;
}