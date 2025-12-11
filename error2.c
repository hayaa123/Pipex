/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hal-lawa <hal-lawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 17:21:17 by haya              #+#    #+#             */
/*   Updated: 2025/12/11 12:26:59 by hal-lawa         ###   ########.fr       */
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

int	count_eror(void)
{
	ft_putstr_fd("The programm accepts only 4 parameters.\n", 2);
	return (10);
}
