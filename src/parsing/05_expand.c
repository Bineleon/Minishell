#include "../../includes/minishell.h"

int	process_word(char *str, int i, char **result)
{
	int		start;
	char	*text;

	start = i;
	while (str[i] && str[i] != '$')
		i++;
	text = gc_mem(MALLOC, i - start + 1, NULL);
	ft_strlcpy(text, str + start, i - start + 1);
	*result = gc_strjoin(*result, text);
	gc_mem(FREE, 0, text);
	return (i);
}

int	process_exp(char *str, int i, t_env *env_list, char **result)
{
	int		start;
	char	*var_name;
	char	*exp_val;

	start = i;
	i++;
	if (str[i] == '?')
	{
		*result = expand_exit_st(str, result, i);
		i++;
		return (i);
	}
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	if (i > start + 1)
	{
		var_name = extract_var_name(str, start, i);
		exp_val = get_env_value(var_name, env_list);
		gc_mem(FREE, 0, var_name);
		if (exp_val)
			*result = gc_strjoin(*result, exp_val);
	}
	else
		*result = gc_strjoin(*result, "$");
	return (i);
}
