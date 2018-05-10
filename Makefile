FLAGS= -O3 -Wall
CC=gcc


all: dijkstraSerial dijkstraParalelo dijkstraSerialDebug dijkstraParaleloDebug

clean:
	rm -f *.o dijkstraSerial dijkstraParalelo dijkstraSerialDebug dijkstraParaleloDebug

dijkstraSerial: dijkstraSerial.c
	$(CC) $< -o $@

dijkstraParalelo: dijkstraParalelo.c
	$(CC) $< -fopenmp -o $@

dijkstraSerialDebug: dijkstraSerial.c
	$(CC)  dijkstraSerial.c -DDEBUG -o $@ 

dijkstraParaleloDebug: dijkstraParalelo.c
	$(CC)  dijkstraParalelo.c -DDEBUG -fopenmp -o $@
