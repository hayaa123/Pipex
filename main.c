/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haya <haya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 21:10:03 by haya              #+#    #+#             */
/*   Updated: 2025/12/03 22:06:19 by haya             ###   ########.fr       */
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

static void	close_files(int **fd, int i, int input, int argc)
{
	if (i > 0)
		safe_close(fd[i - 1][0], "pipe read close");
	if (i < (argc - 4))
		safe_close(fd[i][1], "pipe write close");
	if (i == 0)
		safe_close(input, "input close");
}

static void	create_pipes_process(int argc, char **argv, char *env[], int **fd)
{
	int		i;
	char	**cmd;
	int		input;
	int		output;

	i = 0;
	create_pipes(argc, fd);
	while (i <= (argc - 3))
	{
		cmd = prepare_aruments(argv[i + 2], env);
		if (!cmd || errno != 0)
			command_error();
		input = set_input(argc, argv, fd, i);
		ft_printf("input : %i\n",input);
		output = set_output(argc, argv, fd, i);
		if (input == -1 || output == -1)
			open_file_error();
		create_a_process(cmd, env, input, output);
		close_files(fd, i, input, argc);
		free_splitted(cmd);
		i++;
	}
}

static void	wait_all_process(int argc)
{
	int	i;
	int	status;

	i = 0;
	while (i < (argc - 3))
	{
		waitpid(-1, &status, 0);
		i++;
	}
}

int	main(int argc, char **argv, char *env[])
{
	int	**fd;
	int	len;

	if (argc < 5)
		return (count_eror());
	len = argc - 3;
	ft_printf("len: %d\n",len);
	fd = initiate_fd(len - 1);
	if (!fd)
	{
		ft_putstr_fd("Malloc failed!\n", 2);
		return (10);
	}
	create_pipes_process(argc, argv, env, fd);
	if (errno != 0)
	{
		free_fd(fd, len - 1);
		return (errno);
	}
	free_fd(fd, len - 1);
	wait_all_process(argc);
	return (0);
}
