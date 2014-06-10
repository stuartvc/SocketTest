CC=g++
CFLAGS=-c -Wall
LDFLAGS=-lsqlite3 -lcrypto
SERVERSOURCES=main.cpp\
		user.cpp\
		database.cpp\
		response.cpp\
		request.cpp\
		parse.cpp\
		handler.cpp\
		socket.cpp\
		logging.cpp

CLIENTSOURCES=client.c
ifndef _ARCH 
	_ARCH := $(shell uname) 
	export _ARCH 
endif
ifeq ($(shell uname), SunOS)
	LDFLAGS += -lsocket -lnsl
endif


SOURCES=$(SERVERSOURCES) $(CLIENTSOURCES)

SERVEROBJECTS=$(SERVERSOURCES:.cpp=.o)
	SERVER=server

CLIENTOBJECTS=$(CLIENTSOURCES:.cpp=.o)
	CLIENT=client

all: $(SOURCES) $(SERVER) $(CLIENT)
		
$(CLIENT): $(CLIENTOBJECTS) 
		$(CC) $(CLIENTOBJECTS) $(LDFLAGS) -o $@

$(SERVER): $(SERVEROBJECTS) 
		$(CC) $(SERVEROBJECTS) $(LDFLAGS) -o $@

.cpp.o:
		$(CC) $(CFLAGS) $< -o $@

clean :
	rm *.o
	rm server client
