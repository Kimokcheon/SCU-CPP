// system
#include <iostream>
#include <algorithm>
#include "simple_fraction.h"

using std::cout;    using std::endl;
using std::to_string;

// constructor to initialize Fraction
Fraction::Fraction (int num, int denom) {
    this->num = num;
    this->denom = denom;
    reduce();
}

void Fraction::reduce() {
    int gcd = std::__gcd(num, denom);
    num /= gcd;
    denom /= gcd;
}

// return if fraction represented by this is less than rhs
bool Fraction::operator< (const Fraction& rhs) const {
    return rhs.denom * num < rhs.num * denom;
}

// return if fraction represented by this is greater than rhs
bool Fraction::operator> (const Fraction& rhs) const {
    return rhs.denom * num > rhs.num * denom;
}

// get difference of this and rhs fractions
Fraction Fraction::operator- (const Fraction& rhs) const {
    int newNum = num * rhs.denom - denom * rhs.num;    
    int newDenom = rhs.denom * denom;
    return Fraction(newNum, newDenom);
}

int main() {

    // creating a few fractions:
    Fraction half(1, 2);
    Fraction third(1, 3);
    Fraction weird(1.5, 3.141);

    // testing out operations:
    bool lessThan = half < third;
    bool greaterThan = half > third;
    cout << "half is less than third: " << lessThan << endl;
    cout << "half is greater than third: " << greaterThan << endl;

    Fraction difference = half - weird;
    // how do we print this out?

    return 0;
}

