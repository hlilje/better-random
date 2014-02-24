CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic -std=c++11
TESTLIBS = -lmylib -lprobdist -ltestu01
SRCS = $(wildcard *.cpp)
TARGET = main

all: $(TARGET)

$(TARGET): $(TARGET).cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS) $(TESTLIBS)

clean:
	rm -f *.o $(TARGET)
