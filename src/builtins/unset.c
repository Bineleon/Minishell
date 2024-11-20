
#include "../../includes/minishell.h"

t_env    *is_in_env(t_data *data, t_env **prev, char *key, t_bool *is_head)
{
    t_env   *curr;
    int    longest;

    curr = data->envp_cpy;
    longest = ft_longest(curr->key, key);
    if (!ft_strncmp(curr->key, key, longest))
    {
        *is_head = true;
        return (curr);
    }
    while (curr)
    {
        longest = ft_longest(curr->key, key);
        if (!ft_strncmp(curr->key, key, longest))
            return (curr);
        *prev = curr;
        curr = curr->next;
    }
    return (NULL);
}

t_bool    rm_var(t_data *data, char *key)
{
    t_env   *tmp;
    t_env   *prev;
    t_bool   is_head;

    is_head = false;
    prev = NULL;
    tmp = is_in_env(data, &prev, key, &is_head);
    if (tmp)
    {
        if (is_head)
        {
            data->envp_cpy = data->envp_cpy->next;
            free_env_node(tmp);
        }
        else
        {
            prev->next = tmp->next;
            free_env_node(tmp);
        }
        return (true);
    }
    return (false);
}

void    ft_unset(t_data *data)
{
    int   i;
    char *key;

    i = 1;
    key = NULL;
    if (!data->cmds->args[i])
    {
        printf("unset: missing argument(s)\n");
        data->exit_status = 1;
        return;
    }
    while (data->cmds->args[i])
    {
        key = data->cmds->args[i];
        if (!is_valid_key(key))
        {
            printf("unset: `%s': not a valid identifier\n", key);
            data->exit_status = 1;
            i++;
            continue;
        }
        if (rm_var(data, key))
            data->exit_status = 0;
        i++;
    }
}
