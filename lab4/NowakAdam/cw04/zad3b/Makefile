simple:
	gcc -Wall sender.c -o sender
	gcc -Wall catcher.c -o catcher
	gcc -Wall wrapper.c -o wrapper

kill:
	make simple
	./wrapper 10000 kill

sigqueue:
	make simple
	./wrapper 10000 sigqueue

sigrt:
	make simple
	./wrapper 100000 sigrt