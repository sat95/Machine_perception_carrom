all: learn test

CC = gcc

learn: learn.c
	$(CC) $< -lm -o $@ 

test: test.c
	$(CC) $< -lm -o $@

clean:
	rm -f learn test