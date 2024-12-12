/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neleon <neleon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:13:26 by neleon            #+#    #+#             */
/*   Updated: 2024/12/12 16:37:20 by neleon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*init_res2(void)
{
	char	*result;

	result = gc_mem(MALLOC, 1, NULL);
	result[0] = '\0';
	return (result);
}

int	append_txt(char **result, char *tmp, char *str, int i)
{
	int	j;

	j = 0;
	while (str[i] && str[i] != DQUOTE && str[i] != '$')
	{
		tmp[j] = str[i];
		j++;
		i++;
	}
	tmp[j] = '\0';
	*result = gc_strjoin(*result, tmp);
	return (i);
}

char	*extract_var_name2(char *str, int start, int end)
{
	char	*var_name;

	var_name = gc_mem(MALLOC, end - start + 1, NULL);
	ft_strlcpy(var_name, &str[start], end - start + 1);
	return (var_name);
}

char	*expand_exit_status(void)
{
	t_data	*data;
	char	*exit_status;

	data = get_data();
	exit_status = gc_itoa(data->exit_status);
	data->exit_status = 0;
	return (exit_status);
}

int	process_env_var(char **result, char *str, int i, t_env *env_list)
{
	int		start;
	char	*exit_status;
	char	*var_name;
	char	*env_value;

	start = ++i;
	if (str[i] == '?')
	{
		exit_status = expand_exit_status();
		*result = gc_strjoin(*result, exit_status);
		gc_mem(FREE, 0, exit_status);
		return (i + 1);
	}
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	var_name = extract_var_name2(str, start, i);
	env_value = get_env_value(var_name, env_list);
	gc_mem(FREE, 0, var_name);
	if (env_value)
		*result = gc_strjoin(*result, env_value);
	return (i);
}

void	handle_dquote_exp(t_fullcmd *token, t_env *env_list)
{
	char	*result;
	char	*tmp;
	int		i;

	i = 1;
	result = init_result();
	tmp = gc_mem(MALLOC, ft_strlen(token->str) + 1, NULL);
	while (token->str[i] && token->str[i] != DQUOTE)
	{
		i = append_txt(&result, tmp, token->str, i);
		if (token->str[i] == '$')
			i = process_env_var(&result, token->str, i, env_list);
	}
	gc_mem(FREE, 0, tmp);
	gc_mem(FREE, 0, token->str);
	token->str = result;
}

// void handle_dquote_exp(t_fullcmd *token, t_env *env_list)
// {
//     char *result;
//     int i;
//     int j;
//     char *tmp;
//     char *env_value;

//     i = 1;
//     result = gc_mem(MALLOC, 1, NULL);
//     result[0] = '\0';
//     tmp = gc_mem(MALLOC, ft_strlen(token->str) + 1, NULL);

//     while (token->str[i] && token->str[i] != DQUOTE)
//     {
//         j = 0;
//         while (token->str[i] && token->str[i] != DQUOTE
	&& token->str[i] != '$')
//             tmp[j++] = token->str[i++];
//         tmp[j] = '\0';
//         result = gc_strjoin(result, tmp);

//         if (token->str[i] == '$')
//         {
//             int start = ++i;
//             while (token->str[i] && (ft_isalnum(token->str[i])
		|| token->str[i] == '_'))
//                 i++;
//             char *var_name = gc_mem(MALLOC, i - start + 1, NULL);
//             ft_strlcpy(var_name, &token->str[start], i - start + 1);
//             env_value = get_env_value(var_name, env_list);
//             gc_mem(FREE, 0, var_name);
//             if (env_value)
//                 result = gc_strjoin(result, env_value);
//         }
//     }
//     gc_mem(FREE, 0, tmp);
//     gc_mem(FREE, 0, token->str);
//     token->str = result;
// }
