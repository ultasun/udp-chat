/*
	UDP client
	works on linux
*/
#include <stdio.h>
#include <stdlib.h> // strtol()
#include <string.h> // memset()

#include <netinet/in.h> // need for sizeof(struct socket_addr_in)
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

#define BUFFSIZE 2049

int main(int argc, char **argv)
{
  int retval;
  int flags = 0; // nothing special

  short int otherPort;
  int udpSocket;
  struct sockaddr_in udpOther;
  socklen_t salength = sizeof(udpOther);

  size_t sentlength;
  char msg[BUFFSIZE];
  char response[BUFFSIZE];

  /*
  set up other's address and port:
  */
  if (argc == 3) {
    char *ep;
    // convert inet addr string (from console)
    // into an inet address value, and put it in
    // udpOther.sin_addr
    retval = inet_aton(argv[1], &(udpOther.sin_addr));
    if (!retval) {
      // if it's an invalid ip address
      fprintf(stderr, "bad IP address %s\n", argv[1]);
      return -1;
    }

    otherPort = strtol(argv[2], &ep, 0);
    if (*ep) {
      // if it's an invalid port
      fprintf(stderr, "bad port number %s\n", argv[2]);
      return -1;
    }
    udpOther.sin_port = htons(otherPort);

  } else {
    // complain about the whole thing if invalid cmdline args
    fprintf(stderr, "usage: %s IP-address port\n", argv[0]);
    return -1;
  }

  udpOther.sin_family = AF_INET;
  memset(&udpOther.sin_zero, 0, sizeof(udpOther.sin_zero));
  // that has setup the address for us. now bind to a port

  // now bind to a socket
  udpSocket = socket(AF_INET, SOCK_DGRAM, 0);
  if (udpSocket < 0) {

    fprintf(stderr, "failed to create socket\n");
    return -2;
  }  

  // loop the chat program
  do { 
    // get user input to send message
    fprintf(stderr, "Message to send? ");
    fgets(msg, BUFFSIZE, stdin);

    // send message
    sentlength = sendto(udpSocket, msg, strlen(msg)+1, flags,
      (struct sockaddr *) &udpOther, salength);

    // more error checking
    // or not
  
    fprintf(stderr, "waiting...\n");
    retval = recvfrom(udpSocket, response, BUFFSIZE, flags,
      (struct sockaddr *) &udpOther, &salength);

    fprintf(stderr, "Got %u bytes: -->\n\t%s\n<-- from %s:%u\n",
      retval, response, inet_ntoa(udpOther.sin_addr),
	    ntohs(udpOther.sin_port));
  
  } while(strlen(msg) != 1); 

  return 0;
}
