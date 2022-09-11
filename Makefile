PAYLOAD_SRC = prog.c
LOADER_SRC = main.c elf_wrapper.c

HDRS = $(wildcard *.h)

loader: payload.txt $(LOADER_SRC) $(HDRS)
	$(CC) $(LOADER_SRC) -o $@

payload.txt: $(PAYLOAD_SRC) $(HDRS)
	$(CC) $(PAYLOAD_SRC) -O2 -o payload.bin
	./to_hex.py payload.bin > $@

.PHONY: claen

clean:
	rm -rf loader payload.* *.o
