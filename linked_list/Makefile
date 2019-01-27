all:
	gcc -o list_test -O1 *.c *.h -Wall
	gcc -o list_test_debug -O1 *.c *.h -Wall -DDEBUG 

clean:
	rm list_test
	rm list_test_debug

run:
	./list_test

test:
	valgrind ./list_test

debug:
	./list_test_debug
