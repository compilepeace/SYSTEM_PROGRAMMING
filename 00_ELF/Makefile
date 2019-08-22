
.PHONY: clean


TARGETS= parse_elf_header parse_sht parse_pht

all: $(TARGETS)


parse_elf_header: parse_elf_header.c
	gcc $< -o $@

parse_sht: parse_sht.c
	gcc $< -o $@

parse_pht: parse_pht.c
	gcc $< -o $@

clean:
	rm $(TARGETS)
