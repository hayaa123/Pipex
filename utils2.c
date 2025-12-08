/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hal-lawa <hal-lawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 10:36:25 by haya              #+#    #+#             */
/*   Updated: 2025/12/08 12:09:12 by hal-lawa         ###   ########.fr       */
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

static void	ch_close_files(t_pipex p)
{
	int	i;

	i = 0;
	while (p.fds[i])
	{
		if (p.fds[i][0] != -1)
			if (close(p.fds[i][0]) == -1)
				perror("Read end of the pipe");
		if (p.fds[i][1] != -1)
		{
			if (close(p.fds[i][1]) == -1)
			{
				perror("Write end of the pipe");
			}
		}
		i++;
	}
	close(p.infile);
	close(p.outfile);
	
}

void	create_a_process(char **cmd, int in_out[], t_pipex *p)
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
		ch_close_files(*p);
		execve(cmd[0], cmd, p->env);
		free_splitted(cmd);
		exit(execve_error());
	}
	p->last_id = id;
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

t_pipex	initialte_pipex(int argc, char **argv, char **env)
{
	t_pipex	pipex;
	int		input;
	int		output;

	if (access(argv[1], R_OK) == -1)
		input = -1;
	else
		input = open(argv[1], O_RDWR);
	output = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (output < 0)
	{
		perror(argv[4]);
		exit(1);
	}
	pipex.pipe_count = argc - 4;
	pipex.argc = argc;
	pipex.argv = argv;
	pipex.env = env;
	pipex.fds = initiate_fd(pipex.pipe_count);
	pipex.infile = input;
	pipex.outfile = output;
	pipex.last_id = -1;
	return (pipex);
}
