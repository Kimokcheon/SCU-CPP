#include "cappuccino.h"
#include "sub_ingredients.h"

Cappuccino::Cappuccino(const Cappuccino& other) {
    for (const auto& i : other.side_items) {
        side_items.push_back(i->clone());
    }
    for(const auto& i : other.ingredients){
        ingredients.push_back(i->clone());
    }
    this->name = other.name;
}

Cappuccino& Cappuccino::operator=(const Cappuccino& other) {
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

Cappuccino::~Cappuccino() {
    for (const auto& i : side_items) {
        delete i;
    }
    side_items.clear();
}

Cappuccino::Cappuccino() {
    auto espresso = new Espresso(2);
    auto milk = new Milk(2);
    auto milk_foam = new MilkFoam(1);
    this->ingredients.push_back(espresso);
    this->ingredients.push_back(milk);
    this->ingredients.push_back(milk_foam);
}

std::string Cappuccino::get_name() {
    return "Cappuccino";
}

double Cappuccino::price() {
    double sum = 0;
    if (!this->ingredients.empty())
        for (auto item: ingredients) {
            sum += item->price();
        }
    if (!this->side_items.empty())
        for(auto item : side_items){
            sum += item->price();
        }
    return sum;
}

void Cappuccino::add_side_item(Ingredient* side) {
    this->side_items.push_back(side);
}

std::vector<Ingredient *> &Cappuccino::get_side_items() {
    return this->side_items;
}