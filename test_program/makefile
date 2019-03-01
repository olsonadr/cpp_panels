CC=g++
EXE_FILE=window_test
INTERFACE=window_test
LIB_NAME=panels
HPP_DIR=../source/headers
LIB_DIR=lib

all: shared
.PHONY: $(LIB_DIR)/lib$(LIB_NAME).a $(LIB_DIR)/lib$(LIB_NAME).so clean

static: $(LIB_DIR) $(INTERFACE).cpp $(LIB_DIR)/lib$(LIB_NAME).a
	$(CC) -std=c++11 -g -I$(HPP_DIR) $(INTERFACE).cpp -o $(EXE_FILE) $(LIB_DIR)/lib$(LIB_NAME).a

shared: $(LIB_DIR) $(INTERFACE).cpp $(LIB_DIR)/lib$(LIB_NAME).so
	$(CC) -std=c++11 -g -I$(HPP_DIR) $(INTERFACE).cpp -o $(EXE_FILE) -L$(LIB_DIR) -Wl,-z,origin,-rpath=\$$ORIGIN/$(LIB_DIR) -l$(LIB_NAME)

$(LIB_DIR)/lib$(LIB_NAME).a: $(LIB_DIR)
	make -C.. static
	cp ../lib$(LIB_NAME).a $(LIB_DIR)/
	make -C.. clean

$(LIB_DIR)/lib$(LIB_NAME).so: $(LIB_DIR)
	make -C.. shared
	cp ../lib$(LIB_NAME).so $(LIB_DIR)/
	make -C.. clean

$(LIB_DIR):
	mkdir $(LIB_DIR)

clean:
	rm -r -f $(LIB_DIR) $(EXE_FILE)
