all:
	gcc -o srjf_sim_auto -O1 *.h *.c -Wall -DVERSION=0 -w
	gcc -o srjf_sim_file -O1 *.h *.c -Wall -DVERSION=1 -w

run_auto:
	./srjf_sim_auto

run_file:
	./srjf_sim_file
	
clean:
	rm srjf_sim_auto srjf_sim_file file_processes/scheduler.txt

test_auto:
	valgrind ./srjf_sim_auto
	
timing_auto:
	time ./srjf_sim_auto
