#include "database.h"
#include "user.h"
#include "parse.h"
#include "request.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

void run();

int main() {
    database db((char*)"test.db");

    //user newUser1("Stuart", "Toronto", 22);
    //db.insertUser(&newUser1);

    user User;

    vector<vector<std::string> > vec = db.query((const char*)"SELECT * FROM USER");
    for( std::vector<vector<std::string> >::const_iterator i = vec.begin(); i != vec.end(); ++i) {
        vector<std::string> temp = *i;
        for ( std::vector<std::string>::const_iterator j = temp.begin(); j != temp.end(); j++)
            std::cout << *j << ' ';
        cout << endl;
    }

    db.getUser((char*)"Stuart", &User);
    cout << User.getName() << ", "
         << User.getLocation() << ", "
         << User.getAge() << endl;

    //user newUser("Jim", "Victoria", 22);

    //db.insertUser(&newUser);

    db.close();
    run();

    return 0;
}

void run() {
    int sockfd, newsockfd, portno;
    socklen_t clilen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    int n;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
    error("ERROR opening socket");
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = 50000;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    if (bind(sockfd, (struct sockaddr *) &serv_addr,
          sizeof(serv_addr)) < 0) 
          error("ERROR on binding");
    listen(sockfd,5);
    clilen = sizeof(cli_addr);

    while (1/*readfrom socket*/) {
        newsockfd = accept(sockfd, 
                 (struct sockaddr *) &cli_addr, 
                 &clilen);
        if (newsockfd < 0) {
            error("ERROR on accept");
        }
        bzero(buffer,256);
        n = read(newsockfd,buffer,255);
        //parse message
        if (n < 0) error("ERROR reading from socket");
        printf("Here is the message: %s\n",buffer);
        Request request;
        parse(request, buffer);
        fprintf(stdout, "name: \"%s\"\n", request.getQuery("name").c_str());
        n = write(newsockfd,"I got your message",18);
        if (n < 0) error("ERROR writing to socket");
        //put into request datatype
        
        
        //do some processing on request
        
        
        
        //database command
        
        
        
        //put into response datatype

        //write to socket
    }
    close(newsockfd);
    close(sockfd);
    return ; 
}
