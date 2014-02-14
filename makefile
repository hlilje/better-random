CXX = g++
CPPFLAGS = -Wall -Wextra -pedantic -std=c++11
DEPS = rand.h rand.cpp
TARGET = main

all: $(TARGET)

$(TARGET): $(TARGET).cpp
	$(CXX) $(CPPFLAGS) -o $(TARGET) $(TARGET).cpp $(DEPS)

clean:
	rm -f *.o $(TARGET)
