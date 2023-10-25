CXX = g++
CXXFLAGS = -std=c++17  -c
LXXFLAGS = -std=c++17
OBJECTS = src/main.o src/publication.o src/book.o src/author.o src/assignment5.o src/unittest.o
TARGET = main


$(TARGET): $(OBJECTS)
	$(CXX) $(LXXFLAGS) $(OBJECTS) -o $(TARGET) -lgtest -lgtest_main -pthread

# VPATH=./include

# main.o: src/main.cpp src/unittest.cpp 
# 	$(CXX) $(CXXFLAGS) src/main.cpp

# unittest.o: src/unittest.cpp 
# 	$(CXX) $(CXXFLAGS) src/unittest.cpp	

# assignment5.o: src/assignment5.cpp 
# 	$(CXX) $(CXXFLAGS) src/assignment5.cpp

# book.o: src/book.cpp 
# 	$(CXX) $(CXXFLAGS) src/book.cpp

# publication.o: src/publication.cpp 
# 	$(CXX) $(CXXFLAGS) src/publication.cpp

# author.o: src/author.cpp 
# 	$(CXX) $(CXXFLAGS) src/author.cpp

.PHONY : clean
clean:
	rm -f $(TARGET) $(OBJECTS)