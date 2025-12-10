/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hal-lawa <hal-lawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 17:21:17 by haya              #+#    #+#             */
/*   Updated: 2025/12/10 09:40:20 by hal-lawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	dup2_error(void)
{
	perror("dup2 Error");
	return (errno);
}

int	execve_error(void)
{
	perror("execve Error");
	return (errno);
}

// void	free_cmd_and_error(char **cmd, void (*f)())
// {
// 	if (cmd)
// 		free_splitted(cmd);
// 	return (f());
// }

int	count_eror(void)
{
	ft_putstr_fd("The programm accept at least 4 parameters.\n", 2);
	return (10);
}
