#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc , char *argv[]){
		int rc = fork();
		if(rc < 0){
			fprintf(stderr, "fork failed\n");
			exit(1);
		} else if (rc == 0){
			
			printf("child dice Hello e il mio pid è: %d \n",(int) getpid());
			close(STDOUT_FILENO);
		} else {
			printf("parent dice goodbye e il mio pid è %d \n",(int) getpid());

		}
		return 0;

}