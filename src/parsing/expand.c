/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bineleon <neleon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 18:56:35 by neleon            #+#    #+#             */
/*   Updated: 2024/11/19 18:13:10 by bineleon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_bool	is_in_dquote(t_fullcmd *token)
{
	if (token->str[0] == DQUOTE && token->str[ft_strlen(token->str)
		- 1] == DQUOTE)
		return (true);
	return (false);
}

t_bool	is_in_squote(t_fullcmd *token)
{
	if (token->str[0] == SQUOTE && token->str[ft_strlen(token->str)
		- 1] == SQUOTE)
		return (true);
	return (false);
}

char	*get_env_value(char *var_name, t_env *env_list)
{
	t_env	*current;

	current = env_list;
	while (current)
	{
		if (ft_strncmp(current->key, var_name, ft_strlen(var_name)) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

char	*expand_exit_st(char *str, char **result, int i)
{
	t_data	*data;

	data = get_data();
	printf("exit_status : %d\n", data->exit_status);
	if (str[i] == '?')
	{
		*result = gc_itoa(data->exit_status);
		printf("exit 2 : %d\n", data->exit_status);
		return (*result);
	}
	return (NULL);
}

char	*expand_token(char *str, t_env *env_list)
{
	char	*var_name;
	char	*var_value;
	char	*result;

	result = NULL;
	result = expand_exit_st(str, &result, 1);
	if (result)
		return (result);
	var_name = str + 1;
	var_value = get_env_value(var_name, env_list);
	if (var_value)
	{
		result = gc_mem(MALLOC, ft_strlen(var_value) + 1, NULL);
		ft_strlcpy(result, var_value, ft_strlen(var_value) + 1);
		return (result);
	}
	return (NULL);
}

char	*expand_in_dquote(char *str, t_env *env_list)
{
	char	*var_name;
	char	*var_value;
	char	*result;
	int		i;

	i = 1;
	result = NULL;
	result = expand_exit_st(str, &result, i);
	if (result)
		return (result);
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

void	expand_var(t_data *data)
{
	t_fullcmd	*current;

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

char	*init_result(void)
{
	char	*result;

	result = gc_mem(MALLOC, 1, NULL);
	result[0] = '\0';
	return (result);
}

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

char	*extract_var_name(char *str, int start, int end)
{
	char	*var_name;

	var_name = gc_mem(MALLOC, end - start, NULL);
	ft_strlcpy(var_name, str + start + 1, end - start);
	return (var_name);
}

int	process_exp(char *str, int i, t_env *env_list, char **result)
{
	int		start;
	char	*var_name;
	char	*expanded_value;

	start = i;
	i++;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	if (i > start + 1)
	{
		var_name = extract_var_name(str, start, i);
		expanded_value = get_env_value(var_name, env_list);
		gc_mem(FREE, 0, var_name);
		if (expanded_value)
			*result = gc_strjoin(*result, expanded_value);
	}
	else
		*result = gc_strjoin(*result, "$");
	return (i);
}

void	handle_expand(t_fullcmd *token, t_env *env_list)
{
	char	*result;
	int		i;

	result = init_result();
	i = 0;
	while (token->str[i])
	{
		if (token->str[i] == '$')
			i = process_exp(token->str, i, env_list, &result);
		else
			i = process_word(token->str, i, &result);
	}
	gc_mem(FREE, 0, token->str);
	token->str = result;
	token->type = WORD;
}

// void	handle_expand(t_fullcmd *token, t_env *env_list)
// {
// 	char	*expanded_value;
// 	char	*result;
//   char  *var_name;
//   char *text;
// 	int		i;
// 	int		start;

// 	result = gc_mem(MALLOC, 1, NULL);
// 	result[0] = '\0';
// 	i = 0;
// 	while (token->str[i])
// 	{
// 		if (token->str[i] == '$')
// 		{
// 			start = i;
// 			i++;
// 			while (token->str[i] && (ft_isalnum(token->str[i]) || token->str[i] == '_'))
// 				i++;
// 			if (i > start + 1)
// 			{
// 				var_name = gc_mem(MALLOC, i - start, NULL);
// 				ft_strlcpy(var_name, token->str + start + 1, i - start);
// 				expanded_value = get_env_value(var_name, env_list);
// 				gc_mem(FREE, 0, var_name);
// 				if (expanded_value)
// 					result = gc_strjoin(result, expanded_value);
// 			}
// 			else
// 				result = gc_strjoin(result, "$");
// 		}
// 		else
// 		{
// 			start = i;
// 			while (token->str[i] && token->str[i] != '$')
// 				i++;
// 			text = gc_mem(MALLOC, i - start + 1, NULL);
// 			ft_strlcpy(text, token->str + start, i - start + 1);
// 			result = gc_strjoin(result, text);
// 			gc_mem(FREE, 0, text);
// 		}
// 	}
// 	gc_mem(FREE, 0, token->str);
// 	token->str = result;
// 	token->type = WORD;
// }

// void	handle_expand(t_fullcmd *token, t_env *env_list)
// {
// 	char	*exp_value;

// 	exp_value = expand_token(token->str, env_list);
// 	gc_mem(FREE, 0, token->str);
// 	if (exp_value)
// 	{
// 		token->str = gc_mem(MALLOC, ft_strlen(exp_value) + 1, NULL);
// 		ft_strlcpy(token->str, exp_value, ft_strlen(exp_value) + 1);
// 	}
// 	else
// 	{
// 		token->str = gc_mem(MALLOC, 1, NULL);
// 		token->str[0] = '\0';
// 	}
// 	token->type = WORD;
// }

void	handle_squote_exp(t_fullcmd *token)
{
	char	*tmp;
	char	*result;
	int		i;
	int		j;

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

void	handle_dquote_exp(t_fullcmd *token, t_env *env_list)
{
	char	*tmp;
	char	*result;
	char	*env_value;
	int		i;
	int		j;

	i = 1;
	j = 0;
	tmp = gc_mem(MALLOC, ft_strlen(token->str) + 1, NULL);
	result = gc_mem(MALLOC, 1, NULL);
	while (token->str[i] && token->str[i] != DQUOTE)
	{
		if (token->str[i] == EXPAND && token->str[i + 1]
			&& ft_isalnum(token->str[i + 1]))
		{
			tmp[j] = '\0';
			result = gc_strjoin(result, tmp);
			env_value = expand_in_dquote(token->str + i, env_list);
			if (env_value)
				result = gc_strjoin(result, env_value);
			i++;
			while (token->str[i] && (ft_isalnum(token->str[i])
					|| token->str[i] == '_'))
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
