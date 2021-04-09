
.PHONY: clean


all: 0_getchar_encrypt 1_gets_danger 2_fsscanf 3_getline


CFLAGS=-fno-stack-protector


0_getchar_encrypt: 0_getchar_encrypt.c
	gcc $< -o $@

1_gets_danger: 1_gets_danger.c
	gcc $(CFLAGS) $< -o $@

2_fsscanf: 2_fsscanf.c
	gcc $< -o $@

3_getline: 3_getline.c
	gcc $< -o $@

clean:
	rm 0_getchar_encrypt 1_gets_danger 2_fsscanf 3_getline
