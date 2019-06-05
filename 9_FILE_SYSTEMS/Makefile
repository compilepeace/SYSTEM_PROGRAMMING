

.PHONY: clean


TARGETS= 1_mmap_file 2_shared_memory
all: $(TARGETS)


1_mmap_file: 1_mmap_file.c
	gcc $< -o $@

2_shared_memory: 2_shared_memory.c
	gcc $< -o $@

clean: 
	rm $(TARGETS)
