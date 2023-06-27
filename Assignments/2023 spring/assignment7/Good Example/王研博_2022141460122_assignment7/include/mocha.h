#ifndef MOCHA_H
#define MOCHA_H
#include "sub_ingredients.h"
#include "espresso_based.h"
#include <iostream>
#include <vector>
class Mocha: public EspressoBased
{
 public:
	Mocha();
	Mocha(const Mocha& mo);
	~Mocha() override;
	void operator=(const Mocha& mo);

	std::string get_name () override;
	double price() override;
	void add_side_item(Ingredient* side);
	std::vector<Ingredient*>& get_side_items();

 private:
	std::vector<Ingredient*> side_items;

};
#endif // MOCHA_H