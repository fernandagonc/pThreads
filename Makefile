all:
	gcc -Wall -c main.c
	gcc -Wall -c thread.c -lpthread
	gcc -Wall -Wextra -std=c11 -ggdb3 main.o thread.o -o servidor_dns -lpthread

clean:
	rm main.o servidor_dns
