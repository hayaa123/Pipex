/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haya <haya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 21:10:03 by haya              #+#    #+#             */
/*   Updated: 2025/11/22 22:11:09 by haya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void safe_close(int fd, char *msg)
{
    if (close(fd) == -1)
        perror(msg);
}

void create_a_process(char **cmd, char *env[], int input, int output)
{
    int id;
    int status;
    int error;

    id = fork();
    if(id == -1)
        return fork_error();
    if(id == 0)
    {
        if(dup2(input, 0) == -1)
            exit (dup2_error());
        if(dup2(output, 1) == -1)
            exit (dup2_error());
        safe_close(input,"input close");
        safe_close(output,"output close");
        if(execve(cmd[0], cmd, env) == -1)
            exit (execve_error());
        exit(0);
    }
}



int **initiate_fd(int len)
{
    int **fd;
    int i;

    i = 0;
    fd = malloc(sizeof(int *)*(len));
    if (!fd)
        return (NULL);
    while(i < len)
    {
        fd[i]= malloc(sizeof(int) * 2);
        if(!fd[i])
        {
            free_fd(fd, i);
            return(NULL);
        }
        i++;
    }
    return (fd);
}

int set_input(int argc, char **argv, int **fd, int i)
{
    int input;

    if(i == 0)
    {
        input = open(argv[1],O_RDWR);
        if (input == -1 ||  access(argv[1],R_OK)== -1)
            return (-1);
    }
    else if(i == (argc - 4))
        input = fd[i - 1][0];
    else
        input = fd[i - 1][0];
    return (input);
}

int set_output(int argc, char **argv, int **fd, int i)
{
    int output;

    if(i == 0)
        output = fd[0][1];
    else if(i == (argc - 4))
    {
        output = open(argv[argc-1], O_RDWR | O_CREAT | O_TRUNC, 0644);
        if (output == -1)
            return (-1);
    }
    else
        output = fd[i][1];

    return (output);
}

void create_pipes(int argc, int **fd)
{
    int i;

    i = 0;
    while(i < argc - 4)
    {
        if(pipe(fd[i]) == -1)
        {
            pipe_error();
            return;
        }
        i++;
    }
}

void close_files(int **fd, int i,int input, int argc)
{
    if (i > 0)
        safe_close(fd[i-1][0],"pipe read close");
    if (i < (argc - 4))
        safe_close(fd[i][1],"pipe write close");
    if ( i == 0)
        safe_close(input,"input close");
}

void create_pipes_process(int argc, char **argv, char *env[], int **fd)
{
    int i;
    char **cmd;
    int input;
    int output;

    i = 0;
    create_pipes(argc,fd);
    while (i < (argc - 3))
    {
        if (errno != 0)
            return ;
        cmd = prepare_aruments(argv[i + 2], env);
        if (!cmd || errno != 0)
            return command_error();
        input = set_input(argc, argv, fd, i);
        output = set_output(argc, argv, fd, i);
        if (input == -1 || output == -1)
            return (open_file_error());
        create_a_process(cmd, env, input, output);
        close_files(fd, i, input, argc);
        free_splitted(cmd);
        if(errno != 0)
            return;
        i++;
    }
}
void wait_all_process(int argc)
{
    int i;
    int status;

    i = 0;
    while (i < (argc - 3))
    {
        waitpid(-1, &status, 0);
        i++;
    }
}

int main(int argc, char **argv, char *env[])
{
    int **fd;
    int len;
    
    if ( argc < 5)
        return 10;
    len = argc - 3;
    fd = initiate_fd(len);
    if(!fd)
        return (10);

    create_pipes_process(argc, argv,  env, fd);
    if(errno != 0)
    {
        free_fd(fd,len);
        return (errno);
    }
    free_fd(fd, len);
    wait_all_process(argc);
    return (0);
}
