#ifndef SOCKET_H_
#define SOCKET_H_
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "request.h"
#include "response.h"

typedef struct {
} socketInfo;

class Socket {
    public:
        Socket();
        ~Socket();
        void readRequest(Request &request);
        void writeResponse(Response &response);

    private:
        void error();
        inline void error(const char *msg) {
            perror(msg);
            exit(1);
        }

        int sockfd_;
        struct sockaddr_in serv_addr_, cli_addr_;
        socklen_t clilen_;
        int newsockfd_;
};


#endif
