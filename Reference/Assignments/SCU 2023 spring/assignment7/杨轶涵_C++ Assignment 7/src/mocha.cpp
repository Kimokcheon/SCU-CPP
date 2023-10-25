#include "mocha.h"
#include "sub_ingredients.h"
#include "espresso_based.h"
#include "ingredient.h"

Mocha::Mocha( ) {
    ingredients.push_back( new Espresso( 2 ) );
    ingredients.push_back( new Milk( 2 ) );
    ingredients.push_back( new MilkFoam( 1 ) );
    ingredients.push_back( new Chocolate( 1 ) );
    name = "Mocha";
}

Mocha::Mocha(const Mocha& cap) : EspressoBased( cap ) {
    for( auto it : cap.side_items ) {
        side_items.push_back( new Ingredient( *it ) );
    }
}

Mocha::~Mocha( ) {
    for( auto it : side_items ) {
        delete it;
    }
    side_items.clear();
}

void Mocha::operator = (const Mocha& cap) {
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

std::string Mocha::get_name() {
    return name;
}

double Mocha::price() {
    double total_price = 0;
    for( auto& t : ingredients )
        total_price += t->get_units() * t->get_price_unit();
    for( auto& t : side_items )
        total_price += t->get_units() * t->get_price_unit();
    return total_price;
}

void Mocha::add_side_item( Ingredient* side ) {
    side_items.push_back( side );
}
std::vector<Ingredient*>& Mocha::get_side_items() {
    return side_items;
}
