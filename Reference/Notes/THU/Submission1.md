#### Submission1

##### Lecture 1/ Make and makefile/16

If we write the makefile like in the problem, it will not generate a executable program called test. Assuming that main.cpp, sum.cpp and product.cpp all include the header file functions.h, I write a makefile fitting the requirements in my own style.



```
.PHONY: clean
test: main.o sum.o product.o
	g++ $^ -o $@
%.o: %.cpp *.h
	g++ -c $<
clean:
	rm -f *.o test
```

​    

##### Lecture 1/ Make and makefile/19

We could use \$^, \$@, \$< to simplify our codes

\$^ refers to all the files behind

\$@ refers to the target 

\$< refers to the first file behind

For example, if we have one command like

```
target: file1 file2 file3
	g++ $^ -o $@ // namely g++ file1 file2 file2 -o target
	g++ $< -o $@ // namely g++ file1 -o target
```

