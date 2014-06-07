CC=g++
CFLAGS=-c -Wall
LDFLAGS=-lsqlite3
SERVERSOURCES=main.cpp\
		user.cpp\
		database.cpp\
		response.cpp\
		request.cpp\
		parse.cpp\
		handler.cpp\
		socket.cpp

CLIENTSOURCES=client.c

SOURCES=$(SERVERSOURCES) $(CLIENTSOURCES)

SERVEROBJECTS=$(SERVERSOURCES:.cpp=.o)
	SERVER=server

CLIENTOBJECTS=$(CLIENTSOURCES:.cpp=.o)
	CLIENT=client

all: $(SOURCES) $(SERVER) $(CLIENT)
		
$(CLIENT): $(CLIENTOBJECTS) 
		$(CC) $(CLIENTOBJECTS) -o $@

$(SERVER): $(SERVEROBJECTS) 
		$(CC) $(SERVEROBJECTS) $(LDFLAGS) -o $@

.cpp.o:
		$(CC) $(CFLAGS) $< -o $@

clean :
	rm *.o
	rm server client
