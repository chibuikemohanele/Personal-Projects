#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

using namespace std;

int main(int argc, char ** argv){

    if(argc < 3){
        cout << "Program requires more inputs." << endl;
        return EXIT_FAILURE;
    }

    //Variable declaration
    int sockfd = 0;
    int portno = 0;
    int n = 0;
    struct sockaddr_in serv_addr;
    struct hostent * server = NULL;
    char * buffer = new(nothrow) char[256];

    //Initializing socket
    portno = stoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0){
        cout << "ERROR opening socket." <<endl;
        return EXIT_FAILURE;
    } 

    //Obtaining hostname
    server = gethostbyname(argv[1]);
    if(server == NULL) {
        cout << "Host name does not exist." <<endl;
        return EXIT_FAILURE;
    }

    //Connecting to socket 
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server -> h_length);

    serv_addr.sin_port = htons(portno);
    if(connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0){
        cout << "ERROR connecting to socket." <<endl;
        return EXIT_FAILURE;
    } 

    //Entering message to send to socket
    cout << "Please enter the message: " <<endl;
    bzero(buffer, 256);
    fgets(buffer,255,stdin);
    n = write(sockfd, buffer, strlen(buffer));
    if(n < 0){
        cout << "ERROR writing to socket." <<endl;
        return EXIT_FAILURE;
    }

    //Reading message returned by server socket
    bzero(buffer, 256);
    n = read(sockfd, buffer, 255);
    if(n < 0){
        cout << "ERROR reading from socket." <<endl;
        return EXIT_FAILURE;
    } 
    cout << buffer;
        
    //Closing sockets
    delete[](buffer);
    close(sockfd);
    return EXIT_SUCCESS;
}



