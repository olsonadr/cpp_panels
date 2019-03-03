CC=g++
LIBRARY=panels
HPP_DIR=include
CPP_DIR=src
BUILD_DIR=build
OUT_DIR=bin

all: shared
.PHONY: shared static clean

shared: lib$(LIBRARY).so
static: lib$(LIBRARY).a

lib$(LIBRARY).so: $(OUT_DIR) $(BUILD_DIR) $(BUILD_DIR)/Element.o $(BUILD_DIR)/Container.o $(BUILD_DIR)/Window.o $(BUILD_DIR)/Label.o $(BUILD_DIR)/Border.o $(BUILD_DIR)/List.o $(BUILD_DIR)/Console.o $(BUILD_DIR)/Alert.o $(HPP_DIR)/Panel.hpp
	$(CC) -std=c++11 -g -fPIC -shared -I$(HPP_DIR) $(BUILD_DIR)/Element.o $(BUILD_DIR)/Container.o $(BUILD_DIR)/Window.o $(BUILD_DIR)/Label.o $(BUILD_DIR)/Border.o $(BUILD_DIR)/List.o $(BUILD_DIR)/Console.o $(BUILD_DIR)/Alert.o -o $(OUT_DIR)/lib$(LIBRARY).so

lib$(LIBRARY).a: $(OUT_DIR) $(BUILD_DIR) $(BUILD_DIR)/Element.o $(BUILD_DIR)/Container.o $(BUILD_DIR)/Window.o $(BUILD_DIR)/Label.o $(BUILD_DIR)/Border.o $(BUILD_DIR)/List.o $(BUILD_DIR)/Console.o $(BUILD_DIR)/Alert.o $(HPP_DIR)/Panel.hpp
	ar rvs $(OUT_DIR)/lib$(LIBRARY).a $(BUILD_DIR)/Element.o $(BUILD_DIR)/Container.o $(BUILD_DIR)/Window.o $(BUILD_DIR)/Label.o $(BUILD_DIR)/Border.o $(BUILD_DIR)/List.o $(BUILD_DIR)/Console.o $(BUILD_DIR)/Alert.o

$(BUILD_DIR)/Element.o: $(BUILD_DIR) $(CPP_DIR)/Element.cpp $(HPP_DIR)/Element.hpp
	$(CC) -std=c++11 -g -fPIC -c -I$(HPP_DIR) $(CPP_DIR)/Element.cpp -o $(BUILD_DIR)/Element.o

$(BUILD_DIR)/Container.o: $(BUILD_DIR) $(CPP_DIR)/Container.cpp $(HPP_DIR)/Container.hpp
	$(CC) -std=c++11 -g -fPIC -c -I$(HPP_DIR) $(CPP_DIR)/Container.cpp -o $(BUILD_DIR)/Container.o

$(BUILD_DIR)/Window.o: $(BUILD_DIR) $(CPP_DIR)/Window.cpp $(HPP_DIR)/Window.hpp
	$(CC) -std=c++11 -g -fPIC -c -I$(HPP_DIR) $(CPP_DIR)/Window.cpp -o $(BUILD_DIR)/Window.o

$(BUILD_DIR)/Label.o: $(BUILD_DIR) $(CPP_DIR)/Label.cpp $(HPP_DIR)/Label.hpp
	$(CC) -std=c++11 -g -fPIC -c -I$(HPP_DIR) $(CPP_DIR)/Label.cpp -o $(BUILD_DIR)/Label.o

$(BUILD_DIR)/Border.o: $(BUILD_DIR) $(CPP_DIR)/Border.cpp $(HPP_DIR)/Border.hpp
	$(CC) -std=c++11 -g -fPIC -c -I$(HPP_DIR) $(CPP_DIR)/Border.cpp -o $(BUILD_DIR)/Border.o

$(BUILD_DIR)/List.o: $(BUILD_DIR) $(CPP_DIR)/List.cpp $(HPP_DIR)/List.hpp
	$(CC) -std=c++11 -g -fPIC -c -I$(HPP_DIR) $(CPP_DIR)/List.cpp -o $(BUILD_DIR)/List.o

$(BUILD_DIR)/Console.o: $(BUILD_DIR) $(CPP_DIR)/Console.cpp $(HPP_DIR)/Console.hpp
	$(CC) -std=c++11 -g -fPIC -c -I$(HPP_DIR) $(CPP_DIR)/Console.cpp -o $(BUILD_DIR)/Console.o

$(BUILD_DIR)/Alert.o: $(BUILD_DIR) $(CPP_DIR)/Alert.cpp $(HPP_DIR)/Alert.hpp
	$(CC) -std=c++11 -g -fPIC -c -I$(HPP_DIR) $(CPP_DIR)/Alert.cpp -o $(BUILD_DIR)/Alert.o

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

$(OUT_DIR):
	mkdir $(OUT_DIR)

clean:
	rm -r -f $(OUT_DIR) $(BUILD_DIR)

