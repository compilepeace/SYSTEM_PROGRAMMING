.PHONY: clean


T1= dots
T2= signal

TARGETS= $(T1) $(T2)
FLAGS= -std=c99 -Wall -Werror

all: $(TARGETS)


$(T1): $(T1).c
	gcc $< -o $@ $(FLAGS) 

$(T2): $(T2).c
	gcc $< -o $@ $(FLAGS)

clean:
	rm $(T1) $(T2)
