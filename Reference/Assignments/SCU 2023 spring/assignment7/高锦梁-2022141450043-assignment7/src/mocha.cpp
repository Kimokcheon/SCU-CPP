#include "mocha.h"
#include "sub_ingredients.h"

Mocha::Mocha(const Mocha& other)  : EspressoBased(other) {
    for (const auto& i : other.side_items) {
        side_items.push_back(i->clone());
    }
    for (const auto& i : other.ingredients) {
        ingredients.push_back(i->clone());
    }
    name = other.name;
}

Mocha& Mocha::operator=(const Mocha& other) {
    if (this != &other) {
        for (const auto& i : side_items) {
            delete i;
        }
        side_items.clear();
        for (const auto& i : other.side_items) {
            side_items.push_back(i->clone());
        }
    }
    return *this;
}

Mocha::~Mocha() {
    for (const auto& i : side_items) {
        delete i;
    }
    side_items.clear();
}

Mocha::Mocha() {
    auto espresso = new Espresso(2);
    auto milk = new Milk(2);
    auto milk_foam = new MilkFoam(1);
    auto chocolate = new Chocolate(1);
    this->ingredients.push_back(espresso);
    this->ingredients.push_back(milk);
    this->ingredients.push_back(milk_foam);
    this->ingredients.push_back(chocolate);
}


std::string Mocha::get_name() {
    return "Mocha";
}

double Mocha::price() {
    double sum = 0;
    for(auto item : ingredients){
        sum += item->price();
    }
    for(auto item : side_items){
        sum += item->price();
    }
    return sum;
}

void Mocha::add_side_item(Ingredient* side) {
    this->side_items.push_back(side);
}

std::vector<Ingredient *> &Mocha::get_side_items() {
    return this->side_items;
}