/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hal-lawa <hal-lawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 21:10:03 by haya              #+#    #+#             */
/*   Updated: 2025/12/04 17:30:18 by hal-lawa         ###   ########.fr       */
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

	// if (i > 0)
	// {
	// 	safe_close(fd[i - 1][0], "pipe read close");
	// }
	if (i < (argc - 4))
	{
		safe_close(fd[i][1], "pipe write close");
	}
	if (i == 0)
		safe_close(input, "input close");
}

void	print_fd_table(int **fd, int pipes, const char *msg)
{
	printf("\n===== FD TABLE DEBUG: %s =====\n", msg);

	for (int i = 0; i < pipes; i++)
	{
		printf("Pipe %d: read_fd = %d, write_fd = %d\n",
				i, fd[i][0], fd[i][1]);
	}

	printf("===== END FD TABLE =====\n\n");
}

static void	create_pipes_process(int argc, char **argv, char *env[], int **fd)
{
	int		i;
	char	**cmd;
	int		input;
	int		output;

	i = 0;
	create_pipes(argc, fd);
	print_fd_table(fd, argc - 4, "After create_pipes");
	while (i < (argc - 3))
	{
		input = set_input(argc, argv, fd, i);
		output = set_output(argc, argv, fd, i);
		if (input == -1 || output == -1)
			open_file_error();
		cmd = prepare_aruments(argv[i + 2], env);
		if ((!cmd || errno != 0) && input != -1)
			command_error(argv[i + 2]);
		if (input != -1 && output != -1 && cmd)
			create_a_process(cmd, env, input, output);
		close_files(fd, i, input, argc);
		if (i == (argc - 4) && output != -1)
            safe_close(output, "output close");
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

void close_readers(int **fd, int len)
{
	int i;
	
	i = 0;
	while(i < len)
	{
		safe_close(fd[i][0],"pipe read close");
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
	int code = wait_all_process(argc);
	close_readers(fd,len -1);
	free_fd(fd, len - 1);
	return (code);
}

