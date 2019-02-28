#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

void read_command(char* cmd, char** params)
{  
   size_t i;
   const char delimeter[2] = " ";
   char *word= strtok(cmd, delimeter);
   for (i = 0 ;word && word[0];++i)
   {
      params[i] = word;
      word =strtok(NULL,delimeter); 
   }  
}

int execute(char** params)
{
    pid_t pid = fork();
    if (pid == -1)
    {
        printf(" error fork: \n");
        return 1;
    }

    else if (pid == 0)
	{
        execvp(params[0], params);  
        return 0;
    }

    else 
    {
        int childStatus;
        waitpid(pid, &childStatus, 0);
        return 1;
    }
}

int main()
{
    char cmd[100];
    char* params[20];

    size_t cmdCount = 0;
    printf("----------------------HELLO TO RUHAMI'S SHELL------------------------\n");
    while(1) {
        printf("%s@shell %d> ","ruhami@ubuntu:", ++cmdCount);

        if(fgets(cmd, sizeof(cmd), stdin) == NULL)
			break;

        if(cmd[strlen(cmd)-1] == '\n') 
            cmd[strlen(cmd)-1] = '\0';
        
        read_command(cmd, params);

        if(strcmp(params[0], "exit") == 0)
			break;

        if(execute(params) == 0)
			break;
    }

    printf("----------------------END RUHAMI'S SHELL------------------------\n");
    return 0;
}

