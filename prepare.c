/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hal-lawa <hal-lawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 15:36:49 by hal-lawa          #+#    #+#             */
/*   Updated: 2025/11/23 15:36:52 by hal-lawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**prepare_aruments(char *arg, char *env[])
{
	char	**out;
	char	*path;
	char	*temp_path;

	out = ft_split(arg, ' ');
	if (!out)
		return (NULL);
	path = absoulute_path(out[0], env);
	if (path == NULL)
	{
		free_splitted(out);
		return (NULL);
	}
	temp_path = out[0];
	out[0] = path;
	free(temp_path);
	return (out);
}
