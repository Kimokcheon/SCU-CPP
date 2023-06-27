#ifndef INGREDIENT_H
#define INGREDIENT_H

#include <string>

class Ingredient {

public:
    double get_price_unit( ) {
        return price_unit;
    }
    size_t get_units( ) {
        return units;
    }
    std::string get_name( ) {
        return name;
    }

    double price() {
        return price_unit * units;
    }

    virtual ~Ingredient() = default;

protected:
    Ingredient(double price_unit, size_t units) : price_unit( price_unit ) , units( units ) {}

    double price_unit;
    size_t units;
    std::string name;

};

#endif // INGREDIENT_H