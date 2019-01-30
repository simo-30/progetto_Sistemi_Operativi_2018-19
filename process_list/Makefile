all:
	gcc -o process_main -O1 process.h process.c process_main.c -Wall -w
	gcc -o list_process_main -O1 process.h process.c list_process.h list_process.c list_process_main.c -Wall -w
	
run:
	./process_main
	./list_process_main

test:
	valgrind ./process_main
	valgrind ./list_process_main
	
clean:
	rm process_main
	rm list_process_main

timing:
	time ./list_process_main
