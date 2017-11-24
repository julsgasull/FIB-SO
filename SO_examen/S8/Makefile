all: exServerSocket exClientSocket sin_nombre lector escritor lector_socket escritor_socket


sin_nombre: 
	gcc -o sin_nombre sin_nombre.c

lector:
	gcc -o lector lector.c
escritor:
	gcc -o escritor escritor.c

lector_socket:
	gcc -o lector_socket lector_socket.c
escritor_socket:
	gcc -o escritor_socket escritor_socket.c

exServerSocket: exServerSocket.c socketMng.o
	gcc -o exServerSocket exServerSocket.c socketMng.o

exClientSocket: exClientSocket.c socketMng.o
	gcc -o exClientSocket exClientSocket.c socketMng.o

socketMng.o: socketMng.c
	gcc -c socketMng.c

clean: 
	rm -f exServerSocket exClientSocket socketMng.o sin_nombre lector escritor lector_socket escritor_socket