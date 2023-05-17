/* Mastery Check-in Quiz Framework built by Sathya Edamadaka for 106L Interview*/
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

/*********************************************
 * Exercise 1:
 * Write a lambda expression to count how many numbers
 * are greater than the LIMIT constant in the following vector.
 * Everything with the STL has been done for you—
 * you just have to write the lambda.
 ********************************************/
int countIfExercise1() {
    int LIMIT = 5;

    // START OF STUDENT CODE
    auto lambda = [LIMIT] (int n) { return n > LIMIT; };
    // END OF STUDENT CODE

    std::vector<int> nums = {3, 5, 10, 6, 8, 9};
    return std::count_if(nums.begin(), nums.end(), lambda);
}

/*********************************************
 * Exercise 2:
 * Write a lambda expression to count how many odd numbers
 * are in nums. In addition, have the lambda add all of the odd
 * numbers into the oddNumbers parameter vector.
 * In addition, if the number is odd
 ********************************************/
int countIfExercise2(std::vector<int>& oddNumbers) {
    // START OF STUDENT CODE
    auto lambda = [&oddNumbers] (int n) {
        if (n % 2) {
            oddNumbers.push_back(n);
        }
        return n % 2;
    };
    // END OF STUDENT CODE

    std::vector<int> nums = {3, 5, 10, 6, 8, 9};
    return std::count_if(nums.begin(), nums.end(), lambda);
}

/*********************************************
 * Exercise 3:
 * Write a lambda to find the first number that is odd and not
 * divisible by 3.
 ********************************************/
int findExercise1() {
    // START OF STUDENT CODE
    auto lambda = [] (int n) { return n % 2 == 1 && n % 3 != 0; };
    // END OF STUDENT CODE

    std::vector<int> nums = {3, 9, 18, 12, 5, 7};
    std::vector<int>::iterator it = std::find_if(nums.begin(), nums.end(), lambda);
    return *it;
}

/*********************************************
 * Exercise 4:
 * Write a lambda expression to sort a vector of integers
 * in reverse order. Your lambda will take in two numbers, 
 * as the sort function works by comparing numbers. Learning
 * how std::sort is very useful in the real world, so we'd 
 * recommend looking up how to write this lambda expression if
 * you're stuck!
 ********************************************/
std::vector<int> sortExercise1() {
    // START OF STUDENT CODE
    auto lambda = [](int i, int j){ return i > j; };
    // END OF STUDENT CODE

    std::vector<int> nums = {3, 5, 10, 6, 8, 9};
    std::sort(nums.begin(), nums.end(), lambda);
    return nums;
}

/*********************************************
 * main — provided code, not necessary to edit!
 * This is provided code that's used for running the autograders. It's a 
 * CLI (command line interface) for this file. 
 ********************************************/
int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "Please specify an exercise name." << std::endl;
        return 1;
    }
    int exerciseNum = std::stoi(argv[1]);
    if (exerciseNum == 1) {
        std::cout << countIfExercise1() << std::endl;
    }
    if (exerciseNum == 2) {
        std::vector<int> oddNumbers;
        std::cout << countIfExercise2(oddNumbers) << std::endl;
    }
    if (exerciseNum == 3) {
        std::cout << findExercise1() << std::endl;
    }
    if (exerciseNum == 4) {
        std::vector<int> vec = sortExercise1();
        std::string str(vec.begin(), vec.end());
        std::cout << str << std::endl;
    }
    return 0;
}
