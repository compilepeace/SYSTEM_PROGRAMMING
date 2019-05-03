.PHONY: clean


T1= simplest_thread
T2= thread1
T3= thread2
T4= thread3
T5= passing_stack_variable
T6= race_conditions

TARGETS= $(T1) $(T2) $(T3) $(T4) $(T5) $(T6)

all: $(TARGETS)

FLAGS= -Wall -Werror -std=c99


$(T1): $(T1).c
	gcc $< -o $@ $(FLAGS) -pthread

$(T2): $(T2).c
	gcc $< -o $@ $(FLAGS) -pthread

$(T3): $(T3).c
	gcc $< -o $@ $(FLAGS) -pthread

$(T4): $(T4).c
	gcc $< -o $@ $(FLAGS) -pthread

$(T5): $(T5).c
	gcc $< -o $@ $(FLAGS) -pthread

$(T6): $(T6).c
	gcc $< -o $@ $(FLAGS) -pthread

clean:
	rm $(T1) $(T2) $(T3) $(T4) $(T5) $(T6)
