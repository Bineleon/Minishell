
#include "../../includes/minishell.h"

t_bool is_builtin(char *cmd)
{
    if (!cmd)
        return (false);
    if (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "cd") == 0 ||
        ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "export") == 0 ||
        ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "env") == 0 ||
        ft_strcmp(cmd, "exit") == 0)
        return (true);
    return (false);
}

void exec_builtin(t_data *data, t_cmd *cmds)
{
    if (ft_strcmp(cmds->cmd, "echo") == 0)
        ft_echo(cmds, STDIN_FILENO);
    else if (ft_strcmp(cmds->cmd, "cd") == 0)
        ft_cd(cmds);
    else if (ft_strcmp(cmds->cmd, "pwd") == 0)
        ft_pwd(data);
    else if (ft_strcmp(cmds->cmd, "export") == 0)
        ft_export(cmds);
    else if (ft_strcmp(cmds->cmd, "unset") == 0)
        ft_unset(cmds);
    else if (ft_strcmp(cmds->cmd, "env") == 0)
        ft_env(data);
    else if (ft_strcmp(cmds->cmd, "exit") == 0)
        ft_exit(cmds);
}
