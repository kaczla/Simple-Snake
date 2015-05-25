DIR := ./src
SOURCE := $(DIR)/main.cpp
CXXFLAGS := -std=c++11 -O2
LDLIBS := -pthread
APP_NAME := server.out

all:
	$(CXX) $(SOURCE) -o $(APP_NAME) $(CXXFLAGS) $(LDLIBS)

clean:
	rm *.o $(APP_NAME)
