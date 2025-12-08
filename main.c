/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hal-lawa <hal-lawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 21:10:03 by haya              #+#    #+#             */
/*   Updated: 2025/12/08 10:26:23 by hal-lawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	create_pipes(int argc, int **fd)
{
	int	i;

	i = 0;
	while (i < argc - 4)
	{
		if (pipe(fd[i]) == -1)
		{
			pipe_error();
			return ;
		}
		i++;
	}
}

static void	handle_error(char **cmd, int *in_out, t_pipex p, int *i)
{
	if (in_out[0] == -1 || in_out[1] == -1)
		open_file_error();
	else
		command_error();
	close_files(p, *i, in_out);
	free_splitted(cmd);
	(*i)++;
}

static void	create_pipes_process(t_pipex p)
{
	int		i;
	char	**cmd;
	int		in_out[2];

	i = 0;
	while (i < (p.argc - 3))
	{
		in_out[0] = set_input(p, i);
		in_out[1] = set_output(p, i);
		if (in_out[0] == -1 || in_out[1] == -1)
		{
			handle_error(NULL, in_out, p, &i);
			continue ;
		}
		cmd = prepare_aruments(p.argv[i + 2], p.env);
		if (!cmd || errno != 0)
		{
			handle_error(cmd, in_out, p, &i);
			continue ;
		}
		create_a_process(cmd, in_out, p);
		close_files(p, i, in_out);
		free_splitted(cmd);
		i++;
	}
}

static int	wait_all_process(t_pipex p)
{
	int	status;

	waitpid(p.last_id, &status, 0);
	while (wait(NULL) > 0)
		;
	return (status);
}

int	main(int argc, char **argv, char *env[])
{
	t_pipex	pipex;
	int		code;

	if (argc < 5)
		return (count_eror());
	pipex = initialte_pipex(argc, argv, env);
	if (!pipex.fds)
	{
		ft_putstr_fd("Malloc failed!\n", 2);
		return (10);
	}
	create_pipes(argc, pipex.fds);
	create_pipes_process(pipex);
	code = wait_all_process(pipex);
	close_readers(pipex.fds);
	free_fd(pipex.fds);
	return (code);
}
