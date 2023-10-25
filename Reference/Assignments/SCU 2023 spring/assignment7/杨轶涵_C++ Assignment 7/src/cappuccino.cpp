#include "cappuccino.h"
#include "sub_ingredients.h"
#include "espresso_based.h"
#include "ingredient.h"

Cappuccino::Cappuccino( ) {
    Ingredient* ptr = new Espresso( 2 );
    ingredients.push_back( new Espresso( 2 ) );
    ingredients.push_back( new Milk( 2 ) );
    ingredients.push_back( new MilkFoam( 1 ) );
    name = "Cappuccino";
}

Cappuccino::Cappuccino(const Cappuccino& cap) : EspressoBased( cap ) {
    for( auto it : cap.side_items ) {
        side_items.push_back( new Ingredient( *it ) );
    }
}

Cappuccino::~Cappuccino( ) {
    for( auto it : side_items ) {
        delete it;
    }
    side_items.clear();
}

void Cappuccino::operator = (const Cappuccino& cap) {
    if( this == &cap ) return;
    EspressoBased::operator = ( cap );
    for( auto it : side_items ) {
        delete it;
    }
    side_items.clear();
    for( auto it : cap.side_items ) {
        side_items.push_back( new Ingredient( *it ) );
    }
}

std::string Cappuccino::get_name() {
    return name;
}

double Cappuccino::price() {
    double total_price = 0;
    for( auto& t : ingredients )
        total_price += t->get_units() * t->get_price_unit();
    for( auto& t : side_items )
        total_price += t->get_units() * t->get_price_unit();
    return total_price;
}

void Cappuccino::add_side_item( Ingredient* side ) {
    side_items.push_back( side );
}
std::vector<Ingredient*>& Cappuccino::get_side_items() {
    return side_items;
}
