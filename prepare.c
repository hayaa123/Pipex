#include "pipex.h"

char **prepare_aruments(char *arg,char *env[])
{
    char **out;
    char *path;
    char *temp_path;
    (void) arg;
    (void) env;
    out = ft_split(arg, ' ');
    if (!out)
        return(NULL);
    path = absoulute_path(out[0],env);
    if (path == NULL)
    {   
        free_splitted(out);
        return (NULL);
    }
    temp_path = out[0];
    out[0] = path;    
    free(temp_path);
    return (out);
}