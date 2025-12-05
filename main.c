/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haya <haya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 21:10:03 by haya              #+#    #+#             */
/*   Updated: 2025/12/05 21:04:09 by haya             ###   ########.fr       */
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

static void	close_files(int **fd, int i, int in_out[], int argc)
{

		if (i < (argc - 4))
			safe_close(&fd[i][1], "pipe write close");
		if (i == 0)
			safe_close(&in_out[0], "input close");
		if (i == (argc - 4) && in_out[1] != -1)
			safe_close(&in_out[1], "output close");	
}


// static void	handle_error(char **cmd, int *in_out, int **fd, int *i)
// {
// 	if (in_out[0] == -1 || in_out[1] == -1)
// 		open_file_error();
// 	else
//     	command_error();
//     close_files(fd, *i, in_out, 0);
//     free_splitted(cmd);
// 	(*i)++;
// }

static void	handle_error(int *in_out, int **fd, int *i, int argc)
{
	if (in_out[0] == -1 || in_out[1] == -1)
		open_file_error();
	else
    	command_error();
    
    // Close all pipe ends for this process
    if (*i > 0 && *i < argc - 3)
        safe_close(&fd[*i - 1][0], "pipe read close in error");
    if (*i < argc - 4)
        safe_close(&fd[*i][1], "pipe write close in error");
    
    // free_splitted(cmd);
	(*i)++;
}


static void	create_pipes_process(int argc, char **argv, char *env[], int **fd)
{
	int		i;
	char	**cmd;
	int		in_out[2];	

	i = 0;
	while (i < (argc - 3))
	{
		in_out[0] = set_input(argc, argv, fd, i);
		in_out[1] = set_output(argc, argv, fd, i);
		if (in_out[0] == -1 || in_out[1] == -1)
		{
			handle_error(in_out, fd, &i, argc);
			continue;
		}
		cmd = prepare_aruments(argv[i + 2], env);
		if (!cmd || errno != 0)
		{
			handle_error(in_out, fd, &i, argc);
			free_splitted(cmd);
			continue;
		}
		create_a_process(cmd, env, in_out, fd);
		close_files(fd, i, in_out, argc);
		free_splitted(cmd);
		i++;
	}
}

static int wait_all_process(int argc)
{
	int	i;
	int	status;
	int code;
	
	i = 0;
	while (i < (argc - 3))
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status))
		{
			code = WEXITSTATUS(status);
		}
		i++;
	}
	return code;
}


int	main(int argc, char **argv, char *env[])
{
	int	**fd;
	int	len;

	if (argc < 5)
		return (count_eror());
	len = argc - 3;
	fd = initiate_fd(len - 1);
	if (!fd)
	{
		ft_putstr_fd("Malloc failed!\n", 2);
		return (10);
	}
	create_pipes(argc, fd);
	create_pipes_process(argc, argv, env, fd);
	if (errno != 0)
	{
		close_readers(fd);
		free_fd(fd);
		return (errno);
	}
	int code = wait_all_process(argc);
	close_readers(fd);
	free_fd(fd);
	return (code);
}

