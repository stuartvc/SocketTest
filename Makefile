all : server client

server : main.o user.o database.o response.o request.o parse.o handler.o
	g++ -o server main.o user.o database.o response.o request.o parse.o -l sqlite3

main.o : main.cpp request.h parse.h response.h database.h user.h 
	g++ -c main.cpp

user.o : user.cpp user.h
	g++ -c user.cpp

database.o : database.cpp database.h
	g++ -c database.cpp

request.o : request.cpp request.h
	g++ -c request.cpp

response.o : response.cpp response.h
	g++ -c response.cpp

handler.o : handler.cpp handler.h request.h
	g++ -c handler.cpp

parse.o : parse.cpp parse.h request.h
	g++ -c parse.cpp

client : client.o
	gcc -o client client.o

client.o : client.c
	gcc -c client.c

clean :
	rm -Rf *.o
	rm -Rf server client
