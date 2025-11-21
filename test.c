#include "pipex.h"

int fork_error()
{
    perror("fork error");
    return 1;
}

int dup2_error()
{
    perror("dup2 Error");
        return 2;
}
int execve_error()
{
    perror("execve Error");
        return 3; 
}

int pipe_error()
{
    perror("Pipe error");
        return 6;
}

int open_file_error()
{
    perror("open file error");
        return 4;
}

int command_error()
{
    perror("command not found");
        return 5;
}

int create_a_process(char **cmd, char *env[], int input, int output)
{
    int id;
    int status;

    id = fork();
    if(id == -1)
        return fork_error();
    if(id == 0)
    {

        if(dup2(input, 0) == -1)
            return dup2_error();
        if(dup2(output, 1) == -1)
            return dup2_error();
        close(input);
        close(output);
        if(execve(cmd[0], cmd, env) == -1)
            return execve_error();
    }
    close(input);
    waitpid(id, &status, 0);
    return (0);
}

void free_fd(int **fd, int len)
{
    int i;

    i = 0;
    while(i < len)
    {
        free(fd[i]);
        i++;
    }
    free(fd);
}

int **initiate_fd(int len)
{
    int **fd;
    int i;

    fd = malloc(sizeof(int *)*(len));
    while(i < len)
    {
        fd[i]= malloc(sizeof(int) * 2);
        i++;
    }
    return (fd);
}

int main(int argc, char **argv, char **env)
{
    int **fd;
    int input;
    int output;
    char **cmd;
    int i;

    if ( argc < 5)
        return 10;
    i = 0;
    fd = initiate_fd(argc - 3);
    while (i < (argc - 3))
    {
        if( i != (argc - 4))
            if(pipe(fd[i]) == -1)
                return pipe_error();
        cmd = prepare_aruments(argv[i + 2],env);
        if (!cmd)
            return command_error();
        if(i == 0)
        {
            input = open(argv[1],O_RDWR);
            output = fd[0][1];
            if (input == -1 ||  access(argv[1],R_OK)== -1)
                return open_file_error();
        }
        else if(i == (argc - 4))
        {
            input = fd[i - 1][0];
            output = open(argv[argc-1], O_RDWR | O_CREAT | O_TRUNC, 0644);
            if (output == -1)
                return open_file_error();
        }
        else
        {
            input = fd[i - 1][0];
            output = fd[i][1];
        }
        create_a_process(cmd,env,input,output);
        free_splitted(cmd);
        close(output);
        i++;
    }
    wait(NULL);
    free_fd(fd, (argc - 3));
}
