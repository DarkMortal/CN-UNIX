// PS: WAP to implement bidirectional IPC between parent and child process by using PIPE

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define MAX_SIZE 1024

void getS(char* str){
    fgets(str, MAX_SIZE, stdin);
    str[strlen(str)-1] = 0;
}

int main(){
    // declaring the file descriptors 
    int fd1[2], fd2[2];
    char message[MAX_SIZE], buffer[MAX_SIZE];
    
    if(pipe(fd1) == -1){
        perror("Pipe-1 creation failed\n");
        return errno;
    }
    if(pipe(fd2) == -1){
        perror("Pipe-2 creation failed\n");
        return errno;
    }
    int pid = fork();
    if(pid == 0){
        close(fd1[1]);
        close(fd2[0]);
        while(1){
            memset(buffer, 0, sizeof(buffer));
            if(read(fd1[0], buffer, MAX_SIZE) == -1){
                perror("Error reading data from PIPE\n");
                return errno;
            }

            if(strlen(buffer) != 0)
                printf("\nReceived data from parent : %s\n",buffer);
            else
                printf("\nNo data received from parent\n");
            if(!strcmp(buffer,"exit")) break;

            fflush(stdin);
            printf("Write data for parent : ");

            getS(message);
            if(write(fd2[1], message, MAX_SIZE) == -1){
                perror("Error writing data to PIPE\n");
                return errno;
            }
            if(!strcmp(message,"exit")) break;
        }
    }else{
        close(fd1[0]);
        close(fd2[1]);
        while(1){
            memset(message, 0, sizeof(message));
            fflush(stdin);
            printf("Write data for child : ");

            getS(message);
            if(write(fd1[1], message, MAX_SIZE) == -1){
                perror("Error writing data to PIPE\n");
                return errno;
            }
            if(!strcmp(message,"exit")) break;

            memset(buffer, 0, sizeof(buffer));
            if(read(fd2[0], buffer, MAX_SIZE) == -1){
                perror("Error reading data from PIPE\n");
                return errno;
            }

            if(strlen(buffer) != 0)
                printf("\nReceived data from child : %s\n",buffer);
            else
                printf("\nNo data received from child\n");
            if(!strcmp(buffer,"exit")) break;            
        }
    }
    return 0;
}

/*Output
Write data for child : hii

Received data from parent : hii
Write data for parent : hello

Received data from child : hello
Write data for child : exit

Received data from parent : exit
*/