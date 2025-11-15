#include "pipex.h"

int main(int argc, char **argv, char *env[])
{
    // int fd[2];
    int id;
    int id2;
    char **cmd1;
    char **cmd2;
    int status;

    cmd1 = prepare_aruments(argv[2],env);
    cmd2 = prepare_aruments(argv[3],env);
    ft_printf("%s\n",cmd1[0]);
    id = fork();

    if(id == -1)
    {
        perror("fork error");
        return 2;
    }
    if (id == 0)
    {
        if (execve(cmd1[0],cmd1,env) == -1)
        {
            perror("execve error");
            exit(1);
        }
    }
    id2 = fork();
    if(id2 == -1)
    {
        perror("fork error");
        return 2;
    }
    if(id2 == 0)
        if (execve(cmd2[0],cmd2,env) == -1)
        {
            perror("execve error");
            exit(1);
        }
    waitpid(id,&status,0);
    waitpid(id2,&status,0);
}