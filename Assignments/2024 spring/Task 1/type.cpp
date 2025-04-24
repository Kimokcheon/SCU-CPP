#include <iostream>

void output_type( const int ) {
    std::cout << "Int type." << std::endl;
}

void output_type( const long long ) {
    std::cout << "Long long type." << std::endl;
}

void output_type( double ) {
    std::cout << "Double type." << std::endl;
}

void output_type( const void* ) {
    std::cout << "Pointer type." << std::endl;
}

void output_type( const unsigned ) {
    std::cout << "Unsigned type." << std::endl;
}

void output_type( const bool ) {
    std::cout << "Bool type." << std::endl;
}

int main() {
    int A[42];

    // Basic Types
    output_type( 31 );
    output_type( 31.4 );
    output_type( 31u );
    output_type( 31ll );
    output_type( "31415" );
    output_type( A );

    // With binary operators?
    output_type( 31 + 41 );
    output_type( 31 + 4.1 );
    output_type( 31 / 4 );
    output_type( 31 + 4ll );
    output_type( 31 - 4.1 );
    output_type( 31u - 41 );
    output_type( 31 > 4.1 );
    output_type( A + 3 );

    std::cout << 31 / 4 << std::endl;
    std::cout << 31u - 41 << std::endl;
    std::cout << ( -3 > 4u ) << std::endl;
}
