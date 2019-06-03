
.PHONY: clean 

CC= gcc

OBJECTS= objects
SPIDER= bin/spider 
 
FLAGS= --std=gnu99

all: $(SPIDER)



$(SPIDER): 1_file_operations.o 2_dir_operations.o main.o
	mv *.o objects
	$(CC) $(OBJECTS)/1_file_operations.o $(OBJECTS)/2_dir_operations.o $(OBJECTS)/main.o -o $(SPIDER)


$(OBJECTS)/main.o: main.c
	$(CC) -c $< -o $(OBJECTS)


$(OBJECTS)/1_file_operations.o: 1_file_operations.c
	$(CC) -c $< -o $(OBJECTS)


$(OBJECTS)/2_dir_operations.o: 2_dir_operations.c
	$(CC) -c $< -o $(OBJECTS)



clean: 
	rm $(SPIDER) $(OBJECTS)/*

