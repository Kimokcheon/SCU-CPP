// mocha.cpp
#include "mocha.h"
#include "ingredient.h"
#include "sub_ingredients.h"

Mocha::Mocha() : side_item() {
    name = "Mocha";
    ingredients.push_back(new Espresso(2));
    ingredients.push_back(new Milk(2));
    ingredients.push_back(new MilkFoam(1));
    ingredients.push_back(new Chocolate(1));
}

Mocha::Mocha(const Mocha& moc) {
    this->name = moc.get_name();
    for (const auto& c : moc.ingredients) {
        this->ingredients.push_back(c->Newself());
    }
    for (const auto& c : moc.side_item) {
        add_side_item(c);
    }
}

Mocha::~Mocha() {
    for (const auto& item : side_item) {
        delete item;
    }
    side_item.clear();
}

void Mocha::operator=(const Mocha& moc) {
    Mocha _moc = moc;
    this->name = moc.get_name();
    this->ingredients.clear();
    this->side_item.clear();
    for (const auto& c : _moc.ingredients) {
        this->ingredients.push_back(c->Newself());
    }
    for (const auto& c : _moc.side_item) {
        add_side_item(c);
    }
}

std::string Mocha::get_name() const { return name; }

double Mocha::price() {
    double _price;
    for (auto v : ingredients)
        _price += v->price();
    for (auto v : side_item)
        _price += v->price();
    return _price;
}

void Mocha::add_side_item(Ingredient* side) {
    side_item.push_back(side);
}

std::vector<Ingredient*>& Mocha::get_side_item() {
    return side_item;
}