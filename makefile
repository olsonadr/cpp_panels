CC=g++
LIBRARY=panels
HPP_DIR=./source/headers
CPP_DIR=./source
OUT_DIR=./build

all: shared
shared: lib$(LIBRARY).so $(OUT_DIR)
static: lib$(LIBRARY).a $(OUT_DIR)

lib$(LIBRARY).so: $(OUT_DIR) $(OUT_DIR)/Element.o $(OUT_DIR)/Container.o $(OUT_DIR)/Window.o $(OUT_DIR)/Label.o $(OUT_DIR)/Border.o $(OUT_DIR)/List.o $(OUT_DIR)/Console.o $(OUT_DIR)/Alert.o
	$(CC) -std=c++11 -g -fPIC -shared -I$(HPP_DIR) $(OUT_DIR)/Element.o $(OUT_DIR)/Container.o $(OUT_DIR)/Window.o $(OUT_DIR)/Label.o $(OUT_DIR)/Border.o $(OUT_DIR)/List.o $(OUT_DIR)/Console.o $(OUT_DIR)/Alert.o -o lib$(LIBRARY).so

lib$(LIBRARY).a: $(OUT_DIR) $(OUT_DIR)/Element.o $(OUT_DIR)/Container.o $(OUT_DIR)/Window.o $(OUT_DIR)/Label.o $(OUT_DIR)/Border.o $(OUT_DIR)/List.o $(OUT_DIR)/Console.o $(OUT_DIR)/Alert.o
	ar rvs lib$(LIBRARY).a $(OUT_DIR)/Element.o $(OUT_DIR)/Container.o $(OUT_DIR)/Window.o $(OUT_DIR)/Label.o $(OUT_DIR)/Border.o $(OUT_DIR)/List.o $(OUT_DIR)/Console.o $(OUT_DIR)/Alert.o

$(OUT_DIR)/Element.o: $(OUT_DIR) $(CPP_DIR)/Element.cpp
	$(CC) -std=c++11 -g -fPIC -c -I$(HPP_DIR) $(CPP_DIR)/Element.cpp -o $(OUT_DIR)/Element.o

$(OUT_DIR)/Container.o: $(OUT_DIR) $(CPP_DIR)/Container.cpp
	$(CC) -std=c++11 -g -fPIC -c -I$(HPP_DIR) $(CPP_DIR)/Container.cpp -o $(OUT_DIR)/Container.o

$(OUT_DIR)/Window.o: $(OUT_DIR) $(CPP_DIR)/Window.cpp
	$(CC) -std=c++11 -g -fPIC -c -I$(HPP_DIR) $(CPP_DIR)/Window.cpp -o $(OUT_DIR)/Window.o

$(OUT_DIR)/Label.o: $(OUT_DIR) $(CPP_DIR)/Label.cpp
	$(CC) -std=c++11 -g -fPIC -c -I$(HPP_DIR) $(CPP_DIR)/Label.cpp -o $(OUT_DIR)/Label.o

$(OUT_DIR)/Border.o: $(OUT_DIR) $(CPP_DIR)/Border.cpp
	$(CC) -std=c++11 -g -fPIC -c -I$(HPP_DIR) $(CPP_DIR)/Border.cpp -o $(OUT_DIR)/Border.o

$(OUT_DIR)/List.o: $(OUT_DIR) $(CPP_DIR)/List.cpp
	$(CC) -std=c++11 -g -fPIC -c -I$(HPP_DIR) $(CPP_DIR)/List.cpp -o $(OUT_DIR)/List.o

$(OUT_DIR)/Console.o: $(OUT_DIR) $(CPP_DIR)/Console.cpp
	$(CC) -std=c++11 -g -fPIC -c -I$(HPP_DIR) $(CPP_DIR)/Console.cpp -o $(OUT_DIR)/Console.o

$(OUT_DIR)/Alert.o: $(OUT_DIR) $(CPP_DIR)/Alert.cpp
	$(CC) -std=c++11 -g -fPIC -c -I$(HPP_DIR) $(CPP_DIR)/Alert.cpp -o $(OUT_DIR)/Alert.o

$(OUT_DIR):
	mkdir $(OUT_DIR)

clean:
	rm -r -f $(OUT_DIR) lib$(LIBRARY).so lib$(LIBRARY).a
