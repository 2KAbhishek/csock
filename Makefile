COMPILER = gcc -w

client:
	mkdir -p bin
	$(COMPILER) src/client.c -o bin/client

server:
	mkdir -p bin
	$(COMPILER) src/server.c -o bin/server

run-server:
	make server
	./bin/server

run-client:
	make client
	./bin/client

clean:
	rm -rf bin

