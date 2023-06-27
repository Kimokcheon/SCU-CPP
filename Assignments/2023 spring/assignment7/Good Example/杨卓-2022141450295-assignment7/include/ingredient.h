#ifndef INGREDIENT_H
#define INGREDIENT_H

#include <iostream>
#include <cstring>

class Ingredient {
public:
    double get_price_unit() { return price_unit; }
    std::size_t get_units() { return units; }
    virtual std::string get_name() = 0; // pure virtual function
    virtual Ingredient* Newself() = 0;

    double price() { return price_unit*units; }
protected:
    Ingredient(double price_unit, std::size_t units) :
        price_unit(price_unit), units(units), name("") {}

    double price_unit;
    std::size_t units;
    std::string name;
};

#endif // INGREDIENT_H