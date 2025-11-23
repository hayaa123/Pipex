/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haya <haya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 21:10:03 by haya              #+#    #+#             */
/*   Updated: 2025/11/23 12:02:16 by haya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
        {
            if (cmd)
                free_splitted(cmd);
            return command_error();
        }
        input = set_input(argc, argv, fd, i);
        output = set_output(argc, argv, fd, i);
        if (input == -1 || output == -1)
        {
            free_splitted(cmd);
            return (open_file_error());
        }
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
