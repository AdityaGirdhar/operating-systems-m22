#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

void* systemCall(void *arg) {
	char *cmd = (char *) arg;
	system(cmd);
	return NULL;
}


int main() {
	pthread_t thread;
	
	printf("\e[1;1H\e[2J");
	char workDir[1000];
	char buffer[1000];
	printf("\033[1;37m"); // bold
	printf("Welcome to the ");
	printf("Girdhar Shell (gsh)");
	printf(".\nType \"help\" for a list of available commands.\n\n");
	while (1) {
		// Input Sequence -------
		printf("\033[1;32m"); // green
		printf("gsh >");
		printf("\033[1;34m"); // blue
		printf(" %s", getcwd(workDir, sizeof(workDir)));
		printf("\033[0m"); // default
		printf("$ ");
		fgets(buffer, 1000, stdin);
		
		// exit -----------------
		if (!strcmp(buffer, "exit\n")) {
			return 0;
		}
		
		if (buffer[strlen(buffer)-2] == ' ') {
			buffer[strlen(buffer)-2] = '\n';
			buffer[strlen(buffer)-1] = '\0';
		}
			
		// ---- INTERNAL COMMANDS ----
		
		char *token = strtok(buffer, " ");
		
		if (!strcmp(token, "echo")) {
			token = strtok(NULL, " ");
			int n = 0;
			if (!strcmp(token, "-n")) {
				n = 1;
				token = strtok(NULL, " ");
			}
			if (!strcmp(token, "--help\n")) {
				printf("\033[1;37m"); // bold
				printf("echo [arg ...]:\n");
				printf("\033[0m"); // default
				printf("  Displays arguments followed by newline on the standard output.\n\n");
				continue;
			}
			if (token[0] == '"' && token[strlen(token)-2] == '"') {
				token[0] = ' ';
				token[strlen(token)-2] = '\0';
				for (int i = 1; i < strlen(token); i++) {
					printf("%c", token[i]);
				}
			}
			else {
				token[strlen(token)-1] = '\0';
				printf("%s", token);
			}
			if (!n) {
				printf("\n");
			}
			continue;
		}
		
		if (!strcmp(token, "echo\n")) {
			printf("echo: Too few arguments");
		}
		
		else if (!strcmp(token, "cd")) {
			token = strtok(NULL, " ");
			if (!strcmp(token, "-L")) {
				token = strtok(NULL, " ");
			}
			if (!strcmp(token, "-P")) {
				token = strtok(NULL, " ");
			}
			token[strlen(token)-1] = '\0';
			int cdRet = chdir(token);
			if (cdRet != 0) {
				printf("cd: %s: No such file or directory\n", token);
			}
			continue;
		}
		else if (!strcmp(token, "cd\n")) {
			printf("cd: Too few arguments\n");
			continue;
		}
		
		char *c = getcwd(workDir, sizeof(workDir));
		
		if (!strcmp(buffer, "pwd\n")) {
			if (c == NULL) {
				c = "pwd: unsuccessful, kindly check permissions\n";
			}
			printf("%s\n", c);
			continue;
		}
		
		else if (!strcmp(buffer, "pwd")) {
			int flag = 0;
			token = strtok(NULL, " ");
			if (!strcmp(token, "-L\n") || !strcmp(token, "-L")) {
				printf("%s\n", c);
				flag = 1;
			}
			if (!strcmp(token, "-P\n") || !strcmp(token, "-P")) {
				printf("%s\n", c);
				flag = 1;
			}
			if (!flag) {
				printf("pwd: Invalid option %s", token);
			}
			continue;
		}

		else if (!strcmp(token, "help") || !strcmp(buffer, "help\n")) {
			int found = 0;
			if (!strcmp(buffer, "help\n")) {
			printf("Girdhar Shell, version 0.5.1; release (x86_64-linux-gnu)\n");
			printf("Designed for CSE231 (Operating Systems), Winter 2022, IIIT-Delhi\n\n");
			printf("----Internal Commands----\n\n");
			}
			
			if (strcmp(buffer, "help\n")) {
				token = strtok(NULL, " ");
			}
			
			if (!strcmp(token, "echo\n") || !strcmp(buffer, "help\n")) {
			printf("\033[1;37m"); // bold
			printf("echo [arg ...]:\n");
			printf("\033[0m"); // default
			printf("  Displays arguments followed by newline on the standard output.\n\n");
			found = 1;
			}
			
			if (!strcmp(token, "cd\n") || !strcmp(buffer, "help\n")) {
			printf("\033[1;37m"); // bold
			printf("cd [dir]:\n");
			printf("\033[0m"); // default
			printf("  Changes current directory to DIR.\n\n");
			found = 1;
			}
			
			if (!strcmp(token, "pwd\n") || !strcmp(buffer, "help\n")) {
			printf("\033[1;37m"); // bold
			printf("pwd:\n");
			printf("\033[0m"); // default
			printf("  Print the name of the current working directory.\n\n");
			found = 1;
			}
			
			if (!strcmp(token, "clear\n") || !strcmp(buffer, "help\n")) {
			printf("\033[1;37m"); // bold
			printf("clear:\n");
			printf("\033[0m"); // default
			printf("  Clear the terminal screen.\n\n");
			found = 1;
			}
			
			if (!strcmp(token, "exit\n") || !strcmp(buffer, "help\n")) {
			printf("\033[1;37m"); // bold
			printf("exit:\n");
			printf("\033[0m"); // default
			printf("  Terminates gsh instance.\n\n");
			found = 1;
			}
			
			if (!found) {
				printf("help: no help topics match %s", token);
			}
		}
		
		else if (!strcmp(token, "clear\n")) {
			printf("\e[1;1H\e[2J");
			printf("\033[1;37m"); // bold
			printf("Welcome to the ");
			printf("Girdhar Shell (gsh)");
			printf(".\nType \"help\" for a list of available commands.\n\n");
		}	
		
		// ---- EXTERNAL COMMANDS ----
		
		else if (!strcmp(token, "ls\n")) { // ls without path or args
			int rc = fork();
			if (!rc) {
				getcwd(workDir, sizeof(workDir));
				execl("/gsh/ls", "/gsh/ls", workDir, NULL);
				return 0;
			} else {
				wait(0);
				continue;
			}
		}
		
		else if (!strcmp(token, "ls&t\n")) {
			char cmd[150] = "/gsh/ls ";
			getcwd(workDir, sizeof(workDir));
			strcat(cmd, workDir);
			pthread_create(&thread, NULL, systemCall, cmd);
			pthread_join(thread, NULL);
			continue;
		}
		
		else if (!strcmp(token, "ls")) { // ls with path or args
			int rc = fork();
			if (!rc) {
				token = strtok(NULL, " ");
				if (!strcmp(token, "-a\n")) {
					getcwd(workDir, sizeof(workDir));
					execl("/gsh/ls", "/gsh/ls", workDir, "-a", NULL);
					return 0;
				}
				if (!strcmp(token, "-a")) {
					token = strtok(NULL, " ");
					if (token[strlen(token)-1] == '\n') {
						token[strlen(token)-1] = '\0';
					}
					execl("/gsh/ls", "/gsh/ls", token, "-a", NULL);
				}
				if (!strcmp(token, "-A\n")) {
					getcwd(workDir, sizeof(workDir));
					execl("/gsh/ls", "/gsh/ls", workDir, "-A", NULL);
					return 0;
				}
				if (!strcmp(token, "-A")) {
					token = strtok(NULL, " ");
					if (token[strlen(token)-1] == '\n') {
						token[strlen(token)-1] = '\0';
					}
					execl("/gsh/ls", "/gsh/ls", token, "-A", NULL);
				}
				if (token[strlen(token)-1] == '\n') {
					token[strlen(token)-1] = '\0';
				}
				execl("/gsh/ls", "/gsh/ls", token, NULL);
				return 0;
			} else {
				wait(0);
				continue;
			}
		}
		
		else if (!strcmp(token, "ls&t")) {
				token = strtok(NULL, " ");
				char cmd[150] = "/gsh/ls ";
				if (!strcmp(token, "-a\n")) {
					getcwd(workDir, sizeof(workDir));
					strcat(cmd, workDir);
					strcat(cmd, " -a");
					pthread_create(&thread, NULL, systemCall, cmd);
					pthread_join(thread, NULL);
					continue;
				}
				if (!strcmp(token, "-a")) {
					token = strtok(NULL, " ");
					if (token[strlen(token)-1] == '\n') {
						token[strlen(token)-1] = '\0';
					}
					strcat(cmd, token);
					strcat(cmd, " -a");
					pthread_create(&thread, NULL, systemCall, cmd);
					pthread_join(thread, NULL);
					continue;
				}
				if (!strcmp(token, "-A\n")) {
					getcwd(workDir, sizeof(workDir));
					strcat(cmd, workDir);
					strcat(cmd, " -A");
					pthread_create(&thread, NULL, systemCall, cmd);
					pthread_join(thread, NULL);
					continue;
				}
				if (!strcmp(token, "-A")) {
					token = strtok(NULL, " ");
					if (token[strlen(token)-1] == '\n') {
						token[strlen(token)-1] = '\0';
					}
					strcat(cmd, token);
					strcat(cmd, " -A");
					pthread_create(&thread, NULL, systemCall, cmd);
					pthread_join(thread, NULL);
					continue;
				}
				if (token[strlen(token)-1] == '\n') {
					token[strlen(token)-1] = '\0';
				}
				strcat(cmd, token);
				pthread_create(&thread, NULL, systemCall, cmd);
				pthread_join(thread, NULL);
				continue;
		}
		
		else if (!strcmp(token, "cat")) {
			int rc = fork();
			if (!rc) {
				token = strtok(NULL, " ");
				if (!strcmp(token, "-E")) {
					token = strtok(NULL, " ");
					if (token[strlen(token)-1] == '\n') {
						token[strlen(token)-1] = '\0';
					}
					execl("/gsh/cat", "/gsh/cat", token, "-E", NULL);
				}
				if (!strcmp(token, "-n")) {
					token = strtok(NULL, " ");
					if (token[strlen(token)-1] == '\n') {
						token[strlen(token)-1] = '\0';
					}
					execl("/gsh/cat", "/gsh/cat", token, "-n", NULL);
				}
				if (token[strlen(token)-1] == '\n') {
					token[strlen(token)-1] = '\0';
				}
				execl("/gsh/cat", "/gsh/cat", token, NULL);
				return 0;
			} else {
				wait(0);
				continue;
			}
		}
		
		else if (!strcmp(token, "cat&t")) {
				char cmd[150] = "/gsh/cat ";
				token = strtok(NULL, " ");
				if (!strcmp(token, "-E")) {
					token = strtok(NULL, " ");
					if (token[strlen(token)-1] == '\n') {
						token[strlen(token)-1] = '\0';
					}
					strcat(cmd, token);
					strcat(cmd, " -E");
					pthread_create(&thread, NULL, systemCall, cmd);
					pthread_join(thread, NULL);
					continue;
				}
				if (!strcmp(token, "-n")) {
					token = strtok(NULL, " ");
					if (token[strlen(token)-1] == '\n') {
						token[strlen(token)-1] = '\0';
					}
					strcat(cmd, token);
					strcat(cmd, " -n");
					pthread_create(&thread, NULL, systemCall, cmd);
					pthread_join(thread, NULL);
					continue;
				}
				if (token[strlen(token)-1] == '\n') {
					token[strlen(token)-1] = '\0';
				}
				strcat(cmd, token);
				pthread_create(&thread, NULL, systemCall, cmd);
				pthread_join(thread, NULL);
				continue;
		}
		
		else if (!strcmp(token, "cat\n")) {
			printf("cat: Too few arguments\n");
		}
		
		else if (!strcmp(token, "cat&t\n")) {
			printf("cat: Too few arguments\n");
		}
		
		else if (!strcmp(token, "date")) {
			int rc = fork();
			if (!rc) {
				token = strtok(NULL, " ");
				if (!strcmp(token, "-d")) {
					token = strtok(NULL, " ");
					if (token[strlen(token)-1] == '\n') {
						token[strlen(token)-1] = '\0';
					}
					execl("/gsh/date", "/gsh/date", "-d", token, NULL);
				}
				else if (!strcmp(token, "-u\n")) {
					execl("/gsh/date", "/gsh/date", "-u", NULL);
				}
				execl("/gsh/date", "/gsh/date", NULL);
				return 0;
			} else {
				wait(0);
				continue;
			}
		}
		
		else if (!strcmp(token, "date&t")) {
				char cmd[150] = "/gsh/date ";
				token = strtok(NULL, " ");
				if (!strcmp(token, "-d")) {
					token = strtok(NULL, " ");
					if (token[strlen(token)-1] == '\n') {
						token[strlen(token)-1] = '\0';
					}
					strcat(cmd, "-d ");
					strcat(cmd, token);
					pthread_create(&thread, NULL, systemCall, cmd);
					pthread_join(thread, NULL);
					continue;
				}
				else if (!strcmp(token, "-u\n")) {
					strcat(cmd, "-u");
					pthread_create(&thread, NULL, systemCall, cmd);
					pthread_join(thread, NULL);
					continue;
				}
				strcpy(cmd, "/gsh/date");
				pthread_create(&thread, NULL, systemCall, cmd);
				pthread_join(thread, NULL);
				continue;
		}
		
		else if (!strcmp(token, "date&t\n")) {
			char cmd[150] = "/gsh/date";	
			pthread_create(&thread, NULL, systemCall, cmd);
			pthread_join(thread, NULL);
			continue;
		}
		
		else if (!strcmp(token, "date\n")) {
			int rc = fork();
			if (!rc) {
				execl("/gsh/date", "/gsh/date", NULL);
			} else {
				wait(0);
				continue;
			}
			
		}
		
		else if (!strcmp(token, "rm")) {
			int rc = fork();
			if (!rc) {
				token = strtok(NULL, " ");
				if (!strcmp(token, "-v")) {
					token = strtok(NULL, " ");
					if (token[strlen(token)-1] == '\n') {
						token[strlen(token)-1] = '\0';
					}
					execl("/gsh/rm", "/gsh/rm", "-v", token, NULL);
				}
				if (!strcmp(token, "-i")) {
					token = strtok(NULL, " ");
					if (token[strlen(token)-1] == '\n') {
						token[strlen(token)-1] = '\0';
					}
					execl("/gsh/rm", "/gsh/rm", "-i", token, NULL);
				}
				if (token[strlen(token)-1] == '\n') {
					token[strlen(token)-1] = '\0';
				}
				execl("/gsh/rm", "/gsh/rm", token, NULL);
				return 0;
			} else {
				wait(0);
				continue;
			}
		}
		
		else if (!strcmp(token, "rm&t")) {
				token = strtok(NULL, " ");
				char cmd[100] = "/gsh/rm ";
				if (!strcmp(token, "-v")) {
					token = strtok(NULL, " ");
					if (token[strlen(token)-1] == '\n') {
						token[strlen(token)-1] = '\0';
					}
					strcat(cmd, "-v ");
					strcat(cmd, token);
					pthread_create(&thread, NULL, systemCall, cmd);
					pthread_join(thread, NULL);
					continue;
				}
				if (!strcmp(token, "-i")) {
					token = strtok(NULL, " ");
					if (token[strlen(token)-1] == '\n') {
						token[strlen(token)-1] = '\0';
					}
					strcat(cmd, "-i ");
					strcat(cmd, token);
					pthread_create(&thread, NULL, systemCall, cmd);
					pthread_join(thread, NULL);
					continue;
				}
				if (token[strlen(token)-1] == '\n') {
					token[strlen(token)-1] = '\0';
				}
				strcat(cmd, token);
				pthread_create(&thread, NULL, systemCall, cmd);
				pthread_join(thread, NULL);
				continue;
		}
			
		else if (!strcmp(token, "rm\n")) {
			printf("rm: too few arguments\n");
		}
		
		else if (!strcmp(token, "rm&t\n")) {
			printf("rm: too few arguments\n");
		}
		
		else if (!strcmp(token, "mkdir")) {
			int rc = fork();
			if (!rc) {
				token = strtok(NULL, " ");
				if (!strcmp(token, "-v")) {
					token = strtok(NULL, " ");
					if (token[strlen(token)-1] == '\n') {
						token[strlen(token)-1] = '\0';
					}
					execl("/gsh/mkdir", "/gsh/mkdir", "-v", token, NULL);
				}
				if (!strcmp(token, "-m")) {
					token = strtok(NULL, " ");
					char m[10];
					strcpy(m, token);
					token = strtok(NULL, " ");
					if (token[strlen(token)-1] == '\n') {
						token[strlen(token)-1] = '\0';
					}
					execl("/gsh/mkdir", "/gsh/mkdir", "-m", m, token, NULL);
				}
				if (token[strlen(token)-1] == '\n') {
					token[strlen(token)-1] = '\0';
				}
				execl("/gsh/mkdir", "/gsh/mkdir", token, NULL);
				return 0;
			} else {
				wait(0);
				continue;
			}
		}
		
		else if (!strcmp(token, "mkdir&t")) {
			char cmd[150] = "/gsh/mkdir ";
			token = strtok(NULL, " ");
			if (!strcmp(token, "-v")) {
				token = strtok(NULL, " ");
				if (token[strlen(token)-1] == '\n') {
					token[strlen(token)-1] = '\0';
				}
				strcat(cmd, "-v ");
				strcat(cmd, token);
				pthread_create(&thread, NULL, systemCall, cmd);
				pthread_join(thread, NULL);
				continue;
			}
			if (!strcmp(token, "-m")) {
				token = strtok(NULL, " ");
				strcat(cmd, "-m ");
				strcat(cmd, token);
				strcat(cmd, " ");
				token = strtok(NULL, " ");
				if (token[strlen(token)-1] == '\n') {
					token[strlen(token)-1] = '\0';
				}
				strcat(cmd, token);
				pthread_create(&thread, NULL, systemCall, cmd);
				pthread_join(thread, NULL);
				continue;
			}
			if (token[strlen(token)-1] == '\n') {
				token[strlen(token)-1] = '\0';
			}
			strcat(cmd, token);
			pthread_create(&thread, NULL, systemCall, cmd);
			pthread_join(thread, NULL);
			continue;
		}
		
		else if (!strcmp(token, "mkdir\n")) {
			printf("mkdir: too few arguments\n");
		}
		
		else if (!strcmp(token, "mkdir&t\n")) {
			printf("mkdir: too few arguments\n");
		}
		
		else {
			if (token[strlen(token)-1] == '\n') {
				token[strlen(token)-1] = '\0';
			}
			printf("%s: command not found\n", token);
		}
	}	

}
