all:
	gcc -o srjf_sim_auto -O1 *.h *.c -Wall -DVERSION=0 -w
	gcc -o srjf_sim_file -O1 *.h *.c -Wall -DVERSION=1 -w

run_auto:
	./srjf_sim_auto

run_file:
	./srjf_sim_file "file_processes/procIn/normal.txt" "file_processes/fileSCHED_norm.txt"
	
clean:
	rm srjf_sim_auto srjf_sim_file file_processes/*.txt

test_auto:
	valgrind ./srjf_sim_auto

test_file:
	valgrind ./srjf_sim_file "file_processes/procIn/normal.txt" "file_processes/fileSCHED_norm.txt"
	
timing_auto:
	time ./srjf_sim_auto

timing_file:
	time ./srjf_sim_file "file_processes/procIn/normal.txt"

go_auto:
	./srjf_sim_auto "file_processes/normal.txt"
	./srjf_sim_auto 5 10 2 "file_processes/simple.txt"
	./srjf_sim_auto 100 10 10 "file_processes/plusProc.txt"
	./srjf_sim_auto 10 20 30 "file_processes/plusDur.txt"

go_file:
	./srjf_sim_file "file_processes/procIn/normal.txt" "file_processes/fileSCHED_norm.txt"
	./srjf_sim_file "file_processes/procIn/sched1.txt" "file_processes/fileSCHED_sched1.txt"

runAll:
	./srjf_sim_auto "file_processes/normal.txt"
	./srjf_sim_auto 5 10 2 "file_processes/simple.txt"
	./srjf_sim_auto 100 10 10 "file_processes/plusProc.txt"
	./srjf_sim_auto 10 20 30 "file_processes/plusDur.txt"
	./srjf_sim_file "file_processes/procIn/normal.txt" "file_processes/fileSCHED_norm.txt"
	./srjf_sim_file "file_processes/procIn/sched1.txt" "file_processes/fileSCHED_sched1.txt"
