#include "pipex.h"
// #include <unistd.h>
// #include <stdio.h>
// #include<wait.h>
int main(int argc, char **srgv, char *env[])
{
    char *path = absoulute_path("lls",env);
    ft_printf("%s\n", path);
    free(path);
    // int id = fork();
    // if (id == 0)
    // {
    //     char *args[] = {
    //         "/bin/ls",
    //         "-a",
    //         NULL
    //     };
    //     char *env[] = {
    //         "PATH=/binaaaa",
    //         NULL
    //     };
    //     if (execve(args[0],args,env) == -1)
    //     {
    //         perror("execve error");
    //     }
    // }
    // wait(NULL);
}