simple:
	gcc -Wall sender.c -o sender
	gcc -Wall catcher.c -o catcher
	gcc -Wall wrapper.c -o wrapper

test:
	make simple
	# ./wrapper 100000 kill
	# sleep 2
	# ./wrapper 1000 sigqueue
	# sleep 2
	./wrapper 100000 sigrt