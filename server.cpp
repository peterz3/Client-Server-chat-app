#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
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
}
