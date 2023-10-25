#ifndef SUB_INGREDIENTS_H
#define SUB_INGREDIENTS_H

#include "ingredient.h"
#define DEFCLASS(NAME,PRICE)                            \
class NAME:public Ingredient{                           \
public:                                                 \
    NAME(size_t units):Ingredient{PRICE,units}{         \
        this->name = #NAME;                             \
    }                                                   \
                                                        \
    std::string get_name()override{return this->name;}  \
    Ingredient* newtype()override{                      \
        return new NAME(this->units);                   \
    }                                                   \
};                                                      \

DEFCLASS(Cinnamon,5)
DEFCLASS(Chocolate,5)
DEFCLASS(Sugar,1)
DEFCLASS(Cookie,10)
DEFCLASS(Espresso,15)
DEFCLASS(Milk,10)
DEFCLASS(MilkFoam,5)
DEFCLASS(Water,1)


// class Cinnamon:public Ingredient{
// public:
//     Cinnamon(size_t units):Ingredient{5,units}{
//         this->name = "Cinnamon";
//     }

//     std::string get_name()override{return this->name;}
//     Ingredient* newtype()override{
//         return new Cinnamon(this->units);
//     }
// };

// class Chocolate:public Ingredient{
// public:
//     Chocolate(size_t units):Ingredient{5,units}{
//         this->name = "Chocolate";
//     }

//     std::string get_name()override{return this->name;}
//     Ingredient* newtype()override{
//         return new Chocolate(this->units);
//     }
// };

// class Sugar:public Ingredient{
// public:
//     Sugar(size_t units):Ingredient{1,units}{
//         this->name = "Sugar";
//     }

//     std::string get_name()override{return this->name;}
//     Ingredient* newtype()override{
//         return new Sugar(this->units);
//     }
// };

// class Cookie:public Ingredient{
// public:
//     Cookie(size_t units):Ingredient{10,units}{
//         this->name = "Cookie";
//     }

//     std::string get_name()override{return this->name;}
//     Ingredient* newtype()override{
//         return new Cookie(this->units);
//     }
// };

// class Espresso:public Ingredient{
// public:
//     Espresso(size_t units):Ingredient{15,units}{
//         this->name = "Espresso";
//     }

//     std::string get_name()override{return this->name;}
//     Ingredient* newtype()override{
//         return new Espresso(this->units);
//     }
// };

// class Milk:public Ingredient{
// public:
//     Milk(size_t units):Ingredient{10,units}{
//         this->name = "Milk";
//     }

//     std::string get_name()override{return this->name;}
//     Ingredient* newtype()override{
//         return new Milk(this->units);
//     }
// };

// class MilkFoam:public Ingredient{
// public:
//     MilkFoam(size_t units):Ingredient{5,units}{
//         this->name = "MilkFoam";
//     }

//     std::string get_name()override{return this->name;}
//     Ingredient* newtype()override{
//         return new MilkFoam(this->units);
//     }
// };

// class Water:public Ingredient{
// public:
//     Water(size_t units):Ingredient{1,units}{
//         this->name = "Water";
//     }

//     std::string get_name()override{return this->name;}
//     Ingredient* newtype()override{
//         return new Water(this->units);
//     }
// };

#endif // SUB_INGREDIENTS_H