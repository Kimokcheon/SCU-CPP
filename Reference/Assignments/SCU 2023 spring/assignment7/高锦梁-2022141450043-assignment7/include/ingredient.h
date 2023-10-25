#ifndef INGREDIENT_H
#define INGREDIENT_H

#include <string>

class Ingredient{
public:
   virtual double get_price_unit() const{
        return price_unit;
    }
   virtual size_t get_units() const{
        return units;
    }

    virtual std::string get_name(){
        return name;
    }
    virtual double price() const{
        return price_unit * (double)units;
    }

    Ingredient* clone() {
        return new Ingredient(*this);
    }

protected:
    Ingredient(double price_unit, size_t units){
        this->price_unit = price_unit;
        this->units = units;
    }

    double price_unit;
    size_t units;
    std::string name;
};
#endif // INGREDIENT_H