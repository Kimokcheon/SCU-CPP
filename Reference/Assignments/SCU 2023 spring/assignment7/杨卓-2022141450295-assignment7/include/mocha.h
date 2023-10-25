// mocha.h
#ifndef MOCHA_H
#define MOCHA_H

#include "ingredient.h"
#include "espresso_based.h"

#include <iostream>
#include <cstring>
#include <vector>

class Mocha : public EspressoBased {
public:
    Mocha();
    Mocha(const Mocha& moc);
    ~Mocha() override;
    void operator=(const Mocha& moc);

    std::string get_name() const override;
    double price() override;

    void add_side_item(Ingredient* side);
    std::vector<Ingredient*>& get_side_item();

private:
    std::vector<Ingredient*> side_item;
};

#endif // MOCHA_H