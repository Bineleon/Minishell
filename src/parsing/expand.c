#include "../../includes/minishell.h"

t_bool    is_in_dquote(t_fullcmd *token)
{
    if (token->str[0] == DQUOTE && token->str[ft_strlen(token->str) - 1] == DQUOTE)
        return (true);
    return (false);
}

char *get_env_value(char *var_name, t_env *env_list)
{
    t_env *current = env_list;

    while (current)
    {
        if (ft_strncmp (current->key, var_name, ft_strlen(var_name)) == 0)
            return (current->value);
        current = current->next;
    }
    return (NULL);
}

char *expand_token_value(char *str, t_env *env_list)
{
    char *var_name;
    char *var_value;
    char *result;

    var_name = str + 1;
    var_value = get_env_value(var_name, env_list);
    if (var_value)
    {
        result =  gc_mem(MALLOC, ft_strlen(var_value) + 1, NULL);
        ft_strlcpy(result, var_value, ft_strlen(var_value) + 1);
        return (result);
    }
    return (NULL);
}

void expand_var(t_data *data)
{
    t_fullcmd *current;

    current = data->token_fullcmd;
    while (current)
    {
        if (current->type == EXPAND)
            handle_expand(current, data->envp_cpy);
        // else if (current->type == WORD && is_in_dquote(current))
        //     handle_dquote_exp(current, data->envp_cpy);
        current = current->next;
    }
}

void handle_expand(t_fullcmd *token, t_env *env_list)
{
    char *exp_value;

    exp_value = expand_token_value(token->str, env_list);
    gc_mem(FREE, 0, token->str);
    if (exp_value)
    {
        token->str = gc_mem(MALLOC, ft_strlen(exp_value) + 1, NULL);
        ft_strlcpy(token->str, exp_value, ft_strlen(exp_value) + 1);
    }
    else
    {
        token->str = gc_mem(MALLOC, 1, NULL);
        token->str[0] = '\0';
    }
    token->type = WORD;
}

// void handle_dquote_exp(t_fullcmd *token, t_env *env_list)
// {
//     char *new_str;
//     int i = 0;
//     int j = 0;

//     new_str = gc_mem(MALLOC, ft_strlen(token->str) + 1, NULL);
//     while (token->str[i])
//     {
//         if (token->str[i] == '$')
//             expand_in_quotes(token, env_list, new_str, &i, &j);
//         else
//         {
//             new_str[j++] = token->str[i++];
//         }
//     }
//     new_str[j] = '\0';
//     gc_mem(FREE, 0, token->str);
//     token->str = new_str;
// }

// void expand_in_quotes(t_data *data, char *new_str, int *i, int *j)
// {
//     char *start;
//     char *exp_var;
//     int var_len;

//     start = data->token->str + *i;
//     exp_var = expand_token_value(start, data->envp_cpy);
//     if (exp_var)
//     {
//         var_len = ft_strlen(exp_var);
//         new_str = gc_mem(MALLOC, ft_strlen(new_str) + var_len + 1, NULL);
//         ft_strlcpy(new_str + *j, exp_var, var_len + 1);
//         *j += var_len;
//         *i += ft_strlen(start);
//     }
// }

// void    replace_env(t_fullcmd *token)
// {
//     t_fullcmd   *current;

//     current = token;
//     while(current)
//     {
//         if (current->type == WORD && !is_in_squote(current))
//         {

//         }
//         current = current->next;
//     }
// }
