CXX = g++
CPPFLAGS = -Wall -Wextra -pedantic -std=c++11
TESTINC = test/TestU01/include
TESTLIB = test/TestU01/libs
DEPS = rand.hpp rand.cpp $(TESTINC)/unif01.h $(TESTINC)/ugfsr.h
TARGET = main

all: $(TARGET)

$(TARGET): $(TARGET).cpp
	$(CXX) $(CPPFLAGS) -o $(TARGET) $(TARGET).cpp $(DEPS)

clean:
	rm -f *.o $(TARGET)
