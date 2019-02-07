//Step 1- Included appropriate Header Files
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>

void echo_message(int acc){
  //Receiving data
  int n;
  char buffer[256];
  bzero(buffer,256);
  n = read(acc,buffer,255 );
  printf("Message Received: %s\n",buffer);
  //write response
  n = write(acc,buffer,18);
}

int main( int argc, char *argv[] ) {
   int sockfd, newsockfd, portno, clilen;
   pid_t pid;
   struct sockaddr_in serv_addr, cli_addr;
   int  n,acc;

   //Step 2- Creating a TCP Socket
   sockfd = socket(AF_INET, SOCK_STREAM, 0);

   //Step 3- Filling Socket Address Structure with server information
   bzero((char *) &serv_addr, sizeof(serv_addr));
   serv_addr.sin_family = AF_INET;
   serv_addr.sin_addr.s_addr = INADDR_ANY;

   //Step 4- Specifying Port where services will be defined by Client
   portno = 5001;
   serv_addr.sin_port = htons(portno);

   //Step 5- Binding the Address and Port
   if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
      perror("ERROR in binding");
      exit(1);
   }
   else{
     printf("Binded\n");
   }

   //Step 6- Executing listen() system call (Willing to Receive Connection)

   if(listen(sockfd,5)==-1){
     printf("Error occured while Listening\n" );
     exit(1);
   }
   else{
     printf("Listening...\n" );
   }

   //Step 7- Accept completed Connection by accept() system call
   /*
   clilen = sizeof(cli_addr);
   acc = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
   if(acc > 0)
      printf("Accepted\n");
   else{
      printf("Not accepted\n");
      exit(1);
    }
    */
    //Step 8- Creating new child process using Fork() to handle client request.
    for(; ;){
      clilen = sizeof(cli_addr);
      acc = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
      if(acc > 0){
         printf("Accepted\n");
         printf("Connected to Client...");
       }
      else{
         printf("Not accepted\n");
         exit(1);
       }

      //Creating child process
      if((pid=fork()) == 0){
        printf("Child process created.");
        close(sockfd);
        echo_message(acc);
        close(acc);
        exit(0);
      }
      close(acc);
    }
    return 0;
}
