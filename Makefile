build: tema1

tema1: main.c
	gcc -Wall main.c queue.c train.c -o tema1
clean:
	rm -f tema1
run:
	./tema1
