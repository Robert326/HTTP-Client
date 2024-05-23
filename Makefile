CC=gcc

client: client.c requests.c helpers.c buffer.c commands.c parson.c
	$(CC) -o client client.c requests.c helpers.c buffer.c commands.c parson.c -Wall
	
build: client

run: client
	./client

clean:
	rm -f *.o client
