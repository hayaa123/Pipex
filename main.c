#include "pipex.h"

void infile_cmd_exec(char **argv, char *env[], int fd[], char **cmd1)
{
    int infile;

    infile = open(argv[1],O_RDWR);
    if(infile == -1)
        perror("open error");
    dup2(infile,0);
    dup2(fd[1],1);
    close(fd[0]);
    close(fd[1]);
    close(infile);
    if (execve(cmd1[0],cmd1,env) == -1)
    {
        perror("execve error");
        exit(1);
    }
}

void outfile_cmd_exec(char **argv, char *env[], int fd[], char **cmd2,int outfile)
{
    dup2(fd[0],0);
    dup2(outfile, 1);
    close(fd[0]);
    close(fd[1]);
    if (execve(cmd2[0],cmd2,env) == -1)
    {
        perror("execve error");
        exit(1);
    }
}

int fork_eror()
{
    perror("fork error");
    return 2;
}

int create_sup_process(char **argv, char *env[], int fd[],int outfile)
{
    int id;
    int id2;
    char **cmd1;
    char **cmd2;
    int status;


    id = fork();
    cmd1 = prepare_aruments(argv[2],env);
    cmd2 = prepare_aruments(argv[3],env);
    if(id == -1)
        return fork_eror();
    if (id == 0)
        infile_cmd_exec(argv,env,fd,cmd1);
    id2 = fork();
    if(id2 == -1)
        return fork_eror();
    if(id2 == 0)
        outfile_cmd_exec(argv,env,fd,cmd2,outfile);
    close(fd[1]);
    waitpid(id,&status,0);
    waitpid(id2,&status,0);
    free_splitted(cmd1);
    free_splitted(cmd2);
    return(0);
}

int main(int argc, char **argv, char *env[])
{
    int fd[2];
    int outfile;


    outfile = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0644);
    if(outfile == -1)
    {
        perror("open file error");
        return 3;
    }
    if(pipe(fd) == -1)
    {
        perror("pipe error");
        return 1;
    }
    if (create_sup_process(argv,env,fd,outfile) != 0)
        return create_sup_process(argv,env,fd,outfile);
    close(fd[0]);
    close(outfile);
}


// int main(int argc, char **argv, char *env[])
// {
//     int fd[2];
//     int id;
//     int id2;
//     char **cmd1;
//     char **cmd2;
//     int status;
//     int infile;
//     int outfile;
//     // char *output;

//     cmd1 = prepare_aruments(argv[2],env);
//     cmd2 = prepare_aruments(argv[3],env);
//     outfile = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0644);
//     infile = open(argv[1],O_RDWR);
//     if(outfile == -1)
//     {
//         perror("open file error");
//         return 3;
//     }
//     if(infile == -1)
//         perror("open error");
//     if(pipe(fd) == -1)
//     {
//         perror("pipe error");
//         return 1;
//     }
//     id = fork();

//     if(id == -1)
//     {
//         perror("fork error");
//         return 2;
//     }
//     if (id == 0)
//     {
//         dup2(infile,0);
//         dup2(fd[1],1);
//         close(fd[0]);
//         close(fd[1]);
//         if (execve(cmd1[0],cmd1,env) == -1)
//         {
//             perror("execve error");
//             exit(1);
//         }
//     }
//     id2 = fork();
//     if(id2 == -1)
//     {
//         perror("fork error");
//         return 2;
//     }
//     if(id2 == 0)
//     {
//         dup2(fd[0],0);
//         dup2(outfile, 1);
//         close(fd[0]);
//         close(fd[1]);
//         if (execve(cmd2[0],cmd2,env) == -1)
//         {
//             perror("execve error");
//             exit(1);
//         }
//     }
//     close(fd[1]);
//     waitpid(id,&status,0);
//     waitpid(id2,&status,0);
//     dup2(outfile,1);
//     free_splitted(cmd1);
//     free_splitted(cmd2);
//     close(fd[0]);
//     close(infile);
//     close(outfile);
// }