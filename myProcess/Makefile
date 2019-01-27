all:
	gcc -o process_test -O1 *.c *.h -Wall
	gcc -o process_test_debug -O1 *.c *.h -Wall -DDEBUG
	
clean:
	rm ./process_test ./process_test_debug

run:
	./process_test

debug:
	./process_test_debug
	
test:
	valgrind ./process_test
