
#include "../../includes/minishell.h"

void    ft_exit(t_data *data)
{
    int   i;

    i = 0;
    if (data->cmds->args[1])
    {
        while (data->cmds->args[1][i])
        {
            if (!ft_isdigit(data->cmds->args[1][i]))
            {
                printf("exit : %s : numeric argument required\n", data->cmds->args[1]);
                gc_mem(FULL_CLEAN, 0, NULL);
                exit(EXIT_FAILURE);
            }
            i++;
        }
        if (ft_atol(data->cmds->args[1]) > INT_MAX)
        {
            printf("exit : %s : numeric argument required\n", data->cmds->args[1]);
            gc_mem(FULL_CLEAN, 0, NULL);
            exit(2);
        }
    }
    if (data->cmds->args[1] && data->cmds->args[2])
    {
        printf("exit: too many arguments\n");
        data->exit_status = 1;
        return;
    }
    if(data->cmds->args[1])
    {
        printf("exit : %lld\n", ft_atol(data->cmds->args[1]));
        printf(MAGENTA);
        printf("\e[4mCIAO BABY!\e[0m\n");
        printf(RESET);
        gc_mem(FULL_CLEAN, 0, NULL);
        exit((int)ft_atol(data->cmds->args[1]));
    }
    printf(MAGENTA);
    printf("\e[4mCIAO BABY!\e[0m\n");
    printf(RESET);
    gc_mem(FULL_CLEAN, 0, NULL);
    exit(data->exit_status);
}
