CC=g++
EXE_FILE=window_test
INTERFACE=window_test
LIBRARY=panels
HPP_DIR=../source/headers
OUT_DIR=build
LIB_DIR=lib

static: $(LIB_DIR) $(INTERFACE).cpp $(LIB_DIR)/lib$(LIBRARY).a
	$(CC) -std=c++11 -g -I$(HPP_DIR) $(INTERFACE).cpp -o $(EXE_FILE) $(LIB_DIR)/lib$(LIBRARY).a

shared: $(LIB_DIR) $(INTERFACE).cpp $(LIB_DIR)/lib$(LIBRARY).so
	$(CC) -std=c++11 -g -I$(HPP_DIR) $(INTERFACE).cpp -o $(EXE_FILE) -L$(LIB_DIR) -Wl,-z,origin,-rpath=\$$ORIGIN/$(LIB_DIR) -lpanels

$(LIB_DIR)/lib$(LIBRARY).a: $(LIB_DIR)
	make -C.. static
	cp ../lib$(LIBRARY).a $(LIB_DIR)/
	make -C.. clean

$(LIB_DIR)/lib$(LIBRARY).so: $(LIB_DIR)
	make -C.. shared
	cp ../lib$(LIBRARY).so $(LIB_DIR)/
	make -C.. clean

$(OUT_DIR):
	mkdir $(OUT_DIR)

$(LIB_DIR):
	mkdir $(LIB_DIR)

clean:
	rm -r -f $(OUT_DIR) $(LIB_DIR) $(EXE_FILE)
