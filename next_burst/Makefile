all:
	gcc -o next_burst_main -O1 ../process_list/list_process.h ../process_list/list_process.c ../process_list/process.h ../process_list/process.c nextBurst.h nextBurst.c nextBurst_main.c -Wall -w

run:
	./next_burst_main
	
test:
	valgrind ./next_burst_main

timing:
	time ./next_burst_main

clean:
	rm next_burst_main
