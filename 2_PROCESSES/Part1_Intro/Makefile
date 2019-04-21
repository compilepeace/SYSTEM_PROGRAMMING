
.PHONY: clean

T1= simplest_fork
T2= shock_flush
T3= ppid_cpid
T4= fork_bomb
T5= wait_for_child
T6= exec
FLAGS= -std=c99 -Wall -Werror
TARGETS= $(T1) $(T2) $(T3) $(T4) $(T5) $(T6)

all: $(TARGETS)


$(T1): $(T1).c
	gcc $< -o $@ $(FLAGS)

$(T2): $(T2).c
	gcc $< -o $@ $(FLAGS)

$(T3): $(T3).c
	gcc $< -o $@ $(FLAGS)

$(T4): $(T4).c
	gcc $< -o $@ $(FLAGS)

$(T5): $(T5).c
	gcc $< -o $@ $(FLAGS)

$(T6): $(T6).c
	gcc $< -o $@ $(FLAGS)

clean:
	rm $(T1) $(T2) $(T3) $(T4) $(T5) $(T6)
