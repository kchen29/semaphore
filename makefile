all: main.o
	gcc main.o

main.o: main.c
	gcc -c main.c

clean:
	rm -f *.o *~ a.out

run: all
	./a.out -c 4
	./a.out -v
	./a.out -c 3
	./a.out -v
	./a.out -r
