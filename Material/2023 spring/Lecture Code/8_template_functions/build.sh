#!/bin/bash

# build
g++ -Wall -Werror -std=c++17 template_functions_soln.cpp -o tempf_soln
g++ -Wall -Werror -std=c++17 count_occurrences_soln.cpp -o count_soln

# template files
g++ -Wall -Werror -std=c++17 template_functions.cpp -o tempf
g++ -Wall -Werror -std=c++17 count_occurrences.cpp -o count
