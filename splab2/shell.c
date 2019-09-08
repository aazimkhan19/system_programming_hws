#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
	char s[100];
	int isBackground = 0;
	while(1){
		printf("$ Enter your command: ");		
		fgets(s,100,stdin);
		if(strcmp(s,"exit\n")==0){
			break;		
		}
		else{
			s[strlen(s)-1] = '\0';
			char* a[10];
			
			char *c = s;
			
			for(int i = 0; i < 10; i++) {
				a[i] = strsep(&c, " ");  
				if(a[i] == NULL) 
					break;
				if(strcmp(a[i],"&")==0){
					isBackground = 1;
					a[i] = NULL;					
				}
			}

			int x = fork();
			
			if(x==0){
				execvp(a[0],a);
				_exit(0);			
			}
			else{
				if(isBackground){
					isBackground = 0;
					continue;			
				}		
				else{
					waitpid(x,0,0);				
				}	
			}
		}
	}
}
