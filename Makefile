COMPILER = gcc -w

client:
	mkdir -p bin
	$(COMPILER) src/client.c -o bin/client

server:
	mkdir -p bin
	$(COMPILER) src/client.c -o bin/client

run-server:
	./bin/server

run-client:
	./bin/client

clean:
	rm -rf bin

