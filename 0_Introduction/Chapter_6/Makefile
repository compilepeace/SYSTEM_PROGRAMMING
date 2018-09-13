
.PHONY: clean


all: 0_signals 1_fork 2_fork_bomb


0_signals: 0_signals.c
	gcc $< -o $@

1_fork: 1_fork.c
	gcc $< -o $@


2_fork_bomb: 2_fork_bomb.c
	gcc $< -o $@


clean:
	rm 0_signals 1_fork 2_fork_bomb
