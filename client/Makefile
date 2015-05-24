DIR := ./src
SOURCE := $(DIR)/main.cpp 
CXXFLAGS := -std=c++11 -Ofast
LDLIBS := -pthread
APP_NAME := client.out

all:
	$(CXX) $(SOURCE) -o $(APP_NAME) $(CXXFLAGS) $(LDLIBS)

clean:
	rm *.o $(APP_NAME)

