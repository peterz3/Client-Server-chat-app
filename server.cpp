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

#define BACKLOG 5

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
    int serverSide = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if(serverSide < 0)
    {
        cerr << "Error establishing the server socket" << endl;
        exit(0);
    }
    //bind the socket to local address
    bind(serverSide, res->ai_addr,res->ai_addrlen);
    cout << "server side binded " << endl;
    //listens to server socket
    listen(serverSide, BACKLOG);
    
    //new socket storage that will maintain connected clients
    sockaddr_storage newSockAddr;
    socklen_t newSockAddrSize = sizeof(newSockAddr);
     //accept, create a new socket descriptor to 
    //handle the new connection with client
    int newSide = accept(serverSide, (sockaddr *)&newSockAddr, &newSockAddrSize);
    if(newSide < 0)
    {
        cerr << "Error accepting request from client!" << endl;
        exit(1);
    }
    cout << "established connection with client" << endl;
    while(1)
    {
        //receive a message from the client (listen)
        cout << "Awaiting client response..." << endl;
        memset(&buf, 0, sizeof(buf));//clear the buffer
        if(!strcmp(buf, "exit"))
        {
            cout << "Client has quit the session" << endl;
            break;
        }
        cout << "Client: " << buf << endl;
        cout << ">";
        string data;
        getline(cin, data);
        memset(&buf, 0, sizeof(buf)); //clear the buffer
        recv(newSide, (char*)buf, sizeof(buf), 0);
        strcpy(buf, data.c_str());
        if(data == "exit")
        {
            //send to the client that server has closed the connection
            send(newSide, (char*)&msg, strlen(msg), 0);
            break;
        }
        //send the message to client
        send(newSide, (char*)&msg, strlen(msg), 0);
    }

    close(newSide);
    close(serverSide);
    cout << "closing connections and ending session";

    return 0;
}
