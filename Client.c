/*
argv[0] = file name
argv[1] = ip addrress
argv[2] = portno
*/


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
 #include <arpa/inet.h>

int main(int argc, char *argv[] ){  //input port no as commandline arg . 0th arg stores program name  
                                      // we are sending 2 values . so, argc = 2
    int socket1, portno, n;
    char message[1000];
    struct sockaddr_in serv_addr;

    if (argc < 3){ //we add ip address .so argc=3
        printf("provide inputs");
        exit(1);
    }

    portno = atoi(argv[2]);
    socket1 = socket(AF_INET,SOCK_STREAM, 0);
    if(socket1<0){
        printf("ERROR! Opening socket");
        exit(1);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(portno); 
    serv_addr.sin_addr.s_addr= inet_addr(argv[1]);

    if(connect(socket1, (struct sockaddr *) &serv_addr, sizeof(serv_addr))<0){
        printf("Connection Failed");
    }

    while(1){
        bzero(message, 1000);
        fgets(message, 1000, stdin);
        n = write(socket1, message, strlen(message));
        if(n<0){
            printf("Writing error");
        }
        bzero(message, 1000);
        n = read(socket1,message,1000);
        if(n<0){
            printf("Cannot read ");
        }
        printf("Server: %s",message);

        int i = strncmp("Bye", message,3);
        if(i ==0){
            break;
        }
    }
    close(socket1);

    return 0;
}
