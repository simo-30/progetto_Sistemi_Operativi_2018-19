all:
	gcc -o procMain -O1 proc_vector.h proc_vector.c main.c -Wall -w
	
run:
	./procMain

test:
	valgrind ./procMain

clean:
	rm procMain
