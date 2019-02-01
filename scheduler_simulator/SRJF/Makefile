all:
	gcc -o srjf_sim_auto -O1 *.h *.c -Wall -DVERSION=0 -w
	gcc -o srjf_sim_file -O1 *.h *.c -Wall -DVERSION=1 -w

run_auto:
	./srjf_sim_auto

clean:
	rm srjf_sim_auto srjf_sim_file
