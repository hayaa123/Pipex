/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hal-lawa <hal-lawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 17:21:53 by haya              #+#    #+#             */
/*   Updated: 2025/12/08 10:00:18 by hal-lawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_fd(int **fd)
{
	int	i;

	i = 0;
	while (fd[i])
	{
		free(fd[i]);
		i++;
	}
	free(fd);
}

void	free_splitted(char **splitted)
{
	int	i;

	if (!splitted)
		return ;
	i = 0;
	while (splitted[i])
	{
		free(splitted[i]);
		i++;
	}
	free(splitted);
}

void	clear_all(int **fd, char **cmd)
{
	if (cmd)
		free_splitted(cmd);
	if (fd)
		free_fd(fd);
}

void	close_readers(int **fd)
{
	int	i;

	i = 0;
	while (fd[i])
	{
		safe_close(&fd[i][0], "pipe read close");
		i++;
	}
}

void	close_files(t_pipex p, int i, int in_out[])
{
	if (i < p.pipe_count)
		safe_close(&p.fds[i][1], "pipe write close");
	if (i == 0)
		safe_close(&in_out[0], "input close");
	if (i == p.pipe_count)
		safe_close(&in_out[1], "output close");
}
