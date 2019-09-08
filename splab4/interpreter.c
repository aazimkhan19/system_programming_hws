/*
All rights reserved
Author Azimkhan Almas
MIT License
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

void console(char* s){
	char *token = strtok(s, ")(");
	if(strcmp(token,"print")==0){
		token = strtok(NULL, "\"");
		printf("%s\n",token);
	}
	else if(strcmp(token,"Zen of Potato")==0){
		printf("No syntactic sugar in Potato!\nOnly print!\n");
	}
	else{
		printf("Name error: no such function\n");
	}	
}

int main(){
	char s[100];
	int isBackground = 0;
	while(1){
		printf("$ ");		
		fgets(s,100,stdin);
		if(strcmp(s,"\n")==0)
			continue;
		s[strlen(s)-1] = '\0';
		if(strcmp(s,"exit")==0){
			break;		
		}
		else if(strcmp(s,"potato")==0){
			char sin[100];			
			while(1){
				printf(">>> ");		
				fgets(sin,100,stdin);
				if(strcmp(sin,"exit()\n")==0){
					break;		
				}
				sin[strlen(sin)-1] = '\0';
				console(sin);
			}
		}
		else{
			char *token = strtok(s, " ");
			if(strcmp(token,"echo")==0){
				token = strtok(NULL, "'");
				char *a = token;
				token = strtok(NULL, " ");
				char *mode = token;
				token = strtok(NULL, " ");
				char *b = token;
				FILE *potfile;
				if(strcmp(mode,">>")==0) {
					potfile = fopen(b,"a");
					fputs(a,potfile);
					fputs("\n",potfile);
					fclose(potfile);
				} 
				else {
					potfile = fopen(b,"w");
					fputs(a,potfile);
					fputs("\n",potfile);
					fclose(potfile);	
				}
				
				
			}
			else if(strcmp(token,"potato")==0){  
				token = strtok(NULL, "");
				
				char s[255];

				FILE *potfile = fopen(token,"r");
				
				while((fgets(s,255,potfile)) != NULL){
            		s[strlen(s)-1] = '\0';
					console(s);
				}
				fclose(potfile);
			}
			else if(s[0]='.' && s[1]=='/'){ 
				
 				char *token = strtok(s, "/");
				token = strtok(NULL, "/");

				char sin[255];

				FILE *potfile = fopen(token,"r");
				fgets(sin,255,potfile);
				
				int shebang = 0;
				sin[strlen(sin)-1] = '\0';

				if(strcmp(sin,"#!/bin/potato")==0){
					shebang=1;
				}

				if(shebang){
					while((fgets(sin,255,potfile)) != NULL){
                		sin[strlen(sin)-1] = '\0';
						console(sin);
					}
					fclose(potfile);
				}
				else{
					printf("error\n");
					break;
				}
			}
			
		}
	}
}


/*
(r) Almas Azimkhan

*/
