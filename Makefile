FLAGS= -O3 -Wall
CC=gcc


all: dijkstraSerial dijkstraParalelo

clean:
	rm -f *.o dijkstraSerial dijkstraParalelo

dijkstraSerial: dijkstraSerial.c
	$(CC) $< -o $@

dijkstraParalelo: dijkstraParalelo.c
	$(CC) $< -openmp -o $@
