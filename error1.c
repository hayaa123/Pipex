/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hal-lawa <hal-lawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 17:20:48 by haya              #+#    #+#             */
/*   Updated: 2025/12/08 10:03:41 by hal-lawa         ###   ########.fr       */
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

void	command_error(void)
{
	ft_putstr_fd("command not found\n", 2);
	return ;
}

void	pipe_error(void)
{
	perror("Pipe error");
	return ;
}
