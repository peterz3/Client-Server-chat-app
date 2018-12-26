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
    //only argument needed to pass in fo server side is the port
    //number on which the app will be hosted, make sure its over 2000

    if(argc != 2 ){
        cerr << "please specify a port number greater that 2000" << endl;
        exit(0);
    }
    int status;

    //buffer used to read messages
    char buf[1000];
    //structs used for sockets 
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
    int serverSd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if(serverSd < 0)
    {
        cerr << "Error establishing the server socket" << endl;
        exit(0);
    }
    //bind the socket to local address
    bind(serverSd, res->ai_addr,res->ai_addrlen);
    cout << "server side binded " << endl;
}
