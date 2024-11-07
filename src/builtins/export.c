
#include "../../includes/minishell.h"

static t_bool   is_valid_key(char  *key)
{
    int i;

    i = 1;
    if (!ft_isalpha(key[0]) && key[0] != '_')
        return (false);
    while(key[i])
    {
        if (!ft_isalnum(key[i]) && key[i] != '_')
            return (false);
        i++;
    }
    return (true);
}

static void    update_env(t_env **env, char *key, char *value)
{
    t_env   *curr;
    t_env   *new_node;

    curr = *env;
    new_node = NULL;
    while (curr)
    {
        if (ft_strncmp(curr->key, key, ft_strlen(key)) == 0)
        {
            gc_mem(FREE, 0, curr->value);
            curr->value = gc_strdup(value);
            return;
        }
        curr = curr->next
    }
    new_node = gc_mem(MALLOC, sizeof(t_env), NULL);
    new_node->key = gc_strdup(key);
    new_node->value = gc_strdup(value);
    new_node->next = *env;
    *env = new_node;

}

void    ft_export(t_data *data)
{
    char  *equal;
    int   i;

    i = 1;
    while(data->cmds->args[i])
    {
        equal = ft_strchr(data->cmds->args[i], '=');
        if(!equal)
        {
            if (!is_valid_key(data->cmds->args[i]))
            {
                printf("export: `%s': not a valid identifier\n", args[i]);
                continue;
            }
            else
                update_env(data->envp_cpy, data->cmds->args[i], "");
        }
        
        i++;
    }
}
