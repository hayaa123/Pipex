/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hal-lawa <hal-lawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 21:10:03 by haya              #+#    #+#             */
/*   Updated: 2025/12/10 10:30:39 by hal-lawa         ###   ########.fr       */
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
	close_files(p, *i, in_out);
	free_splitted(cmd);
	(*i)++;
}

static void	create_pipes_process(t_pipex *p)
{
	int		i;
	char	**cmd;
	int		in_out[2];

	i = 0;
	while (i < (p->argc - 3))
	{
		in_out[0] = set_input(*p, i);
		in_out[1] = set_output(*p, i);
		if (in_out[0] == -1 || in_out[1] == -1)
		{
			handle_error(NULL, in_out, *p, &i);
			continue ;
		}
		cmd = prepare_aruments(p->argv[i + 2], p->env);
		create_a_process(cmd, in_out, p, i);
		close_files(*p, i, in_out);
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
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

int	main(int argc, char **argv, char *env[])
{
	t_pipex	pipex;
	int		code;
	int		i;

	i = 0;
	if (argc < 5)
		return (count_eror());
	pipex = initialte_pipex(argc, argv, env);
	if (!pipex.fds)
	{
		ft_putstr_fd("Malloc failed!\n", 2);
		return (10);
	}
	create_pipes(argc, pipex.fds);
	create_pipes_process(&pipex);
	while (pipex.fds[i])
	{
		safe_close(&pipex.fds[i][0], "pipe read close");
		safe_close(&pipex.fds[i][1], "pipe write close");
		i++;
	}
	code = wait_all_process(pipex);
	free_fd(pipex.fds);
	return (code);
}
