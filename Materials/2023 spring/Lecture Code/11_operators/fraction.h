#ifndef FRACTION_H
#define FRACTION_H

#include <iostream>

// Class to represent fractions with distinct numerators and denominators.
class Fraction {

    public:
        /*
         * constructor to initialize Fraction
         */
        Fraction (int num, int denom);

        /*
         * return if fraction represented by this is less than rhs
         */
        bool operator < (const Fraction& rhs) const;

        /*
         * return if fraction represented by this is greater than rhs
         */
        bool operator > (const Fraction& rhs) const;

        /*
         * get difference of this and rhs fractions
         */
        Fraction operator - (const Fraction& rhs) const;

        /*
         * Non-member functions:
         */
        friend Fraction& operator += (Fraction& lhs, const Fraction& rhs);
        friend bool operator < (const double& lhs, const Fraction& rhs);
        friend std::ostream& operator << (std::ostream& out, const Fraction& target);

    private:
        int num, denom;
        void reduce();
};

#endif
