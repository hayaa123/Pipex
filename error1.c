/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hal-lawa <hal-lawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 17:20:48 by haya              #+#    #+#             */
/*   Updated: 2025/12/10 09:57:46 by hal-lawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	fork_error(void)
{
	perror("fork error");
	return ;
}

int	open_file_error(void)
{
	perror("open file error");
	return (errno);
}

int	command_error(void)
{
	ft_putstr_fd("command not found\n", 2);
	return (127);
}

void	pipe_error(void)
{
	perror("Pipe error");
	return ;
}

void	error_exit(char **cmd, t_pipex *p, int f(void))
{
	ch_close_files(*p);
	free_splitted(cmd);
	exit(f());
}
