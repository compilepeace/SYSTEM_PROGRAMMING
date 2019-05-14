.PHONY: clean log


T0= 0_without_mutex
T1= 1_mutex_lock
T2= 2_semaphore_lock
TARGETS= $(T0) $(T1) $(T2)

LOGFILE1= log_output_with_mutex
LOGFILE2= log_output_race_condition


FLAGS= -std=c99 -Wall -Werror

all: $(TARGETS)


$(T1): $(T1).c
	gcc $< -o $@ $(FLAGS) -pthread

$(T0): $(T0).c
	gcc $< -o $@ $(FLAGS) -pthread

$(T2): $(T2).c
	gcc $< -o $@ $(FLAGS) -pthread


clean:
	rm $(T2) $(T1) $(T0) 


log:
	./log_script.sh

clean_log:
	rm $(LOGFILE1) $(LOGFILE2)
