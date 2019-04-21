
.PHONY: clean


T1= fork
FLAGS= -std=c99 -Wall -Werror
all: $(T1)


$(T1): $(T1).c
	gcc $< -o $@ $(FLAGS)

clean:
	rm $(T1)
