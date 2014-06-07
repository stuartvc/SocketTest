#include "socket.h"        
#include "parse.h"


Socket::Socket() {
    sockfd_ = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd_ < 0) 
        error("ERROR opening socket");
    bzero((char *) &serv_addr_, sizeof(serv_addr_));
    serv_addr_.sin_family = AF_INET;
    serv_addr_.sin_addr.s_addr = INADDR_ANY;
    serv_addr_.sin_port = htons(50000);
    if (bind(sockfd_, (struct sockaddr *) &serv_addr_,
          sizeof(serv_addr_)) < 0) 
          error("ERROR on binding");
    listen(sockfd_,5);
    clilen_ = sizeof(cli_addr_);
}

Socket::~Socket() {
    close(sockfd_);
}

void Socket::readRequest(Request &request) {
    char buffer[256];
    newsockfd_ = accept(sockfd_, 
             (struct sockaddr *) &(cli_addr_), 
             &(clilen_));
    if (newsockfd_ < 0) {
        error("ERROR on accept");
    }
    bzero(buffer,256);
    int n = read(newsockfd_,buffer,255);
    if (n < 0) error("ERROR reading from socket");
    printf("Here is the message: %s\n",buffer);
    parse(request, buffer);
    request.setData();
}

void Socket::writeResponse(Response &response) {
    int n = write(newsockfd_,"I got your message",18);
    if (n < 0) error("ERROR writing to socket");
}

