/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haya <haya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 17:20:48 by haya              #+#    #+#             */
/*   Updated: 2025/12/05 18:00:17 by haya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	fork_error(void)
{
	perror("fork error");
	return ;
}

void	open_file_error(void)
{
	perror("open file error");
	return ;
}

void	command_error()
{
	// perror("command not found");
	// int i;

	// i = 0;
	ft_putstr_fd("command not found\n", 2);
	// while (cmd[i] && cmd[i] != ' ')
	// {
	// 	ft_putchar_fd(cmd[i], 2);
	// 	i++;
	// }
	// ft_putchar_fd('\n',2);
	// return ;
}

void	pipe_error(void)
{
	perror("Pipe error");
	return ;
}
