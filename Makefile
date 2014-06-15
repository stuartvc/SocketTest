DIRS    := src
SOURCES := $(foreach dir, $(DIRS), $(wildcard $(dir)/*.cpp))
OBJS    := $(patsubst %.cpp, %.o, $(SOURCES))
OBJS    := $(foreach o,$(OBJS),./obj/$(o))
DEPFILES:= $(patsubst %.o, %.P, $(OBJS))

CFLAGS   = -Wall -MMD -c 
LDFLAGS=-lsqlite3 -lcrypto
COMPILER = g++
 
all : client server

client : client.o
	g++ client.o -o client 

client.o : client.c
	g++ -c client.c

#link the executable
server: $(OBJS)
	$(COMPILER) $(OBJS) $(LDFLAGS) -o server
 
#generate dependency information and compile
obj/%.o : %.cpp
	@mkdir -p $(@D)
	$(COMPILER) $(CFLAGS) -o $@ -MF obj/$*.P $<
 
#remove all generated files
clean:
	rm -f server 
	rm -f client 
	rm -rf obj
 
#include the dependency information
-include $(DEPFILES)
