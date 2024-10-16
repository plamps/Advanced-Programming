all: p1 p2 p3 p4 p5 p6 file_fork

clean:
	rm -f p1 p2 p3 p4 p5 p6 file_fork output.txt

p1: p1.c
	gcc -o p1 p1.c -Wall

p2: p2.c
	gcc -o p2 p2.c -Wall

p3: p3.c
	gcc -o p3 p3.c -Wall

p4: p4.c
	gcc -o p4 p4.c -Wall

p5: p5.c
	gcc -o p5 p5.c -Wall

p6: p6.c
	gcc -o p6 p6.c -Wall

file_fork: file_fork.c
	gcc -o file_fork file_fork.c -Wall

test: all
	bash run_tests.sh