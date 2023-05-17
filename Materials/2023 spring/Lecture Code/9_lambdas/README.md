# Mastery Check-in: Functions and Algorithms
## Overview
Thank you so much again for the opportunity to interview!  

Consistent concept mastery assessments are among the best ways of testing student understanding. I believe that giving students the chance to concisely and consistently practice what they learn is very useful. As a result, I implemented this check-in quiz framework for students and lecturers alike to use, including a completely reusable autograder. These exercises would be optional, but provided every week for students to use. A reward scheme could be implemented with late days. This is just one example of what I'd love to do for students as a co-lecturer! 

## How to complete check-in exercises
First, students clone this repository to the myth machines or to your computer if you have the GNU compiler, `g++`, installed (`git clone https://github.com/snme/106L-mastery`). Then, students will open the exercises.cpp file and fill out the exercise functions. Function and inline comments describe the check-in exercise to the students and tell them where to write their code. Lastly, to check their answers, they would simply run `./autograder`! If they got any of the tests wrong, the autograder prints out the expected output and student output. Here are the files inside this directory:
- `exercises.cpp`: Where students write their code.
- `solution.cpp`: Solution code (displayed for convenience and ease of use (i.e. you can copy and paste it into `exercises.cpp` to test the autograder), but in reality, we'd just provide them with the compiled executible).
- `test_cases`: The test cases run by the autograder on student code.
- `autograder`: A completely reusible python autograder that I implemented from scratch! It compiles the solution and student exercises file, runs each of the tests in `test_cases`, and compares the output. It provides a report of which test cases were incorrect, the expected and student output, and how many test cases were successfully passed.

*Mastery Check-in Quiz Framework built by Sathya Edamadaka for 106L Interview*
