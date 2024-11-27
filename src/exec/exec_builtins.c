
#include "../../includes/minishell.h"

void    start_buitlin(t_data *data)
{


}


t_bool	is_builtin(t_data *data)
{
    char	*tmp;

    tmp = data->cmds->args[0];
    if (!tmp)
        return (false);
    if (ft_strcmp("echo", tmp) == 0)
        return (true);
    else if (ft_strcmp("cd", tmp) == 0)
        return (true);
    else if (ft_strcmp("pwd", tmp) == 0)
        return (true);
    else if (ft_strcmp("exit", tmp) == 0)
        return (true);
    else if (ft_strcmp("unset", tmp) == 0)
        return (true);
    else if (ft_strcmp("export", tmp) == 0)
        return (true);
    else if (ft_strcmp("env", tmp) == 0)
        return (true);
    return (false);
}
