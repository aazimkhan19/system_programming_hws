#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
    
		
int main(){
	char s[100];
	
	int proc[50];

	int index = 0;

	int isBackground = 0;
	
	while(1) {
	    	printf("$ Enter your command: ");		
		fgets(s,100,stdin);
		

		if(strcmp(s,"exit\n")==0){
			break;		
		}
		else if(strcmp(s,"showjobs\n")==0){
			int indexTemp = 0;
			int new = index;
			int status = 0;
			while(indexTemp<index){
				if(waitpid(proc[indexTemp], &status, WNOHANG)){
					int shift = indexTemp;			    		
					while(shift<index-1){
						proc[shift] = proc[shift+1];
						shift++;
					}
					new--;
			 	}
				indexTemp++;
	     		}

			index = new;
			indexTemp = 0;

			while(indexTemp<index){
				printf("%d ",proc[indexTemp]);
		 		indexTemp++;
	     		}
			
			printf("\n");
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
					proc[index] = x;
					index++;
					continue;			
				}
				else{
					waitpid(x,0,0);	
				}
			}
	     	}
	}
}
