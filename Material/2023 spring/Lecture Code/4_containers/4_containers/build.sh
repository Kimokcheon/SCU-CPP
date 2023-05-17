#!/bin/bash

# build
g++ -Wall -Werror -std=c++17 vector_time_trials.cpp -o vector
g++ -Wall -Werror -std=c++17 vector_time_trials_solution.cpp -o vector_solution
g++ -Wall -Werror -std=c++17 vector_list_deque.cpp -o compare
