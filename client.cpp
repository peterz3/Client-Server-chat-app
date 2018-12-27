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
        cerr << "please specify ip address and port number of server(in that order)" << endl;
        exit(0);
    }
    int status;

    char buf[1000];

    addrinfo hints, *res;

    memset(&hints, 0, sizeof(hints));

    hints.ai_family = AF_UNSPEC;  // use IPv4 or IPv6, whichever
    hints.ai_socktype = SOCK_STREAM; //connection is run until one side disconnects
    hints.ai_flags = AI_PASSIVE;

    if((status = getaddrinfo(argv[1], argv[2] , &hints, &res)) != 0){
       fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
       //print error if address info returns non-zero
    }

    //open stream oriented socket with internet address
    // keep track of the server socket descriptor
    int clientSide = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if(clientSide < 0)
    {
        cerr << "Error establishing the server socket" << endl;
        exit(0);
    }

    connect(clientSide, res->ai_addr, res->ai_addrlen);
    if (status < 0)
    {
        cout << "Error connecting to socket!" << endl;
    }

    cout << "established connection with server" << endl;

    while(1)
    {
        string data;
        cout << "Client: " << buf << endl;
        cout << ">";
        //gets server input
        getline(cin, data);
        memset(&buf, 0, sizeof(buf)); //clear the buffer
        strcpy(buf, data.c_str());
        //checks if server wrote exit
        if(data == "exit")
        {
            //send to the client that server has closed the connection
            send(clientSide, (char*)&buf, strlen(buf), 0);
            break;
        }
        //send the message to client
        send(clientSide, (char*)&buf, strlen(buf), 0);
        memset(&buf, 0, sizeof(buf));
        recv(clientSide, (char *)&buf, sizeof(buf), 0);
        if (strcmp(buf, "exit") == 0)
        {
            cout << "Server exited" << endl;
            break;
        }
        cout << "Server: " << buf << endl;
    }
    //closing client socket
        close(clientSide);

        cout << "closing connections and ending session" << endl;
        return 0;
}