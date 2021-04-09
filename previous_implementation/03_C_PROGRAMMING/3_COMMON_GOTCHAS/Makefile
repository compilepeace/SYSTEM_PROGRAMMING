
.PHONY: clean

all: 0_string_literals 1_memcpy_memmove

0_string_literals: 0_string_literals.c
	gcc $< -o $@

1_memcpy_memmove: 1_memcpy_memmove.c
	gcc $< -o $@

clean:
	rm 0_string_literals 1_memcpy_memmove
