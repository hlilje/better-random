CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic -std=c++11
TESTINC = test/TestU01/include
TESTLIBS = -lmylib -lprobdist -ltestu01
DEPS = BetterRandom.hpp BetterRandom.cpp CppRandom.hpp CppRandom.cpp $(TESTINC)/unif01.h $(TESTINC)/ugfsr.h $(TESTINC)/bbattery.h
TARGET = main

all: $(TARGET)

$(TARGET): $(TARGET).cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(TARGET).cpp $(DEPS) $(TESTLIBS)

clean:
	rm -f *.o $(TARGET)
