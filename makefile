s:
	gcc -o server dame-s.c 
	./server

c:
	gcc -o client dame-c.c 
	./client 127.0.0.1 2024
