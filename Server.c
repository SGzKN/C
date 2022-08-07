#include<stdio.h>
#include<stdlib.h>       
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

int main(int argc, char *argv[] ){  //enter port no. as command line arg
    int socket1, socket2, portno, n;
    char message[1000]; //stores message

    // Confirming if port no. is entered
    if (argc < 2){
        printf("Provide Port no. in command line argument.");
        exit(1);
    }

    struct sockaddr_in serv_addr;//server info
    struct sockaddr_in cli_addr; //client info
    socklen_t clilen; //socklen_t  is data type to store address in particular format.
    portno = atoi(argv[1]); //atoi inbuilt function to convert into network byte order

    socket1 = socket(AF_INET,SOCK_STREAM, 0); //creates the socket

    //Confirming if Socket is created
    if(socket1<0){
        printf("Socket is not Created.");
    }

    

    //bulinding structure
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno); // host to network short 

    //Bind the socket to address and port no.
    if (bind(socket1, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0){
        printf("Cannot Bind");
        exit(1);
    }

    listen(socket1,5);
    clilen = sizeof(cli_addr);
    socket2 = accept(socket1,(struct sockaddr *) &cli_addr, &clilen);
    if(socket2 < 0){
        printf("Cannot accept the client");
    }

    while(1){
        bzero(message, 1000);
        n = read(socket2,message,1000);
        if(n<0){
            printf("Cannot read ");
        }
        printf("Client: %s \n",message);
        bzero(message,1000);
        fgets(message,1000, stdin);

        n= write(socket2, message, strlen(message));
        if(n<0){
            printf("Error writing");
        }
        int i = strncmp("Bye", message,3);
        if(i ==0){
            break;
        }
    }
    close(socket1);
    close(socket2);
    return 0;
}
