#ifndef INGREDIENT_H
#define INGREDIENT_H
#include <bits/stdc++.h>
class Ingredient
{
public:
    virtual ~Ingredient(){}
    double get_price_unit(){
        return price_unit;
    }
    size_t get_units(){
        return units;
    }
    std::string get_name(){
        return name;
    }
    double price(){
        return price_unit*units;
    }
    Ingredient* Copy(){
        auto p= new Ingredient(price_unit,units);
        p->name=name;
        return p;
    }

protected:
    Ingredient(double price_unit_, size_t units_):price_unit(price_unit_),units(units_){}
    double price_unit;
    size_t units;
    std::string name;
};
#endif // INGREDIENT_H