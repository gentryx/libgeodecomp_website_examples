CXX = g++
CXXFLAGS += $(shell pkg-config --cflags libgeodecomp)
LIBS += $(shell pkg-config --libs libgeodecomp)

all: main

main: main.cpp
	$(CXX) $< $(CXXFLAGS) $(LDFLAGS) -o $@ $(LIBS)
