.PHONY: clean


T1= heap_boundary
T2= clear_memory
TARGETS= $(T1) $(T2)

FLAGS= -Wall -Werror

all: $(TARGETS)

$(T1): $(T1).c
	gcc $< -o $@ $(FLAGS)

$(T2): $(T2).c
	gcc $< -o $@ $(FLAGS)

clean:
	rm $(T1) $(T2)
