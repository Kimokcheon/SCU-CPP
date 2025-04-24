# Task 2 Streams

## Streams

- What does `setw,setfill` manipulator do? How do you use them?

- What is stream failure? How do you check for it?

- Use a `stringstream` and write a function that converts an `int` into a `string`.

- Try to implement a function `has_hex_letters` that accepts an `int` and return whether or not that integer's hexadecimal representation contains letters (`a` to `z`). You should learn `hex` and `dec` stream manipulators and implement with a `stringstream`.

-  Try to implement a function `draw_triangle` with `setw` and `setfill` that takes an `int` corresponding to the height of the triangle and a `char` representing a character to print, then draws a triangle of the specified height using that character. 

  For example, if you call `draw_triangle( 5 , '#' )` you'll get:

  ```
      #
     ###
    #####
   #######
  #########
  ```

- There is a table in `table.txt`, which has several lines, each line contains a string `name` and an integer `s` separated by a space, with the meaning of the salary of `name` . Some operators about this table is recorded in `operator.txt`. It also has some lines, each line contains a string `name` and an integer `t`, which means changing the salary of `name` to `t`. If changed salary is higher, output  `name has more salary.` in console; if it is becoming less, output `name has less salary.`; otherwise, output `name's salary doesn't change.`. Also, it maybe a invalid operator, including inputting two strings, swapping the input i.e. first input an integer, then input a string. In this situation, output `Error operator on line d!` in console, `d` means the line of invalid operator in `operator.txt`. Finally, output the changed table to `table_new.txt`, with the following format:

  ```
  -----id|---name|-salary
  ------1|--Alice|--99824
  ------2|----Bob|---4353
  ```

  The first line is table head. `-` means space, first column is indexes numbered from `1`,  second column is strings,  third column is integers. You should write a program to complete it. It is guaranteed that the length of string and integer is less than 7,  `name` in `table.txt` is different.

## Memory

- Learn what are `new,new[]` and `delete,delete[]` and compare them with `malloc,free`.
- Try to implement a function `allocate_linear` that accepts an integer $n$ and returns a pointer which points to an integer array of length $n$ . What should you do if you want to free the memory of the allocated array?
- What is memory leak? Can you give an example code of memory leak?