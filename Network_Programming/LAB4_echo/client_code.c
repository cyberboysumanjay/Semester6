#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>

void echo_client(int sockfd) {
    char buff[100], buff1[1000];
    puts("Enter message\n");
    fgets(buff, 100, stdin);
    send(sockfd, buff, 100, 0);
    recv(sockfd, buff1, 100, 0);
    puts("Message from server...");
    printf(buff1);
  }

int main(int argc, char *argv[]) {
     int sockfd, portno, n;
     struct sockaddr_in serv_addr;
     struct hostent *server;
     char buffer[256];
     if (argc < 3) {
        fprintf(stderr,"Enter in this format: %s hostname port\n", argv[0]);
        exit(0);
     }
     portno = atoi(argv[2]);
     //Creating Socket
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) {
        perror("ERROR in opening socket");
        exit(1);
     }
     server = gethostbyname(argv[1]);
     if (server == NULL) {
        fprintf(stderr,"No such host found\n");
        exit(0);
     }

     bzero((char *) &serv_addr, sizeof(serv_addr));
     serv_addr.sin_family = AF_INET;
     bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
     serv_addr.sin_port = htons(portno);

     //Connecting
     if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR in connecting");
        exit(1);
     }
     //Echo function
     echo_client(sockfd);

}
