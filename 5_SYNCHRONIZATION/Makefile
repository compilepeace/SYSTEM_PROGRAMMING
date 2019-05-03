.PHONY: clean


T1= mutex_lock
TARGETS= $(T1)

FLAGS= -std=c99 -Wall -Werror

all: $(TARGETS)


$(T1):$(T1).c
	gcc $< -o $@ $(FLAGS) -pthread


clean:
	rm $(T1)
