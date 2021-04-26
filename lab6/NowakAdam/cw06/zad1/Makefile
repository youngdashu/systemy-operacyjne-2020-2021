simple:

	gcc -Wall -c commonData.c

	ar crs libcommonData.a commonData.o

	gcc -Wall serwer.c -o serwer -L. -lcommonData
	gcc -Wall klient.c -o klient -L. -lcommonData

	rm -f *.o