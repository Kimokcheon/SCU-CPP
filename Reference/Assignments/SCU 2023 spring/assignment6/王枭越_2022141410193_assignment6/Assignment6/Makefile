CXX = g++
CXXFLAGS = -std=c++2a -Wall -I h -I /usr/local/include/gtest/ -c
LXXFLAGS = -std=c++2a -Ih -pthread
OBJECTS = ./obj/linkedlist.o ./obj/main.o ./obj/unittest.o
GTEST = /usr/local/lib/libgtest.a
TARGET = main


$(TARGET): $(OBJECTS)
	$(CXX) $(LXXFLAGS) -g -o $(TARGET) $(OBJECTS) $(GTEST)
./obj/linkedlist.o: ./cpp/linkedlist.cpp
	$(CXX) $(CXXFLAGS) ./cpp/linkedlist.cpp -o ./obj/linkedlist.o
./obj/unittest.o: ./cpp/unittest.cpp
	$(CXX) $(CXXFLAGS) ./cpp/unittest.cpp -o ./obj/unittest.o
./obj/main.o: ./cpp/main.cpp
	$(CXX) $(CXXFLAGS) ./cpp/main.cpp -o ./obj/main.o
clean:
	rm -fv $(TARGET) $(OBJECTS)
