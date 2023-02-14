//XRISTOS PAPASTAMOS csd4569@csd.uoc.gr

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>

#define DEBUG 0
#define EXIT -1
#define SUCCESS 1

int execute(char *args[]);
void printpipe(char *pipecmd[5][50]);
void printargs(char *args[50]);

int main(int argc, char const *argv[]){

	while(1){

		char *command;
		char inputstr[200]={0};
		char *inputptr=inputstr;

		char workding_dir[50];
		getcwd(workding_dir,sizeof(workding_dir));

		//print the terminal header
		printf("\033[0;35m");
		printf("%s@cs345sh",getlogin());

		printf("\033[0m");
		printf(":");

		printf("\e[0;31m");
		printf("%s",workding_dir);

		printf("\033[0m");
		printf("$");

		//read the input
		fgets(inputstr,200, stdin);

		int inputcnt=0;
		while(inputstr[inputcnt]!='\n' && inputcnt<199){
			inputcnt++;
		}

		inputstr[inputcnt]='\0';
		while ((command = strtok_r(inputptr, ";", &inputptr))){ 						//Split the input string in the individual commands, separated by ';'
			int redirection=0,pipecnt=0;												//redirection and pipecnt flags

			int redfd,saved_stdout,saved_stdin;											//the redirection fd and the two saved for the stdio

			char *pipecmd[20][50]={0};													//the array used to store up to 20 pipe commands with 49 arguements each
			char *commandptr=command;
			char *args[50]={0};															//the array used to store the single command
			char *op;
			char *arg;
			char *redfile;

			//Save the stdio fds
			saved_stdin=dup(0);
			saved_stdout=dup(1);

			//parse the command
			int argcnt=0;
			int pipeargcnt=0;
			while ((arg = strtok_r(commandptr, " ", &commandptr))){						//split the command on ' '
				if(redirection!=0){														//if redirection was detected, the next part is the file name
					redfile=arg;
					break;
				}

				//detect redirections and pipes, and flag them
				if(!strcmp(arg,"<")){
					redirection=1;
					continue;
				}else if(!strcmp(arg,">")){
					redirection=2;
					continue;
				}else if(!strcmp(arg,">>")){
					redirection=3;
					continue;
				}else if(!strcmp(arg, "|")){
					pipecnt++;
					pipeargcnt=0;
				}

				if(pipecnt){															//if a pipe was detected store the commands in pipecmd[]
					if(!strcmp(arg,"|")){continue;}
					pipecmd[pipecnt][pipeargcnt]=arg;
					pipeargcnt++;
				}else{																	//if no redirection or pipe is detected store the command in args[]
					pipecmd[pipecnt][argcnt]=arg;
					args[argcnt]=arg;
					argcnt++;
				}
			}

			if(DEBUG){
				if(pipecnt){printpipe(pipecmd);}else{printargs(args);}
			}

			if(redirection){															//if a redirection was detected
				if(redirection==1){														//and it is a input redirection
					if(DEBUG){fprintf(stderr,"duping redfd to stdin\n");}
					redfd = open(redfile,O_CREAT | O_RDONLY,0644);
	 				dup2(redfd, 0); 													//duplicate the redirection fd on the stdin
	 			}else if(redirection==2){												//if it is a write redirection
					if(DEBUG){fprintf(stderr,"duping redfd to stdout\n");}
					redfd = open(redfile,O_CREAT | O_WRONLY | O_TRUNC,0644);
	 				dup2(redfd, 1);														//duplicate the redirection fd on the stdout
				}else if(redirection==3){												//if it is a append redirection
					if(DEBUG){fprintf(stderr,"duping redfd to stdout (append)\n");}
					redfd = open(redfile,O_CREAT | O_WRONLY | O_APPEND,0644);
	 				dup2(redfd, 1);														//duplicate the redirection fd on the stdout as append
				}
			}

			//if a pipe was detected
			if(pipecnt){
				int pipefd[pipecnt][2];													//create an array for the pipe fds
				int pipeindex=0;
				for(pipeindex=0;pipeindex<=pipecnt;pipeindex++){						//and execute for each command of the pipe
					if(DEBUG){fprintf(stderr,"\nEXECUTING PIPE %d\n",pipeindex);}
					pipe(pipefd[pipeindex]);

					if(pipeindex!=0){													//if it is the first command of the pipe,dont overwrite stdin
						if(DEBUG){fprintf(stderr,"duping pipefd[%d][0] to stdin\n",pipeindex-1);}
						dup2(pipefd[pipeindex-1][0], 0);								//else dup the previus piepe's read end to stdin

						close(pipefd[pipeindex-1][0]);									//and close all previus pipe's ends
						close(pipefd[pipeindex-1][1]);
					}

					if(pipeindex!=pipecnt){												//if it isn't the last command of the pipe
						if(DEBUG){fprintf(stderr,"duping pipefd[%d][1] to stdout\n",pipeindex);}
						dup2(pipefd[pipeindex][1], 1);									//dup the current pipes write end to stdout
					}else{ 
						if(redirection==2 || redirection==3){							//if it is the last one and a write redirection was detected
							if(DEBUG){fprintf(stderr,"duping redfd to stdout\n");}
							dup2(redfd, 1);												//dup the redirection fd to stdout
						}else{															//else if there is no redirection detected
							if(DEBUG){fprintf(stderr,"duping saved_stdout to stdout\n");}
							dup2(saved_stdout, 1);										//dup saved stdout to stdout
						}
					}

					execute(pipecmd[pipeindex]);										//and finally execute the command
				}
			}

			//if there is no pipe detected, just execute the requested command
			if(!pipecnt && execute(args)==EXIT){return 1;}

			//close the remaining open fds and restore the stdin and stdout
			if(redirection){close(redfd);}
			dup2(saved_stdin, 0);
			dup2(saved_stdout, 1);
			close(saved_stdout);
			close(saved_stdin);
		}
	}

	return 0;
}

//a funtcion used to execute a given command
int execute(char *args[]){
	if(DEBUG){fprintf(stderr, "Executing %s\n\n",args[0]);}
	if(!strcmp(args[0],"exit")){														//if the command is exit, return an exit code
		return EXIT;
	}else if(!strcmp(args[0],"cd")){													//if the command is cd, use chdir to change the current directory
		chdir(args[1]);
		return SUCCESS;
	}else{																				//else fork the process and change the child to execute the requested command
		int *waitstatus;
		if(fork() == 0){
			execvp(args[0],args);
			return 0;
		}else{
			wait(waitstatus);
			return SUCCESS;
		}
	} 
}

//a debug function used to print the array where the pipe commands are stored
void printpipe(char *pipecmd[5][50]){
	int i=0,j=0;
	fprintf(stderr,"pipecnt ARRAY:\n");
	for(i=0;i<5;i++){
		if(pipecmd[i][0]){
			fprintf(stderr,"%d->",i);
			for(j=0;j<50;j++){
				if(pipecmd[i][j]){fprintf(stderr,"%d:[%s]",j,pipecmd[i][j]);}
			}
			fprintf(stderr,"\n");
		}
	}
	fprintf(stderr,"END OF pipecnt ARRAY\n\n");
}

//a debug function used to print the array where the command is stored
void printargs(char *args[50]){
	int i=0;
	fprintf(stderr,"ARGS ARRAY\n");
	for(i=0;i<50;i++){
		if(args[i]){fprintf(stderr,"%d:[%s]",i,args[i]);}
	}
	fprintf(stderr,"\nEND OF ARGS ARRAY\n\n");
}
