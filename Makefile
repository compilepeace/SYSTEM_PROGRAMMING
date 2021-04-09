OS	:= $(shell uname)

ifeq ($(OS), Linux)

CC  = g++
BIN = ./bin
SRC = ./src

BINS = $(BIN)/4_1_custom_tee $(BIN)/4_2_cp_holes

all: $(BINS)

.PHONY: all clean #run

$(BIN)/4_1_custom_tee: $(SRC)/4_1_custom_tee.cpp
	$(CC) $^ -o $@

$(BIN)/4_2_cp_holes: $(SRC)/4_2_cp_holes.cpp
	$(CC) $^ -o $@

clean:
	rm -f $(BIN)/*

endif
