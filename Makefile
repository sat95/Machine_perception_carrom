
all: learn test onetime main

learn: learn.c
	gcc $^ -lm -o $@

test: test.c
	gcc $^ -lm -o $@

onetime: onetime.c
	gcc $^ -o  $@

main: main.c
	gcc $^ -o $@


clean:
	rm -f test learn 1_time main