#include <iostream>
#include <cstdlib>
#include <string>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

using namespace std;

int main(int argc, char ** argv){

    if(argc < 2){
        cout << "Incorrect number of arguments." << endl;
        return EXIT_FAILURE;
    }

    //Variable declaration
    int sockfd = 0;
    int newsockfd = 0;
    int portno = 0;
    socklen_t clilen;
    char * buffer = new(nothrow) char[256];
    struct sockaddr_in serv_addr;
    struct sockaddr_in cli_addr;
    int n = 0;

    //Creating TCP socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0){
        cout << "Socket fild descripto is invalid." << endl;
        return EXIT_FAILURE;
    }

    //Initializing variables
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = stoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    //Binding socket to address
    if(bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
        cout << "Error occured at binding." << endl;
        return EXIT_FAILURE;
    } 

    //Listening to socket for connection
    listen(sockfd, 5);
    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
    if (newsockfd < 0){
        cout << "Error on accepting." << endl;
        return EXIT_FAILURE;
    } 

    //Reading message from socket
    bzero(buffer, 256);
    n = read(newsockfd, buffer, 255);
    if (n < 0){
        cout << "Error reading from socket." << endl;
        return EXIT_FAILURE;
    }

    //Printing message sent from client
    cout << buffer << endl;
    n = write(newsockfd, "Message Recieved" ,16);
    if (n < 0){
        cout << "Error writing to socket." << endl;
        return EXIT_FAILURE;
    }
    
    //Closing sockets
    close(newsockfd);
    close(sockfd);
    delete[](buffer);
    return EXIT_SUCCESS;
}


