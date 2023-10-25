#ifndef INGREDIENT_H
#define INGREDIENT_H

class Ingredient{
public:
    double get_price_unit(){return price_unit;}
    size_t get_units(){return units;}
    virtual std::string get_name()=0;

    double price(){return price_unit*units;}
    
    virtual Ingredient* newtype()=0; 

protected:
    Ingredient(double price_unit, size_t units){
        this->price_unit=price_unit;
        this->units=units;
    }

    double price_unit;
    size_t units;
    std::string name;
};

// double Ingredient::get_price_unit(){
//     return price_unit;
// }

// size_t Ingredient::get_units(){
//     return units;
// }

// double Ingredient::price(){
//     return price_unit*units;
// }

#endif // INGREDIENT_H