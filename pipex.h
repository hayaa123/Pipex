#include <unistd.h>
#include "libft/libft.h"
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <wait.h>
#include <errno.h>  
#include <fcntl.h>

char *absoulute_path(char *cmd, char* env[]);
char **prepare_aruments(char *arg,char *env[]);
void free_splitted(char **splitted);
