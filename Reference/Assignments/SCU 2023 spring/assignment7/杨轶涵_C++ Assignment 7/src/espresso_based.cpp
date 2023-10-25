#include "espresso_based.h"

EspressoBased::EspressoBased( ) = default;

EspressoBased::EspressoBased( const EspressoBased& esp ) {
    for( auto it : esp.ingredients ) {
        ingredients.push_back( new Ingredient( *it ) );
    }
    name = esp.name;
}

void EspressoBased::operator = ( const EspressoBased& esp ) {
    // puts("HERE");
    if( this == &esp ) return;
    for( auto it : ingredients ) {
        delete it;
    }
    ingredients.clear();
    for( auto it : esp.ingredients ) {
        ingredients.push_back( new Ingredient( *it ) );
    }
    name = esp.name;
}

EspressoBased::~EspressoBased( ) {
    for( auto t : ingredients ) {
        delete t;
    }
    ingredients.clear();
    name.clear();
}

std::vector<Ingredient*>& EspressoBased::get_ingredients( ) {
    return ingredients;
}



