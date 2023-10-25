#ifndef SUB_INGREDIENTS_H
#define SUB_INGREDIENTS_H

#include "ingredient.h"

#include <iostream>
#include <cstring>

// macro define
#define DEFCLASS(NAME, PRICE)                                   \
class NAME : public Ingredient {                                \
public:                                                         \
    NAME(std::size_t units) : Ingredient(PRICE, units) {        \
        this->name = #NAME;                                     \
    }                                                           \
    std::string get_name() override { return name; }            \
    NAME* Newself() override { return new NAME(this->units); }  \
};                                                              \

// class define
DEFCLASS(Cinnamon, 5);
DEFCLASS(Chocolate, 5);
DEFCLASS(Sugar, 1);
DEFCLASS(Cookie, 10);
DEFCLASS(Espresso, 15);
DEFCLASS(Milk, 10);
DEFCLASS(MilkFoam, 5);
DEFCLASS(Water, 1);

#endif // SUB_INGREDIENTS_H