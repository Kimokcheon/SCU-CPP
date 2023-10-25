#ifndef SUB_INGREDIENTS_H
#define SUB_INGREDIENTS_H

#include "ingredient.h"

#define DEFCLASS(Name, Price) \
class Name : public Ingredient \
{\
public:\
    Name(size_t units) : Ingredient{Price, units}{\
        this->name = #Name; \
    }\
    virtual std::string get_name() {return this->name;} \
    virtual double get_price_unit() const{return price_unit;} \
    virtual size_t get_units() const{return units;} \
    virtual double price() const{return price_unit * units;} \
};

DEFCLASS(Cinnamon, 5)
DEFCLASS(Chocolate, 5)
DEFCLASS(Sugar, 1)
DEFCLASS(Cookie, 10)
DEFCLASS(Espresso, 15)
DEFCLASS(Milk, 10)
DEFCLASS(MilkFoam, 5)
DEFCLASS(Water, 1)

#endif // SUB_INGREDIENTS_H
