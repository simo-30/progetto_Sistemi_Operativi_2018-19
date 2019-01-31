all:
	gcc -o scheduler_main -O1 process.h list_process.h nextBurst.h scheduler.h process.c list_process.c nextBurst.c scheduler.c scheduler_main.c -Wall -w

run:
	./scheduler_main
	
test:
	valgrind ./scheduler_main
	
timing:
	time ./scheduler_main

clean:
	rm ./scheduler_main
	rm *.txt
