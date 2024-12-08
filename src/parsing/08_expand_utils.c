
#include "../../includes/minishell.h"

t_bool	is_in_dquote(t_fullcmd *token)
{
	if (token->str[0] == DQUOTE && token->str[ft_strlen(token->str) - 1] == DQUOTE)
		return (true);
	return (false);
}

t_bool	is_in_squote(t_fullcmd *token)
{
	if (token->str[0] == SQUOTE && token->str[ft_strlen(token->str) - 1] == SQUOTE)
		return (true);
	return (false);
}

char	*get_env_value(char *var_name, t_env *env_list)
{
	t_env	*current;
	size_t	longest;

	if (!var_name || !env_list)
		return (NULL);
	current = env_list;
	while (current)
	{
		longest = ft_longest(var_name, current->key);
		if (ft_strncmp(current->key, var_name, longest) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

char	*expand_exit_st(char *str, char **result, int i)
{
	t_data	*data;

	data = get_data();
	if (str[i] == '?')
	{
		*result = gc_itoa(data->exit_status);
		data->exit_status = 0;
		return (*result);
	}
	return (NULL);
}

char	*init_result(void)
{
	char	*result;

	result = gc_mem(MALLOC, 1, NULL);
	result[0] = '\0';
	return (result);
}

void	init_var(int *i, int *j, char **tmp, t_fullcmd *token)
{
	*i = 1;
	*j = 0;
	*tmp = gc_mem(MALLOC, ft_strlen(token->str) + 1, NULL);
}

char	*extract_var_name(char *str, int start, int end)
{
	char	*var_name;

	var_name = gc_mem(MALLOC, end - start, NULL);
	ft_strlcpy(var_name, str + start + 1, end - start);
	return (var_name);
}
