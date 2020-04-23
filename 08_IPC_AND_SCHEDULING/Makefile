.PHONY: clean 


T0= 1_pipes
T1= 2_pipe_block
T2= 3_pipe_gotchas
T3= 4_fdopen
T4= 5_pipes_fdopen
T5= 6_close_pipe
TARGETS= $(T0) $(T1) $(T2) $(T3) $(T4) $(T5)

FLAGS= -Wall -Werror

all: $(TARGETS)


$(T0): $(T0).c
	gcc $< -o $@ $(FLAGS) 

$(T1): $(T1).c
	gcc $< -o $@ $(FLAGS)

$(T2): $(T2).c
	gcc $< -o $@ -std=c99 $(FLAGS)

$(T3): $(T3).c
	gcc $< -o $@ -std=gnu99 $(FLAGS)

$(T4): $(T4).c
	gcc $< -o $@ -std=gnu99 $(FLAGS)

$(T5): $(T5).c
	gcc $< -o $@ -std=gnu99 $(FLAGS)

clean:
	rm $(T0) $(T1) $(T2) $(T3) $(T4) $(T5)

