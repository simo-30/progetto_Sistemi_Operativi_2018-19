all:
	gcc -o procMain -O1 proc.h proc.c main.c -Wall -w
	
run:
	./procMain

test:
	valgrind ./procMain

clean:
	rm procMain
