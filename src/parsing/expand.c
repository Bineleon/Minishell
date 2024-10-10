#include "../../includes/minishell.h"

t_bool    is_in_squote(t_fullcmd *token)
{
    if (token->str[0] == SQUOTE)
        return (true);
    return (false);
}


char *get_env_value(char *var_name, t_env *env_list)
{
    t_env *current = env_list;

    while (current)
    {
        if (ft_strncmp (current->key, var_name, ft_strlen(var_name)) == 0)
            return current->value;
        current = current->next;
    }
    return (NULL);
}

void    replace_env(t_fullcmd *token)
{
    t_fullcmd   *current;

    current = token;
    while(current)
    {
        if (current->type == WORD && !is_in_squote(current))
        {

        }
        current = current->next;
    }
}
