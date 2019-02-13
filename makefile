CC=g++
EXE_FILE=window_test
INTERFACE=window_test
HPP_DIR=./headers
CPP_DIR=./source
OUT_DIR=./compiled

all: $(EXE_FILE) $(OUT_DIR)

$(EXE_FILE): $(OUT_DIR) $(INTERFACE).cpp $(OUT_DIR)/Element.o $(OUT_DIR)/Container.o $(OUT_DIR)/Window.o $(OUT_DIR)/Label.o $(OUT_DIR)/Border.o
	$(CC) -std=c++11 -g -I$(HPP_DIR) $(OUT_DIR)/Element.o $(OUT_DIR)/Container.o $(OUT_DIR)/Window.o $(OUT_DIR)/Label.o $(OUT_DIR)/Border.o $(INTERFACE).cpp -o $(EXE_FILE)

$(OUT_DIR)/Element.o: $(HPP_DIR)/Element.hpp $(CPP_DIR)/Element.cpp
	$(CC) -std=c++11 -g -c -I$(HPP_DIR) $(CPP_DIR)/Element.cpp -o $(OUT_DIR)/Element.o
	
$(OUT_DIR)/Container.o: $(OUT_DIR) $(HPP_DIR)/Container.hpp $(HPP_DIR)/Label.hpp $(CPP_DIR)/Container.cpp
	$(CC) -std=c++11 -g -c -I$(HPP_DIR) $(CPP_DIR)/Container.cpp -o $(OUT_DIR)/Container.o

$(OUT_DIR)/Window.o: $(OUT_DIR) $(HPP_DIR)/Window.hpp $(HPP_DIR)/Container.hpp $(CPP_DIR)/Window.cpp
	$(CC) -std=c++11 -g -c -I$(HPP_DIR) $(CPP_DIR)/Window.cpp -o $(OUT_DIR)/Window.o

$(OUT_DIR)/Label.o: $(OUT_DIR) $(HPP_DIR)/Label.hpp $(HPP_DIR)/Element.hpp $(CPP_DIR)/Label.cpp
	$(CC) -std=c++11 -g -c -I$(HPP_DIR) $(CPP_DIR)/Label.cpp -o $(OUT_DIR)/Label.o

$(OUT_DIR)/Border.o: $(OUT_DIR) $(HPP_DIR)/Border.hpp $(HPP_DIR)/Border.hpp $(CPP_DIR)/Border.cpp
	$(CC) -std=c++11 -g -c -I$(HPP_DIR) $(CPP_DIR)/Border.cpp -o $(OUT_DIR)/Border.o

$(OUT_DIR):
	mkdir $(OUT_DIR)

clean:
	rm -f $(OUT_DIR)/* $(EXE_FILE)