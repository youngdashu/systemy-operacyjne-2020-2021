simple:
	gcc -Wall -c mergeFilesLib.c

	ar crs libmergeFilesLib.a mergeFilesLib.o

	gcc -Wall zad2.c -o zad2 -L. -lmergeFilesLib

	rm -f *.o
	rm -f *.a

test:
	make simple
	./zad2 test

