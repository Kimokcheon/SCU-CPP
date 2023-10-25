#ifndef ESPRESSO_BASED_H
#define ESPRESSO_BASED_H

#include <vector>
#include <string>
#include "sub_ingredients.h"

class EspressoBased{
public:
    virtual std::string get_name()=0;
    virtual double price()=0;

    void brew();
    std::vector<Ingredient*>& get_ingredients();

    virtual ~EspressoBased();

protected:
    EspressoBased()=default;
    EspressoBased(const EspressoBased& esp);
    void operator=(const EspressoBased& esp);

    std::vector<Ingredient*> ingredients;
    std::string name;

};

#endif // ESPRESSO_BASED_H