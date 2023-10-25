#include "espresso_based.h"
std::vector<Ingredient*>& EspressoBased::get_ingredients()
{
	return ingredients;
}
EspressoBased::EspressoBased() = default;
EspressoBased::EspressoBased(const EspressoBased& esp)
{
	this->name = esp.name;
	for(const auto& i : esp.ingredients)
	{
		Ingredient* temp = nullptr;
		if(i->get_name() == "Espresso")
		{
			temp = new Espresso(*dynamic_cast<Espresso*>(i));
		}
		else if(i->get_name() == "Milk")
		{
			temp = new Milk(*dynamic_cast<Milk*>(i));
		}
		else if(i->get_name() == "MilkFoam")
		{
			temp = new MilkFoam(*dynamic_cast<MilkFoam*>(i));
		}
		ingredients.push_back(temp);
	}
}

EspressoBased::~EspressoBased()
{
	ingredients.clear();
//	std::cout<<"~EspressoBased"<<std::endl;
}