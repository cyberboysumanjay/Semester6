/*
socket
bind
listen
accept
read
write
read
close
*/

#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>

int main( int argc, char *argv[] ) {
   int sockfd, newsockfd, portno, clilen;
   char buffer[256];
   struct sockaddr_in serv_addr, cli_addr;
   int  n;
   //socket
   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   bzero((char *) &serv_addr, sizeof(serv_addr));
   portno = 5001;
   serv_addr.sin_family = AF_INET;
   serv_addr.sin_addr.s_addr = INADDR_ANY;
   serv_addr.sin_port = htons(portno);
   //bind
   if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
      perror("ERROR in binding");
      exit(1);
   }
   //listen
   listen(sockfd,5);
   clilen = sizeof(cli_addr);
   newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
   //accept or communicate
   bzero(buffer,256);
   n = read( newsockfd,buffer,255 );
   printf("Message Received: %s\n",buffer);
   //write response
   n = write(newsockfd,"Sent Message",18);
   return 0;
}
