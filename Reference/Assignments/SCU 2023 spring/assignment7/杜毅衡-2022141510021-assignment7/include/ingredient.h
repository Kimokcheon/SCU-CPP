#ifndef INGREDIENT_H
#define INGREDIENT_H
#include <string>

class Ingredient{
public:
    double get_price_unit() { return price_unit; }
    size_t get_units() { return units; }
    virtual std::string get_name(){ return name; }
    double price() { return price_unit * units; }
protected:
    Ingredient(double price_unit, size_t units) : 
            price_unit(price_unit), units(units), name("Unknown") {};
    double price_unit;
    size_t units;
    std::string name;
};


#endif // INGREDIENT_H
