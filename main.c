/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hal-lawa <hal-lawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 21:10:03 by haya              #+#    #+#             */
/*   Updated: 2025/12/07 13:47:06 by hal-lawa         ###   ########.fr       */
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
static void close_readers(int **fd)
{
	int i;
	
	i = 0;
	while(fd[i])
	{
		safe_close(&fd[i][0],"pipe read close");
		i++;
	}
}

static void	close_files(t_pipex p, int i, int in_out[])
{
	if (i <  p.pipe_count )
		safe_close(&p.fds[i][1], "pipe write close");
	if (i == 0)
	{
		if (in_out[0] == -1)
			safe_close(&in_out[1], "out close");
		safe_close(&in_out[0], "input close");
	}
	if (i == p.pipe_count)
	{
		safe_close(&in_out[1], "output close");
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
			continue;
		}
		cmd = prepare_aruments(p.argv[i + 2], p.env);
		if (!cmd || errno != 0)
		{
			handle_error(cmd, in_out, p, &i);
			continue;
		}
		create_a_process(cmd, in_out, p);
		close_files(p, i, in_out);
		free_splitted(cmd);
		i++;
	}
}
#include <stdio.h>

static int wait_all_process(t_pipex p, int argc)
{
	// int	i;
	int	status;
	int code;
	int id;
	

	// i = 0;
	(void)argc;
	while (1)
	{
		id = waitpid(-1, &status, 0);
		if (id < 0)
			break;
		if (WIFEXITED(status) && id == p.last_id)
		{
			code = WEXITSTATUS(status);
		}
	}
	return code;
}


int	main(int argc, char **argv, char *env[])
{
	t_pipex pipex;
	
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
	int code = wait_all_process(pipex, argc);
	close_readers(pipex.fds);
	free_fd(pipex.fds);
	return (code);
}

