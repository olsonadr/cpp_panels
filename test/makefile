CC=g++
CPP_DIR=src
HPP_DIR=src
LIB_NAME=panels
LIB_HPP_DIR=../include
LIB_MAKE_DIR=..
LIB_OUT_SRC=../bin
LIB_OUT_DEST=lib
BUILD_DIR=build
OUT_DIR=bin
LIB_OUT_REL=../$(LIB_OUT_DEST)

# Special Targets
all: console alert find label list
.PHONY: $(LIB_OUT_DEST)/lib$(LIB_OUT_DEST).a $(LIB_OUT_DEST)/lib$(LIB_NAME).so clean


# Intended Targets
console: $(OUT_DIR)/console_test
alert: $(OUT_DIR)/alert_test
find: $(OUT_DIR)/find_test
label:$(OUT_DIR)/label_test
border: $(OUT_DIR)/label_test
speed: $(OUT_DIR)/label_test
list: $(OUT_DIR)/list_test


# Executable Targets
$(OUT_DIR)/console_test: $(OUT_DIR) $(BUILD_DIR)/console_test.o $(LIB_OUT_DEST)/lib$(LIB_NAME).so
	$(CC) -std=c++11 -g -I$(LIB_HPP_DIR) -I$(HPP_DIR) $(BUILD_DIR)/console_test.o -o $(OUT_DIR)/console_test -L$(LIB_OUT_DEST) -Wl,-z,origin,-rpath=\$$ORIGIN/$(LIB_OUT_REL) -l$(LIB_NAME)

$(OUT_DIR)/alert_test: $(OUT_DIR) $(BUILD_DIR)/alert_test.o $(LIB_OUT_DEST)/lib$(LIB_NAME).so
	$(CC) -std=c++11 -g -I$(LIB_HPP_DIR) -I$(HPP_DIR) $(BUILD_DIR)/alert_test.o -o $(OUT_DIR)/alert_test -L$(LIB_OUT_DEST) -Wl,-z,origin,-rpath=\$$ORIGIN/$(LIB_OUT_REL) -l$(LIB_NAME)

$(OUT_DIR)/find_test: $(OUT_DIR) $(BUILD_DIR)/find_test.o $(LIB_OUT_DEST)/lib$(LIB_NAME).so
	$(CC) -std=c++11 -g -I$(LIB_HPP_DIR) -I$(HPP_DIR) $(BUILD_DIR)/find_test.o -o $(OUT_DIR)/find_test -L$(LIB_OUT_DEST) -Wl,-z,origin,-rpath=\$$ORIGIN/$(LIB_OUT_REL) -l$(LIB_NAME)

$(OUT_DIR)/label_test: $(OUT_DIR) $(BUILD_DIR)/label_test.o $(LIB_OUT_DEST)/lib$(LIB_NAME).so
	$(CC) -std=c++11 -g -I$(LIB_HPP_DIR) -I$(HPP_DIR) $(BUILD_DIR)/label_test.o -o $(OUT_DIR)/label_test -L$(LIB_OUT_DEST) -Wl,-z,origin,-rpath=\$$ORIGIN/$(LIB_OUT_REL) -l$(LIB_NAME)

$(OUT_DIR)/list_test: $(OUT_DIR) $(BUILD_DIR)/list_test.o $(LIB_OUT_DEST)/lib$(LIB_NAME).so
	$(CC) -std=c++11 -g -I$(LIB_HPP_DIR) -I$(HPP_DIR) $(BUILD_DIR)/list_test.o -o $(OUT_DIR)/list_test -L$(LIB_OUT_DEST) -Wl,-z,origin,-rpath=\$$ORIGIN/$(LIB_OUT_REL) -l$(LIB_NAME)


# Compilation Targets
$(BUILD_DIR)/alert_test.o: $(BUILD_DIR) $(CPP_DIR)/alert_test.cpp
	$(CC) -std=c++11 -g -I$(LIB_HPP_DIR) -I$(HPP_DIR) $(CPP_DIR)/alert_test.cpp -c -o $(BUILD_DIR)/alert_test.o

$(BUILD_DIR)/console_test.o: $(BUILD_DIR) $(CPP_DIR)/console_test.cpp
	$(CC) -std=c++11 -g -I$(LIB_HPP_DIR) -I$(HPP_DIR) $(CPP_DIR)/console_test.cpp -c -o $(BUILD_DIR)/console_test.o

$(BUILD_DIR)/find_test.o: $(BUILD_DIR) $(CPP_DIR)/find_test.cpp
	$(CC) -std=c++11 -g -I$(LIB_HPP_DIR) -I$(HPP_DIR) $(CPP_DIR)/find_test.cpp -c -o $(BUILD_DIR)/find_test.o

$(BUILD_DIR)/label_test.o: $(BUILD_DIR) $(CPP_DIR)/label_test.cpp
	$(CC) -std=c++11 -g -I$(LIB_HPP_DIR) -I$(HPP_DIR) $(CPP_DIR)/label_test.cpp -c -o $(BUILD_DIR)/label_test.o

$(BUILD_DIR)/list_test.o: $(BUILD_DIR) $(CPP_DIR)/list_test.cpp
	$(CC) -std=c++11 -g -I$(LIB_HPP_DIR) -I$(HPP_DIR) $(CPP_DIR)/list_test.cpp -c -o $(BUILD_DIR)/list_test.o


# Library File Targets
$(LIB_OUT_DEST)/lib$(LIB_NAME).a: $(LIB_OUT_DEST)
	make -C$(LIB_MAKE_DIR) static
	cp $(LIB_OUT_SRC)/lib$(LIB_NAME).a $(LIB_OUT_DEST)
	make -C$(LIB_MAKE_DIR) clean_lib

$(LIB_OUT_DEST)/lib$(LIB_NAME).so: $(LIB_OUT_DEST)
	make -C$(LIB_MAKE_DIR) shared
	cp $(LIB_OUT_SRC)/lib$(LIB_NAME).so $(LIB_OUT_DEST)
	make -C$(LIB_MAKE_DIR) clean_lib


# Directory Targets
$(BUILD_DIR):
	mkdir $(BUILD_DIR)

$(OUT_DIR):
	mkdir $(OUT_DIR)

$(LIB_OUT_DEST):
	mkdir $(LIB_OUT_DEST)



# Clean Target
clean:
	rm -r -f $(OUT_DIR) $(BUILD_DIR) $(LIB_OUT_DEST)
