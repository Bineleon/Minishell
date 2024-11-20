
#include "../../includes/minishell.h"

t_bool   is_valid_key(char  *key)
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

static void    update_env(t_env **env, char *key, char *value, int equal)
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
        curr = curr->next;
    }
    new_node = gc_mem(MALLOC, sizeof(t_env), NULL);
    init_env(new_node);
    new_node->key = gc_strdup(key);
    if (value)
        new_node->value = gc_strdup(value);
    if (!equal)
        new_node->equal = false;
    new_node->next = *env;
    *env = new_node;

}

static size_t	get_env_size(t_env *env)
{
	size_t	env_size;
  t_env   *curr;

  curr = env;
	env_size = 0;
	while (curr)
  {
		  env_size++;
      curr = curr->next;
  }
	return (env_size);
}

t_env    **lst_to_arr(t_env *env)
{
    t_env    **arr;
    t_env   *curr;
    size_t  env_size;
    int     i;

    i = 0;
    env_size = get_env_size(env);
    arr = gc_mem(MALLOC, (env_size * sizeof(t_env)) + 1, NULL);
    curr = env;
    while (curr)
    {
        arr[i] = gc_mem(MALLOC, sizeof(t_env), NULL);
        init_env(arr[i]);
        arr[i]->key = gc_strdup(curr->key);
        if (curr->value)
            arr[i]->value = gc_strdup(curr->value);
        arr[i]->equal = curr->equal;
        arr[i]->next = NULL;
        curr = curr->next;
        i++;
    }
    arr[i] = NULL;
    return (arr);
}

void    swap_env(t_env *a, t_env *b)
{
    t_env  tmp;

    tmp = *a;
    *a = *b;
    *b = tmp;
}

int	ft_longest(char *s1, char *s2)
{
    int len_1;
    int len_2;

    len_1 = ft_strlen(s1);
    len_2 = ft_strlen(s2);
    if (len_1 > len_2)
        return (len_1);
    return (len_2);
}

void    sort_env(t_env **arr)
{
    int i;
    int j;

    i = 0;
    while(arr[i + 1])
    {
        j = i + 1;
        while(arr[j])
        {
            if (ft_strncmp(arr[i]->key, arr[j]->key, ft_longest(arr[i]->key, arr[j]->key)) > 0)
                swap_env(arr[i], arr[j]);
            j++;
        }
        i++;
    }
}

void print_export(t_env **arr)
{
    int i;

    i = 0;
    while (arr[i])
    {
        if (arr[i]->value)
        {
            printf("export %s=\"%s\"\n", arr[i]->key, arr[i]->value);
        }
        else if (arr[i]->equal == false)
            printf("export %s\n", arr[i]->key);
        else if (arr[i]->equal && !arr[i]->value)
        {
            printf("export %s=\"\"\n", arr[i]->key);
        }
        i++;
    }
}

void    sub_export(t_data *data)
{
    char    *equal;
    char    *key;
    char    *value;
    int     i;

    i = 1;
    equal = NULL;
    key = NULL;
    value = NULL;
    while(data->cmds->args[i])
    {
        equal = ft_strchr(data->cmds->args[i], '=');
        if(!equal)
        {
            key = data->cmds->args[i];
            if (!is_valid_key(key))
            {
                printf("export: `%s': not a valid identifier\n", key);
                data->exit_status = 1;
            }
            else
            {
                update_env(&data->envp_cpy, key, NULL, 0);
                data->exit_status = 0;
            }
        }
        else
        {
            *equal = '\0';
            key = data->cmds->args[i];
            value = equal + 1;
            if (!is_valid_key(key))
            {
                printf("export: `%s': not a valid identifier\n", key);
                data->exit_status = 1;
            }
            else
            {
                update_env(&data->envp_cpy, key, value, 1);
                data->exit_status = 0;
            }
            *equal = '=';
        }
        i++;
    }
}

void    ft_export(t_data *data)
{
    t_env    **sorted_env;

    sorted_env = lst_to_arr(data->envp_cpy);
    sort_env(sorted_env);
    if (!data->cmds->args[1])
        print_export(sorted_env);
    sub_export(data);
}
