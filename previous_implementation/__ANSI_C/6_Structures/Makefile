

.PHONY: clean 
FLAGS= -fno-stack-protector

all: operations


operations: operations.c 
	gcc $(FLAGS) $< -o $@ 

clean:
	rm operations
