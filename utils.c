/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hal-lawa <hal-lawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 17:22:20 by haya              #+#    #+#             */
/*   Updated: 2025/12/08 09:59:29 by hal-lawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*get_path(char *env[])
{
	char	*path;
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH=", 5))
		{
			path = env[i];
		}
		i++;
	}
	path = ft_strtrim(path, "PATH=");
	return (path);
}

static char	*safe_join(char *str1, char *str2)
{
	char	*result;

	result = ft_strjoin(str1, str2);
	free(str1);
	return (result);
}

char	*absoulute_path(char *cmd, char *env[])
{
	char	*path;
	char	**paths;
	char	*sub;
	int		i;

	path = get_path(env);
	paths = ft_split(path, ':');
	free(path);
	i = 0;
	while (paths[i])
	{
		sub = ft_strjoin(paths[i], "/");
		sub = safe_join(sub, cmd);
		if (access(sub, F_OK) == 0)
		{
			errno = 0;
			free_splitted(paths);
			return (sub);
		}
		free(sub);
		i++;
	}
	free_splitted(paths);
	return (NULL);
}

int	set_input(t_pipex pipex, int i)
{
	int	input;

	if (i == 0)
		input = pipex.infile;
	else
		input = pipex.fds[i - 1][0];
	return (input);
}

int	set_output(t_pipex p, int i)
{
	int	output;

	if (i == 0)
		output = p.fds[0][1];
	else if (i == p.pipe_count)
		output = p.outfile;
	else
		output = p.fds[i][1];
	return (output);
}
