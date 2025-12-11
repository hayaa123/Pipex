/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hal-lawa <hal-lawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 15:25:07 by hal-lawa          #+#    #+#             */
/*   Updated: 2025/12/11 12:41:23 by hal-lawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <wait.h>

typedef struct s_pipex
{
	int		argc;
	char	**argv;
	int		comand_count;
	int		**fds;
	int		pipe_count;
	char	**env;
	int		last_id;
	int		infile;
	int		outfile;
}			t_pipex;

char		*absoulute_path(char *cmd, char *env[]);
void		free_splitted(char **splitted);
char		**prepare_aruments(char *arg, char *env[]);
void		free_fd(int **fd);
void		clear_all(int **fd, char **cmd);
void		fork_error(void);
int			dup2_error(void);
int			execve_error(void);
void		pipe_error(void);
int			open_file_error(void);
int			command_error(void);
int			set_output(t_pipex p, int i);
int			set_input(t_pipex pipex, int i);
int			**initiate_fd(int len);
void		create_a_process(char **cmd, int in_out[], t_pipex *p, int i);
void		safe_close(int *fd, char *msg);
int			count_eror(void);
t_pipex		initialte_pipex(int argc, char **argv, char **env);
void		close_files(t_pipex p, int i, int in_out[]);
void		error_exit(char **cmd, t_pipex *p, int f(void));
void		ch_close_files(t_pipex p);

#endif