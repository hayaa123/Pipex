/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hal-lawa <hal-lawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 15:25:07 by hal-lawa          #+#    #+#             */
/*   Updated: 2025/12/01 10:21:59 by hal-lawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <wait.h>

char	*absoulute_path(char *cmd, char *env[]);
void	free_splitted(char **splitted);
char	**prepare_aruments(char *arg, char *env[]);
void	free_fd(int **fd, int len);
void	clear_all(int **fd, int len, char **cmd);
void	fork_error(void);
int		dup2_error(void);
int		execve_error(void);
void	pipe_error(void);
void	open_file_error(void);
void	command_error(void);
int		set_output(int argc, char **argv, int **fd, int i);
int		set_input(int argc, char **argv, int **fd, int i);
int		**initiate_fd(int len);
void	create_a_process(char **cmd, char *env[], int input, int output);
void	safe_close(int fd, char *msg);
void	free_cmd_and_error(char **cmd, void (*f)());
int		count_eror(void);

#endif