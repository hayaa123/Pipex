#include "pipex.h"

char **prepare_aruments(char *arg,char *env[])
{
    char **out = ft_split(arg, ' ');
    char *path = absoulute_path(out[0],env);
    if (path == NULL)
    {
        perror("command not found");
        exit(EXIT_FAILURE);
    }
    out[0] = path;    
    return (out);
}