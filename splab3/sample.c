#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <ctype.h>

int main() {
	int fd[2], fd2[2], fd3[2], fd4[2], fd5[2], fd6[2], fd7[2];//                                       

	pipe(fd);
	pid_t pid1 = fork();                
		       
	if (!pid1) {
		dup2(fd[1], 1);
		
		close(fd[0]);
		close(fd[1]);
		execlp("grep","grep","-o", "--color=auto", "../Oct/....", "log.txt", NULL);
		exit(EXIT_FAILURE);
	} else if (pid1 == -1) {                                   
		fprintf(stderr, "Can't fork, exiting...\n");           
		exit(EXIT_FAILURE);
	}
	
                                                          
	pipe(fd2);
	pid_t pid2 = fork();                                       
	if (!pid2) {
		dup2(fd[0], 0);
		close(fd[0]);
		close(fd[1]);

		dup2(fd2[1], 1);
		close(fd2[0]);
		close(fd2[1]); 
		
		execlp("sed","sed", "s/\\(..\\)\\/Oct\\/\\(....\\)/\\2-10-\\1/", NULL);
		exit(EXIT_FAILURE);                            
	} else if (pid2 == -1) {             
		fprintf(stderr, "Can't fork, exiting...\n");
		exit(EXIT_FAILURE);
	}
	close(fd[0]);
	close(fd[1]);


	pipe(fd3);
	pid_t pid3 = fork();                                       
	if (!pid3) {
		dup2(fd2[0], 0);
		close(fd2[0]);
		close(fd2[1]);

		dup2(fd3[1], 1);
		close(fd3[0]);
		close(fd3[1]); 
		
		execlp("sort", "sort", NULL);
		exit(EXIT_FAILURE);                            
	} else if (pid3 == -1) {             
		fprintf(stderr, "Can't fork, exiting...\n");
		exit(EXIT_FAILURE);
	}
	close(fd2[0]);
	close(fd2[1]);

	
	pipe(fd4);
	pid_t pid4 = fork();                                       
	if (!pid4) {
		dup2(fd3[0], 0);
		close(fd3[0]);
		close(fd3[1]);

		dup2(fd4[1], 1);
		close(fd4[0]);
		close(fd4[1]);

		execlp("uniq", "uniq","-c", NULL);
		exit(EXIT_FAILURE);                            
	} else if (pid4 == -1) {             
		fprintf(stderr, "Can't fork, exiting...\n");
		exit(EXIT_FAILURE);
	}
	close(fd3[0]);
	close(fd3[1]);


	pipe(fd5);
	pid_t pid5 = fork();                                       
	if (!pid5) {
		dup2(fd4[0], 0);
		close(fd4[0]);
		close(fd4[1]);

		dup2(fd5[1], 1);
		close(fd5[0]);
		close(fd5[1]);

		execlp("sort", "sort","-r", NULL);
		exit(EXIT_FAILURE);                            
	} else if (pid5 == -1) {             
		fprintf(stderr, "Can't fork, exiting...\n");
		exit(EXIT_FAILURE);
	}
	close(fd4[0]);
	close(fd4[1]);
	

	pipe(fd6);
	pid_t pid6 = fork();
	if (!pid6) {
		dup2(fd5[0], 0);
		close(fd5[0]);
		close(fd5[1]);

		dup2(fd6[1], 1);
		close(fd6[0]);
		close(fd6[1]);

		execlp("head", "head", NULL);
		exit(EXIT_FAILURE);                            
	} else if (pid6 == -1) {             
		fprintf(stderr, "Can't fork, exiting...\n");
		exit(EXIT_FAILURE);
	} 
	close(fd5[0]);
	close(fd5[1]);

	
	/*pipe(fd7);
	pid_t pid7 = fork();
	if (!pid7) {
		dup2(fd6[0], 0);
		close(fd6[0]);
		close(fd6[1]);

		dup2(fd7[1], 1);
		close(fd7[0]);
		close(fd7[1]);

		execlp("cut", "cut", "-d ", "-f5", NULL);
		exit(EXIT_FAILURE);                            
	} else if (pid7 == -1) {             
		fprintf(stderr, "Can't fork, exiting...\n");
		exit(EXIT_FAILURE);
	}
	//close(fd6[0]); 
	close(fd6[1]);
	close(fd7[1]);

	FILE* Cin = fdopen(fd7[0],"r");
	int x,sum=0;
	while(fscanf(Cin,"%d",&x)>0){ 
		sum+=x;
	}
	close(fd7[0]);
*/
	
	pid_t pid8 = fork();
	if (!pid8) {
		dup2(fd6[0], 0);
		close(fd6[0]);
		close(fd6[1]);

		execlp("awk", "awk", "{print NR-0\". \" $2\" - \"$1\" - \"$1*100/3417\" %\";}", NULL);
		exit(EXIT_FAILURE);                            
	} else if (pid8 == -1) {             
		fprintf(stderr, "Can't fork, exiting...\n");
		exit(EXIT_FAILURE);
	}
	close(fd6[0]);
	close(fd6[1]);
	
	waitpid(pid1, NULL, 0);                                
	waitpid(pid2, NULL, 0);
	waitpid(pid3, NULL, 0);
	waitpid(pid4, NULL, 0);
	waitpid(pid5, NULL, 0);
	waitpid(pid6, NULL, 0);
	//waitpid(pid7, NULL, 0);
	waitpid(pid8, NULL, 0);
}
