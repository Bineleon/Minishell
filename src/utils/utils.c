/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neleon <neleon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 21:34:22 by neleon            #+#    #+#             */
/*   Updated: 2024/12/11 17:33:03 by neleon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_bool	is_whitespace(char c)
{
	if ((c == 32 || (c >= 9 && c <= 13)))
		return (true);
	return (false);
}

t_bool	isquote(char c)
{
	if (c == SQUOTE || c == DQUOTE)
		return (true);
	return (false);
}

t_bool	is_separator(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (true);
	return (false);
}

void	free_env_node(t_env *node)
{
	if (node->key)
		gc_mem_env(FREE, 0, node->key);
	if (node->value)
		gc_mem_env(FREE, 0, node->value);
	node = NULL;
	gc_mem_env(FREE, 0, node);
}

char	*gc_strjoin(char const *s1, char const *s2)
{
	char	*join;
	size_t	len_s1;
	size_t	len_s2;

	if (!s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	join = gc_mem(MALLOC, (len_s1 + len_s2 + 1) * sizeof(char), NULL);
	if (!join)
		return (NULL);
	ft_strlcpy(join, s1, (len_s1 + 1));
	ft_strlcat(join, s2, len_s1 + len_s2 + 1);
	return (join);
}

char	*gc_strdup(const char *s1)
{
	size_t	len;
	char	*str;
	int		i;

	i = 0;
	len = ft_strlen(s1);
	str = gc_mem(MALLOC, (len + 1) * sizeof(char), NULL);
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*gc_strdup_env(const char *s1)
{
	size_t	len;
	char	*str;
	int		i;

	i = 0;
	len = ft_strlen(s1);
	str = gc_mem_env(MALLOC, (len + 1) * sizeof(char), NULL);
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static long	ft_nb_size(long nb)
{
	long	size;
	long	sign;

	size = 0;
	sign = 1;
	if (nb < 0)
	{
		sign = -sign;
		nb = -nb;
		size++;
	}
	else if (nb == 0)
		return (1);
	while (nb != 0)
	{
		size++;
		nb /= 10;
	}
	return (size);
}

static void	ft_nbr_to_str(long nb, char *itoa, long size)
{
	if (nb < 0)
	{
		itoa[0] = '-';
		nb *= -1;
	}
	if (nb > 9)
		ft_nbr_to_str(nb / 10, itoa, size - 1);
	itoa[size] = nb % 10 + '0';
}

char	*gc_itoa(int n)
{
	long	nb;
	long	size;
	char	*itoa;

	nb = n;
	size = ft_nb_size(nb);
	itoa = gc_mem(MALLOC, (size + 1), NULL);
	if (!itoa)
		return (NULL);
	if (nb < 0)
		itoa[0] = '-';
	ft_nbr_to_str(nb, itoa, size - 1);
	itoa[size] = '\0';
	return (itoa);
}

void	ciao(int exit_status)
{
	printf(MAGENTA);
	printf("\e[4mCIAO BABY!\e[0m\n");
	printf(RESET);
	gc_mem(FULL_CLEAN, 0, NULL);
	exit(exit_status);
}

long long int	ft_atol(const char *nptr)
{
	int		i;
	long	sign;
	long	res;

	i = 0;
	res = 0;
	sign = 1;
	while ((nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13)))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while ((nptr[i] >= '0' && nptr[i] <= '9'))
	{
		res = res * 10 + nptr[i] - '0';
		i++;
	}
	return (res * sign);
}


static void	free_tokens(t_data *data)
{
	t_fullcmd	*tmp;

	tmp = NULL;
	if (!data->token_fullcmd)
		return ;
	while (data->token_fullcmd->next)
	{
		tmp = data->token_fullcmd;
		if (tmp->str) 
			gc_mem(FREE, 0, tmp->str);
		data->token_fullcmd = data->token_fullcmd->next;
		// if (tmp)
		// 	free(tmp);
	}
	if (data->token_fullcmd)
	{
		if (data->token_fullcmd->str)
			gc_mem(FREE, 0, data->token_fullcmd->str);
		gc_mem(FREE, 0, data->token_fullcmd);
	}
	return ;
}

static void	free_redi(t_cmd *cmd)
{
	t_redir	*tmp;

	tmp = NULL;
	if (!cmd->redir)
		return ;
	while (cmd->redir->next)
	{
		tmp = cmd->redir;
		if (tmp->file_name)
			gc_mem(FREE, 0, tmp->file_name);
		cmd->redir = cmd->redir->next;
		free(tmp);
	}
	if (cmd->redir)
	{
		if (cmd->redir->file_name)
			gc_mem(FREE, 0, cmd->redir->file_name);
		gc_mem(FREE, 0, cmd->redir);
	}
	return ;
}

static void	free_args(char **args)
{
	int	i;

	i = 0;
	if (!args)
		return ;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	gc_mem(FREE, 0, args);
}

static void	free_cmds(t_data *data)
{
	t_cmd	*tmp;

	tmp = NULL;
	while (data->cmds->next)
	{
		tmp = data->cmds;
		if (data->cmds->redir)
			free_redi(data->cmds);
		if (data->cmds->cmd)
			gc_mem(FREE, 0, data->cmds->cmd);
		if (data->cmds->args)
			free_args(data->cmds->args);
		data->cmds = data->cmds->next;
		free(tmp);
	}
	if (data->cmds->redir)
		free_redi(data->cmds);
	if (data->cmds->cmd)
	{
		free_args(data->cmds->args);
		gc_mem(FREE, 0, data->cmds->cmd);
	}
	gc_mem(FREE, 0, data->cmds);
	return ;
}

void	free_post_prompt(t_data *data)
{
	if (data->cmds)
		free_cmds(data);
	if (data->token_fullcmd)
		free_tokens(data);
	if (data->delim)
		gc_mem(FREE, 0, data->delim);
}