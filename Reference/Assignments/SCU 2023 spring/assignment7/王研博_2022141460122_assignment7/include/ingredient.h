#ifndef INGREDIENT_H
#define INGREDIENT_H
#include <iostream>
class Ingredient
{
 public:
	Ingredient() = default;
	~Ingredient() = default;
	[[nodiscard]] double get_price_unit() const {return price_unit;}
	[[nodiscard]] size_t get_units() const {return units;}
	virtual std::string get_name() = 0;
	[[nodiscard]] double price() const {return price_unit*(double)units;}


 protected:
	Ingredient(double price_unit, size_t units) : price_unit(price_unit), units(units) {}

	double price_unit;
	size_t units;
	std::string name;
};

#endif // INGREDIENT_H