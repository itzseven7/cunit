# Directories

SRC_DIR=CUnit
TESTS_DIR=CUnitTest
EXAMPLE_DIR=CUnitExample
INC_DIRS=-I${SRC_DIR}/include -I${SRC_DIR}/include/internal -I${TESTS_DIR}/include -I${EXAMPLE_DIR}/include
OBJ_DIR=obj
BIN_DIR=bin

# Compiler

CC=gcc
CFLAGS=-O3 $(INC_DIRS)
LDFLAGS=-lcunit

# Source/header files

PUBLIC_HEADERS := $(wildcard $(SRC_DIR)/include/*.h)
PUBLIC_HEADERS := $(filter-out $(SRC_DIR)/include/ctperf.h $(SRC_DIR)/include/internal/_ctcase.h $(SRC_DIR)/include/internal/_ctest.h $(SRC_DIR)/include/internal/_ctexpect.h $(SRC_DIR)/include/internal/_ctsuite.h, $(PUBLIC_HEADERS))
SOURCES := $(wildcard **/*.c)
OBJECTS := $(patsubst %.c, $(OBJ_DIR)/%.o, $(SOURCES))

# Rules

all: clean lib tests example

obj:
	mkdir -p $(OBJ_DIR)/$(SRC_DIR) && mkdir -p $(OBJ_DIR)/$(TESTS_DIR) && mkdir -p $(OBJ_DIR)/$(EXAMPLE_DIR)

bin:
	mkdir -p $(BIN_DIR)/include

headers: bin
	for fname in $(PUBLIC_HEADERS) ; do \
		cp $${fname} $(BIN_DIR)/include/ ; \
	done

$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

lib: obj headers $(OBJECTS)
	ar rcs $(BIN_DIR)/libcunit.a $(OBJ_DIR)/$(SRC_DIR)/*.o

tests: lib
	$(CC) $(OBJ_DIR)/$(TESTS_DIR)/*.o -o $(BIN_DIR)/CUnitTest -L $(BIN_DIR)/ -lcunit

example: lib
	$(CC) $(OBJ_DIR)/$(EXAMPLE_DIR)/*.o -o $(BIN_DIR)/CUnitExample -L $(BIN_DIR)/ -lcunit

install: lib
	mkdir -p /usr/local/include/cunit ; \
	cp -rf $(BIN_DIR)/include/*.h /usr/local/include/cunit/ ; \
	mkdir -p /usr/local/lib/cunit ; \
	cp -rf $(BIN_DIR)/libcunit.a /usr/local/lib/cunit/ ; \

clean:
	rm -rf $(OBJ_DIR) && rm -rf $(BIN_DIR)
