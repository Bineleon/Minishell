#include "../../includes/minishell.h"

t_bool    is_in_dquote(t_fullcmd *token)
{
    if (token->str[0] == DQUOTE && token->str[ft_strlen(token->str) - 1] == DQUOTE)
        return (true);
    return (false);
}

t_bool    is_in_squote(t_fullcmd *token)
{
    if (token->str[0] == SQUOTE && token->str[ft_strlen(token->str) - 1] == SQUOTE)
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

char *expand_token(char *str, t_env *env_list)
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

char *expand_in_dquote(char *str, t_env *env_list)
{
    char *var_name;
    char *var_value;
    char *result;
    int   i;

    i = 1;
    while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
        i++;
    var_name = gc_mem(MALLOC, i, NULL);
    ft_strlcpy(var_name, str + 1, i);
    var_value = get_env_value(var_name, env_list);
    gc_mem(FREE, 0, var_name);
    if (var_value)
    {
        result = gc_mem(MALLOC, ft_strlen(var_value) + 1, NULL);
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
        else if (current->type == WORD && is_in_dquote(current))
            handle_dquote_exp(current, data->envp_cpy);
        else if (current->type == WORD && is_in_squote(current))
            handle_squote_exp(current);
        current = current->next;
    }
}

void handle_expand(t_fullcmd *token, t_env *env_list)
{
    char *exp_value;

    exp_value = expand_token(token->str, env_list);
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

void handle_squote_exp(t_fullcmd *token)
{
    char    *tmp;
    char    *result;
    int     i;
    int     j;

    i = 1;
    j = 0;
    tmp = gc_mem(MALLOC, ft_strlen(token->str) + 1, NULL);
    result = gc_mem(MALLOC, 1, NULL);
    result[0] = '\0';
    while (token->str[i] && token->str[i] != SQUOTE)
        tmp[j++] = token->str[i++];
    tmp[j] = '\0';
    result = gc_strjoin(result, tmp);
    gc_mem(FREE, 0, token->str);
    token->str = result;
    gc_mem(FREE, 0, tmp);
}

void handle_dquote_exp(t_fullcmd *token, t_env *env_list)
{
    char    *tmp;
    char    *result;
    char    *env_value;
    int     i;
    int     j;

    i = 1;
    j = 0;
    tmp = gc_mem(MALLOC, ft_strlen(token->str) + 1, NULL);
    result = gc_mem(MALLOC, 1, NULL);
    while (token->str[i] && token->str[i] != DQUOTE)
    {
        if (token->str[i] == EXPAND && token->str[i + 1] && ft_isalnum(token->str[i + 1]))
        {
            tmp[j] = '\0';
            result = gc_strjoin(result, tmp);
            env_value = expand_in_dquote(token->str + i, env_list);
            if (env_value)
                result = gc_strjoin(result, env_value);
            i++;
            while (token->str[i] && (ft_isalnum(token->str[i]) || token->str[i] == '_'))
                i++;
            j = 0;
        }
        else
            tmp[j++] = token->str[i++];
    }
    tmp[j] = '\0';
    result = gc_strjoin(result, tmp);
    gc_mem(FREE, 0, token->str);
    token->str = result;
}
