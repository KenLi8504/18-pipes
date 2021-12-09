all: pipes.o
	gcc -o main pipes.o

pipes.o:
	gcc -c pipes.c

run:
	./main

clean:
	rm main
