all:
	gcc -o scheduler_main -O1 ../process_list/process.h ../process_list/list_process.h ../next_burst/nextBurst.h scheduler.h ../process_list/process.c ../process_list/list_process.c ../next_burst/nextBurst.c scheduler.c scheduler_main.c -Wall -w

run:
	./scheduler_main
	
test:
	valgrind ./scheduler_main
	
timing:
	time ./scheduler_main

clean:
	rm ./scheduler_main
	rm *.txt
