#include "pipex.h"

char **prepare_aruments(char *arg,char *env[])
{

    char **out;
    char *path;
    char *temp_path;

    out = ft_split(arg, ' ');
    path = absoulute_path(out[0],env);
    if (path == NULL)
    {
        perror("command not found");
        exit(EXIT_FAILURE);
    }
    temp_path = out[0];
    out[0] = path;    
    free(temp_path);
    return (out);
}