

.PHONY: clean

all: 0_datatype_sizes 1_pointer_arithemetic 2_strings



0_datatype_sizes: 0_datatype_sizes.c
	gcc $< -o $@

1_pointer_arithemetic: 1_pointer_arithemetic.c
	gcc $< -o $@

2_strings: 2_strings.c
	gcc $< -o $@


clean:
	rm  0_datatype_sizes 1_pointer_arithemetic 2_strings
