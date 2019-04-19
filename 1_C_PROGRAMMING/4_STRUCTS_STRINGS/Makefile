
.PHONY: clean edit run

T1=test_my_library

TARGETS= $(T1) 

all: $(TARGETS)


$(T1): $(T1).c
	gcc $< -o $@

clean:
	rm $(T1) 

edit:
	vim $(T1).c

run:
	./$(T1)
