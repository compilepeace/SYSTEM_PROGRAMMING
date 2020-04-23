

.PHONY: clean

all: 0_arguments_atoi 1_environment 2_strings_and_ptrs 3_stack_segment


0_arguments_atoi: 0_arguments_atoi.c
	gcc $< -o $@

1_environment: 1_environment.c
	gcc $< -o $@

2_strings_and_ptrs: 2_strings_and_ptrs.c
	gcc $< -o $@

3_stack_segment: 3_stack_segment.c
	gcc $< -o $@

clean:
	rm 0_arguments_atoi 1_environment 2_strings_and_ptrs 3_stack_segment
