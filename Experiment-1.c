#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#define MAX_SIZE 1024

void getS(char* str){
    fgets(str, MAX_SIZE, stdin);
    str[strlen(str)-1] = 0;
}

int main(int argc, char *argv[]){
    int fd[2];

    if(pipe(fd) == -1){
        perror("Error creating pipe\n");
        return errno;
    }
    int pid = fork();
    
    // main thread
    if(pid > 0){
        char message[MAX_SIZE] = {0};
        close(fd[0]);
        while(1){
            memset(message,0,MAX_SIZE);
            printf("Enter message for child: ");
            getS(message);
            if(write(fd[1], message, MAX_SIZE) == -1){
                perror("Error writing data to PIPE\n");
                return errno;
            }
            if(!strcmp(message,"exit")) break;
            sleep(1);
        }
    }
    
    // child process
    else{
        char buffer[MAX_SIZE] = {0};
        close(fd[1]);
        while(1){
            memset(buffer,0,MAX_SIZE);
            if(read(fd[0], buffer, MAX_SIZE) == -1){
                perror("Error reading data from PIPE\n");
                return errno;
            }
            else printf("Message received from parent: %s\n",buffer);
            if(!strcmp(buffer,"exit")) break;
        }
    }
    return 0;
}

/*Output
Enter message for child: hii
Message received from parent: hii
Enter message for child: hello
Message received from parent: hello
Enter message for child: exit
Message received from parent: exit
*/