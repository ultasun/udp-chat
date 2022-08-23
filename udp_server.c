/*
|   example UDP server
|   "inspired by" ... many examples
|   2011-10-16
*/
#include<stdio.h>
#include<stdlib.h>      // strtol()

#include<sys/socket.h>  //
#include<sys/types.h>   //
#include<arpa/inet.h>   // brings in netint/in.h, etc.
#include<netinet/in.h>  // need for (struct sockaddr_in) sizeof

#include "process.h"

#define BUF_SIZE        2049
#define ECHO_PORT       IPPORT_ECHO // from netinet/in.h

int main(int argc, char **argv)
{
    int retval;

    short int server_port;
    int udpSocket;
    struct sockaddr_in udpServer;

    /*
    | Obtain the server-port:
    */
    if (argc == 2) {
        char *endptr;
        server_port = strtol(argv[1], &endptr, 0);
        if (*endptr) {
            fprintf(stderr, "invalid port number: %s\n", argv[1]);
            return -9;
        }
    } else {
        fprintf(stderr, "usage: %s  <port-number>\n", argv[0]);
    }

    /*
    |   Create the listener socket:
    */
    udpSocket = socket(AF_INET, SOCK_DGRAM, 0);
        // default protocol for datagrams is UDP...
    if (udpSocket < 0) {
        fprintf(stderr, "Failure to create socket\n");
        return -1;
    }

    // setup server's address:port
    udpServer.sin_family = AF_INET;
    udpServer.sin_addr.s_addr = htonl(INADDR_ANY);
    udpServer.sin_port = htons(server_port);

    /*
    | Bind the socket:
    */
    retval = bind(udpSocket,
        (struct sockaddr *)&udpServer, sizeof(udpServer));
    if (retval < 0) {
        fprintf(stderr, "Failure to bind listener socket\n");
        return -1;
    }

    /*
    | no "listening"...
    */

    /*
    | Receive, respond to client messages
    */
    while (1) {
        struct sockaddr_in udpClient;
        socklen_t calength = sizeof(udpClient);
        int flags = 0;  // nothing special...

        char buffer[BUF_SIZE];
        char response[BUF_SIZE];
        ssize_t responsesize;

        fprintf(stderr, "waiting...\n");
        retval = recvfrom( udpSocket, buffer, BUF_SIZE, flags,
            (struct sockaddr *)&udpClient, &calength );
        if (retval < 0) {
            fprintf(stderr, "Failure to recvfrom socket\n");
            return -2;
        }
        fprintf(stderr, "Datagram from %s:%u\n",
            inet_ntoa(udpClient.sin_addr),
            ntohs(udpClient.sin_port) );
        fprintf(stderr, "\n Got -->%s<--\n", buffer);

        /*
        | Send back a reply
        */
        responsesize = process(response, buffer, BUF_SIZE) - response;

        retval = sendto( udpSocket, response, responsesize+1, flags,
            (struct sockaddr *)&udpClient, calength );
        if (retval < 0) {
            fprintf(stderr, "Failure to sendto socket\n");
        }
        fprintf(stderr, "    ... sent response -->%s<--\n", response);
    }

    // We'll never get here...
    retval = close(udpSocket);
    return 0;
}
//--------------------------------------------------------------------
