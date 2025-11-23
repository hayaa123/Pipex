/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hal-lawa <hal-lawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 17:20:48 by haya              #+#    #+#             */
/*   Updated: 2025/11/23 15:36:19 by hal-lawa         ###   ########.fr       */
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
	perror("command not found");
	return ;
}

void	pipe_error(void)
{
	perror("Pipe error");
	return ;
}
