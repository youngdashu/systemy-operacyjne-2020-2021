simple:
	gcc -Wall mergeFilesLib.c main.c -o main

o:
	gcc -Wall -c mergeFilesLib.c
	gcc -Wall mergeFilesLib.o main.c -o main

smart:
	make clean
	make o
	rm -f *.o

clean:
	rm -f *.o main