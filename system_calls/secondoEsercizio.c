#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>


int main(int argc , char *argv[]){
		
		int file = open("./file.output",O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
		int rc = fork();
		if(rc < 0){
			fprintf(stderr, "fork failed\n");
			exit(1);
		} else if (rc == 0){

			printf("child %d e il mio pid è: %d \n",file,(int) getpid());
			
			write(file,"hello\n",5);
			close(file);

		} else {
			printf("parent %d e il mio pid è %d \n",file,(int) getpid());
			write(file,"hey\n",9);
			close(file);				

		}
		return 0;

}
