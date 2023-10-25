CXX = g++
CXX_FLAGS = -std=c++17 -WALL -c
LXX_FLAGS = -std=c++17

objects = src/assignment5.o src/author.o src/book.o src/main.o \
			src/publication.o src/unittest.o

bookshelf : $(objects)
	$(CXX) $(LXX_FLAGS) $(objects) -o bookshelf -lgtest -lgtest_main -pthread

clean :
	-rm $(objects) bookshelf