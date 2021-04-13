simple:
	gcc -Wall sender.c -o sender
	gcc -Wall catcher.c -o catcher
	gcc -Wall wrapper.c -o wrapper


kill:
	./wrapper 100000 kill

sigqueue:
	./wrapper 100000 sigqueue

sigrt:
	./wrapper 100000 sigrt

test:
	make simple
	./wrapper 100000 kill
	sleep 2
	./wrapper 100000 sigqueue
	sleep 2
	./wrapper 100000 sigrt