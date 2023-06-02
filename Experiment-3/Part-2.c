#include <stdio.h>
#include <string.h>

#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>  // for open() function

#define MAX_SIZE 1024

void getS(char* str){
    fgets(str, MAX_SIZE, stdin);
    str[strlen(str)-1] = 0;
}

int main(){
    int fd;
    const char* myFifo = "myfifo";
    char message[MAX_SIZE] = {0}, buffer[MAX_SIZE] = {0};

    // 0666 = permission bytes
    if(mkfifo("./myfifo", 0666) == -1){
        if(errno == EEXIST)
            printf("FIFO already exists\n");
        else{
            perror("There was some unexpected error\n");
            return errno;
        }
    }
    while(1){
        memset(buffer, 0, MAX_SIZE);
        fd = open(myFifo, O_RDONLY, 0666);
        if(fd == -1){
            perror("Bad file descriptor");
            return errno;
        }
        if(read(fd,buffer,MAX_SIZE) == -1){
            perror("Error reading data from FIFO");
            return errno;
        }
        close(fd);
        printf("\nReceived data from 1st program: %s\n",buffer);
        if(!strcmp(buffer,"exit")) break;

        memset(message, 0, MAX_SIZE);
        fd = open(myFifo, O_WRONLY, 0666);
        if(fd == -1){
            perror("Bad file descriptor");
            return errno;
        }
        printf("Enter data for 1st program: ");
        getS(message);
        if(write(fd,message,MAX_SIZE) == -1){
            perror("Error writing data to FIFO");
            return errno;
        }
        close(fd);
        if(!strcmp(message,"exit")) break;
    }
    return 0;
}