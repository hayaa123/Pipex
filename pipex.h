#include <unistd.h>
#include "libft/libft.h"
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <wait.h>
#include <errno.h>  
#include <fcntl.h>

char *absoulute_path(char *cmd, char* env[]);
void free_splitted(char **splitted);
char **prepare_aruments(char *arg,char *env[]);
void free_fd(int **fd, int len);
void clear_all(int **fd, int len, char **cmd);
void fork_error();
int dup2_error();
int execve_error();
void pipe_error();
void open_file_error();
void command_error();