all:
	gcc -o prediction_main -O1 *.h *.c -Wall -w

run:
	./prediction_main
	
test:
	valgrind ./prediction_main

timing:
	time ./prediction_main
