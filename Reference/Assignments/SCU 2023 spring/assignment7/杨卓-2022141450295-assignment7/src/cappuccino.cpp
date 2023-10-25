// cappuccino.cpp
#include "cappuccino.h"
#include "ingredient.h"
#include "sub_ingredients.h"

Cappuccino::Cappuccino() : side_items() {
    name = "Cappuccino";
    ingredients.push_back(new Espresso(2));
    ingredients.push_back(new Milk(2));
    ingredients.push_back(new MilkFoam(1));
}

Cappuccino::Cappuccino(const Cappuccino& cap) {
    this->name = cap.get_name();
    for (const auto& c : cap.ingredients) {
        this->ingredients.push_back(c->Newself());
    }
    for (const auto& c : cap.side_items) {
        add_side_item(c);
    }
}

Cappuccino::~Cappuccino() {
    for (const auto& item : side_items) {
        delete item;
    }
    side_items.clear();
}

void Cappuccino::operator=(const Cappuccino& cap) {
    Cappuccino _cap = cap;
    this->name = cap.get_name();
    this->ingredients.clear();
    this->side_items.clear();
    for (const auto& c : _cap.ingredients) {
        this->ingredients.push_back(c->Newself());
    }
    for (const auto& c : _cap.side_items) {
        add_side_item(c);
    }
}

std::string Cappuccino::get_name() const { return name; }

double Cappuccino::price() {
    double _price = 0;
    for (auto v : ingredients)
        _price += v->price();
    for (auto v : side_items)
        _price += v->price();
    return _price;
}

void Cappuccino::add_side_item(Ingredient* side) {
    side_items.push_back(side->Newself());
}

std::vector<Ingredient*>& Cappuccino::get_side_items() {
    return side_items;
}