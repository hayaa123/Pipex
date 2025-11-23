/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haya <haya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 17:21:53 by haya              #+#    #+#             */
/*   Updated: 2025/11/23 10:38:08 by haya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void free_fd(int **fd, int len)
{
    int i;

    i = 0;
    while (i < len)
    {
        free(fd[i]);
        i++;
    }
    free(fd);
}

void free_splitted(char **splitted)
{
    int i;

    i = 0;
    while (splitted[i])
    {
        free(splitted[i]);
        i++;
    }
    free(splitted);
}

void clear_all(int **fd, int len, char **cmd)
{
    if (cmd)
        free_splitted(cmd);
    if (fd)
        free_fd(fd, len);
}