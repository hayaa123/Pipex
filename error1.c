/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haya <haya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 17:20:48 by haya              #+#    #+#             */
/*   Updated: 2025/11/22 18:27:23 by haya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "pipex.h"

void fork_error()
{
    perror("fork error");
    return ;
}


void open_file_error()
{
    perror("open file error");
        return ;
}
void command_error()
{
    perror("command not found");
    return;
}

void pipe_error()
{
    perror("Pipe error");
        return;
}