#include "cappuccino.h"
Cappuccino::~Cappuccino()
{
    for(const auto& i : side_items){
        delete i;
    }
    side_items.clear();
}
void Cappuccino::add_side_item(Ingredient* side){
    side_items.push_back(side);
}
std::vector<Ingredient*>& Cappuccino::get_side_items(){
    return side_items;
}
Cappuccino::Cappuccino(){
    name="Cappuccino";
    ingredients.push_back(new Espresso(2));
    ingredients.push_back(new Milk(2));
    ingredients.push_back(new MilkFoam(1));
}
Cappuccino::Cappuccino(const Cappuccino& cap):EspressoBased{cap}{
    for(auto i : cap.side_items){
        this->side_items.push_back(i->Copy());
    }
}
void Cappuccino::operator=(const Cappuccino& esp){
    if((&esp)==this) return;
    this->name=esp.name;
    this->ingredients.clear();
    for(auto i : esp.ingredients){
        this->ingredients.push_back(i->Copy());
    }
    this->side_items.clear();
    for(auto i : esp.side_items){
        this->side_items.push_back(i->Copy());
    }
}
std::string Cappuccino:: get_name(){
    return name;
}
double Cappuccino:: price(){
    double ans=0;
    for(auto i : ingredients){
        ans+=i->price();
    }
    for(auto i : side_items){
        ans+=i->price();
    }
    return ans;
}