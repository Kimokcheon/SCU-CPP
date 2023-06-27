#ifndef SUB_INGREDIENTS_H
#define SUB_INGREDIENTS_H
#include "ingredient.h"
#include <string>
#define DEFCLASS(Name, price)\
class Name : public Ingredient\
{                                  \
public:                             \
	Name() = default;                  \
    ~Name() = default;                                \
	Name(size_t units) : Ingredient(price, units)            \
    {                                         \
        this -> name = #Name;\
    }    	                                     \
    std::string get_name() override {return this->name;}\
};
DEFCLASS(Cinnamon, 5);
DEFCLASS(Chocolate, 5);
DEFCLASS(Sugar, 1);
DEFCLASS(Cookie, 10);
DEFCLASS(Espresso, 15);
DEFCLASS(Milk, 10);
DEFCLASS(MilkFoam, 5);
DEFCLASS(Water, 1);

#endif // SUB_INGREDIENTS_H
