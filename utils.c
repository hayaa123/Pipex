#include "pipex.h"
static char *get_path(char* env[])
{
    char *path;
    int i;

    i = 0;
    while(env[i])
    {
        if(ft_strnstr(env[i],"PATH=",5))
        {
            path = env[i];
        }
        i++;
    }
    path = ft_strtrim(path,"PATH=");
    return (path);
}

void free_splitted(char **splitted)
{
    int i;

    i = 0;
    while(splitted[i])
    {
        free(splitted[i]);
        i++;
    }
    free(splitted);
}

static char *safe_join(char *str1,char *str2)
{
    char *result;
    result = ft_strjoin(str1,str2);
    free(str1);
    return (result);
}

char *absoulute_path(char *cmd, char* env[])
{
    char *path;
    char **paths;
    char *sub;
    int i;

    path = get_path(env);
    paths = ft_split(path, ':');
    free(path);
    i = 0;
    while(paths[i]){
        sub = ft_strjoin(paths[i],"/");
        sub = safe_join(sub, cmd);
        if (access(sub,F_OK) == 0)
        {
            free_splitted(paths);
            return (sub);
        }
        free(sub);
        i++;
    }
    free_splitted(paths);
    return(NULL);
}