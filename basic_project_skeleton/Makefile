OS	:= $(shell uname)

ifeq ($(OS), Linux)


PROJECT_NAME := project_name_here

MKDIR   := mkdir
RMDIR   := rm -rf
CC      := gcc
BIN     := ./bin
OBJ     := ./obj
INCLUDE := ./include
SRC     := ./src
SRCS    := $(wildcard $(SRC)/*.cpp)
OBJS    := $(patsubst $(SRC)/%.cpp,$(OBJ)/%.o,$(SRCS))
CFLAGS  := -I$(INCLUDE) -g
LDLIBS  := #-lm
EXE	:= $(BIN)/$(PROJECT_NAME)

.PHONY: all clean #run

all: $(EXE)

$(EXE): $(OBJS) | $(BIN)
	$(CC) $(LDFLAGS) $^ -o $@ $(LDLIBS)

$(OBJ)/%.o: $(SRC)/%.cpp | $(OBJ)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN) $(OBJ):
	$(MKDIR) $@

#run: $(EXE)
#	$<

clean:
	$(RMDIR) $(OBJ) $(BIN)

endif
