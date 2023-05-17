#!/bin/bash

# build (solution)
g++ -Werror -std=c++17 simple_fraction_soln.cpp -o simple_frac_soln
g++ -Wall -Werror -std=c++17 fraction_soln.cpp -o frac_soln

# student files
g++ -Werror -std=c++17 simple_fraction.cpp -o simple_frac
g++ -Wall -Werror -std=c++17 fraction.cpp -o frac
