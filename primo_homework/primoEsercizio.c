#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>


int main(int argc , char *argv[]){
		int x = 100;
		printf("%d \n",x);
		int rc = fork();
		if(rc < 0){
			fprintf(stderr, "fork failed\n");
			exit(1);
		} else if (rc == 0){
			printf("child %d e il mio pid è: %d \n",x,(int) getpid());

		} else {
			printf("parent %d e il mio pid è %d \n",x,(int) getpid());

		}
		return 0;

}