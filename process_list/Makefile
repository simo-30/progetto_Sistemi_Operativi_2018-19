all:
	gcc -o process_main -O1 process.h process.c process_main.c -Wall -DDEBUG
	
run:
	./process_main

test:
	valgrind ./process_main
	
clean:
	rm process_main
