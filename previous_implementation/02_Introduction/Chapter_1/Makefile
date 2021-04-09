

.PHONY: clean

all: 0_Hello_syscall 1_hello_error_stream 2_Write_to_file 3_closing_stdout 4_redirect_stderr



0_Hello_syscall: 0_Hello_syscall.c
	gcc $< -o $@

1_hello_error_stream: 1_hello_error_stream.c
	gcc $< -o $@

2_Write_to_file: 2_Write_to_file.c
	gcc $< -o $@

3_closing_stdout: 3_closing_stdout.c
	gcc $< -o $@

4_redirect_stderr: 4_redirect_stderr.c
	gcc $< -o $@


clean:
	rm  0_Hello_syscall 1_hello_error_stream 2_Write_to_file 3_closing_stdout 4_redirect_stderr dummy.txt dummy1.txt errors.txt
