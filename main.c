/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hal-lawa <hal-lawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 21:10:03 by haya              #+#    #+#             */
/*   Updated: 2025/12/09 13:48:09 by hal-lawa         ###   ########.fr       */
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
		// if (!cmd)
		// {
			// handle_error(cmd, in_out, p, &i);
			// continue ;
		// }
		create_a_process(cmd, in_out, p, i);
		close_files(*p, i, in_out);
		free_splitted(cmd);
		i++;
	}
}
// // ls cat ghfkd
// static int	wait_all_process(t_pipex p)
// {
// 	int	status;
// 	int id;
// 	int last_status;

// 	last_status = 0;
// 	id = 0;
// 	waitpid(p.last_id, &status, 0);
// 	while (1)
// 	{
// 		id = waitpid(-1, &status, 0);
// 		ft_printf("pipex.id : %i\n", p.last_id);
// 		ft_printf("pid : %i\n", id);
// 		if (id == -1)
// 			break;
// 		if (p.last_id == id)
// 			last_status = status;
			
// 	}
// 	if (WIFEXITED(last_status))
//         return WEXITSTATUS(last_status);
//     return 1;
// }
// static int wait_all_process(t_pipex *p)
// {
//     int status;
//     pid_t wpid;
//     int last_exit = 1; // default non-zero
// 	ft_printf("pipex.id : %i\n", p->last_id);
//     if (p->last_id <= 0)
//         last_exit = 1; // fallback

//     // Wait for all children and remember the status for the last child pid
//     while ((wpid = wait(&status)) > 0)
//     {
// 		ft_printf("wpid: %i, p->last_id %i\n");
//         if (wpid == p->last_id)
//         {
//             if (WIFEXITED(status))
// 			{
				
//                 last_exit = WEXITSTATUS(status);
// 			}
//             else if (WIFSIGNALED(status))
//                 last_exit = 128 + WTERMSIG(status); // mimic shell for signals
//             else
// 			{
// 				ft_printf("HERE!");
//                 last_exit = 1;
// 			}
//         }
//     }

//     return last_exit;
// }
static int	wait_all_process(t_pipex p)
{
	int	status;

	waitpid(p.last_id, &status, 0);
	while (wait(NULL) > 0)
		;
	if (WIFEXITED(status))
        return WEXITSTATUS(status);
    return 1;
}

int	main(int argc, char **argv, char *env[])
{
	t_pipex	pipex;
	int		code;
	int i;

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
	while(pipex.fds[i])
	{
		safe_close(&pipex.fds[i][0], "pipe read close");
		safe_close(&pipex.fds[i][1], "pipe write close");
		i++;
	}
	code = wait_all_process(pipex);
	free_fd(pipex.fds);
	return (code);
}
