/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haya <haya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 10:36:25 by haya              #+#    #+#             */
/*   Updated: 2025/12/05 21:12:28 by haya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	safe_close(int *fd, char *msg)
{
	if ((*fd) == -1)
		return ;
	if (close(*fd) == -1)
		perror(msg);
	(*fd) = -1;
}

static void close_files(int **fd)
{
    int i = 0;

    while (fd[i])
    {
        if (fd[i][0] != -1)
            if (close(fd[i][0]) == -1)
                perror("Read end of the pipe");
        if (fd[i][1] != -1)
		{
            if (close(fd[i][1]) == -1){
                perror("Write end of the pipe");
			}
		}
        i++;
    }
}



/**
 * @brief creates a child
 */
void	create_a_process(char **cmd, char *env[], int in_out[], int **fd)
{
	int	id;

	id = fork();
	if (id == -1)
		return (fork_error());
	if (id == 0)
	{
		if (in_out[0] == -1)
			exit(0);
		if (dup2(in_out[0], 0) == -1)
			exit(dup2_error());
		if (dup2(in_out[1], 1) == -1)
			exit(dup2_error());
		close_files(fd);
		if (execve(cmd[0], cmd, env) == -1)
		{
			free_splitted(cmd);
			exit(execve_error());
		}
	}
}

int	**initiate_fd(int len)
{
	int	**fd;
	int	i;

	i = 0;
	fd = malloc(sizeof(int *) * (len + 1));
	if (!fd)
		return (NULL);
	while (i < len)
	{
		fd[i] = malloc(sizeof(int) * 2);
		if (!fd[i])
		{
			free_fd(fd);
			return (NULL);
		}
		i++;
	}
	fd[i] = NULL;
	return (fd);
}

int	set_input(int argc, char **argv, int **fd, int i)
{
	int	input;

	if (i == 0)
	{
		input = open(argv[1], O_RDWR);
		if (input == -1 || access(argv[1], R_OK) == -1)
			return (-1);
	}
	else if (i == (argc - 4))
		input = fd[i - 1][0];
	else
		input = fd[i - 1][0];
	return (input);
}

int	set_output(int argc, char **argv, int **fd, int i)
{
	int	output;

	if (i == 0)
		output = fd[0][1];
	else if (i == (argc - 4))
	{
		output = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (output == -1)
			return (-1);
	}
	else
		output = fd[i][1];
	return (output);
}
