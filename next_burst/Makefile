all:
	gcc -o next_burst_main -O1 *.h *.c -Wall -w

run:
	./next_burst_main
	
test:
	valgrind ./next_burst_main

timing:
	time ./next_burst_main

clean:
	rm next_burst_main
