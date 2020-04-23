
.PHONY: clean

all: 0_printf_write 1_print_to_file_streams 2_strtol 3_fgets_getline


0_printf_write: 0_printf_write.c
	gcc $< -o $@

1_print_to_file_streams: 1_print_to_file_streams.c
	gcc $< -o $@

2_strtol: 2_strtol.c
	gcc $< -o $@

3_fgets_getline: 3_fgets_getline.c
	gcc $< -o $@

clean:
	rm 0_printf_write 1_print_to_file_streams 2_strtol 3_fgets_getline
