#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
using namespace std;

int main(int argc, char *argv[]){

    // arguments needed to pass in to client side is the port
    //number on which the server is hosted and the ip address

    if(argc != 3 ){
        cerr << "please specify a port number and ip address of server" << endl;
        exit(0);
    }
    int status;

    char buf[1000];

    addrinfo hints, *res;

    memset(&hints, 0, sizeof(hints));

    hints.ai_family = AF_UNSPEC;  // use IPv4 or IPv6, whichever
    hints.ai_socktype = SOCK_STREAM; //connection is run until one side disconnects
    hints.ai_flags = AI_PASSIVE;

    if((status = getaddrinfo(NULL, argv[1] , &hints, &res)) != 0){
       fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
       //print error if address info returns non-zero
    }

    //open stream oriented socket with internet address
    // keep track of the server socket descriptor
    int serverSide = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if(serverSide < 0)
    {
        cerr << "Error establishing the server socket" << endl;
        exit(0);
    }
}