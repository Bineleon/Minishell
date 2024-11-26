/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                    content                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neleon <neleon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:32:05 by bineleon          #+#    #+#             */
/*   Updated: 2024/09/19 19:19:58 by neleon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_tokens(t_fullcmd *tokens)
{
	while (tokens)
	{
		printf("Token: Type = ");
		if (tokens->type == PIPE)
			printf("PIPE");
		else if (tokens->type == WORD)
			printf("WORD");
		else if (tokens->type == IN)
			printf("IN");
		else if (tokens->type == OUT)
			printf("OUT");
		else if (tokens->type == HEREDOC)
			printf("HEREDOC");
		else if (tokens->type == APPEND)
			printf("APPEND");
		else if (tokens->type == EXPAND)
			printf("EXPAND");
		else if (tokens->type == SQUOTE)
			printf("SQUOTE");
		else if (tokens->type == DQUOTE)
			printf("DQUOTE");
		printf(", token = (%s)\n", tokens->str);
		tokens = tokens->next;
	}
}

t_bool	empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t')
			return (false);
		i++;
	}
	return (true);
}

void	ft_prompt(t_data *data)
{
	char		*prompt;
	t_fullcmd	*tokens;

	tokens = NULL;
	while (1)
	{
		printf(CYAN);
		// if (isatty(STDIN_FILENO) == 1)
		// 	printf("OK\n");
		// else
		// 	printf("NOT OK\n");
		// rl_bind_key ('\t', rl_insert); 
			// Uncomment to insert "\t" with TAB on prompt
		prompt = readline("Minishell>\033[0m ");
		if (!prompt)
		{
			printf(MAGENTA);
			printf("\e[4mCIAO BABY!\e[0m\n");
			printf(RESET);
			free(prompt);
			prompt = NULL;
			gc_mem(FULL_CLEAN, 0, NULL);
			exit(EXIT_SUCCESS);
		}
		// if (*prompt && !prompt[0])
		// 	continue ;
		if (prompt && *prompt)
		{
			if (empty_line(prompt))
				continue ;
			add_history(prompt);
			check_open_quotes(prompt);
			tokens = parse_tokens(prompt, data);
			// print_tokens(tokens);
			if (!check_errors(tokens))
			{
				expand_var(data);
				if (ft_strncmp("export", data->token_fullcmd->str,
						ft_strlen(data->token_fullcmd->str)) == 0)
				{
					init_cmds(data);
					ft_export(data);
				}
				else if (ft_strncmp("unset", data->token_fullcmd->str,
						ft_strlen(data->token_fullcmd->str)) == 0)
				{
					init_cmds(data);
					ft_unset(data);
				}
				else if (ft_strncmp("exit", data->token_fullcmd->str,
						ft_strlen(data->token_fullcmd->str)) == 0)
				{
					init_cmds(data);
					ft_exit(data);
				}
				else if (ft_strncmp("cd", data->token_fullcmd->str,
						ft_strlen(data->token_fullcmd->str)) == 0)
				{
					init_cmds(data);
					ft_cd(data);
				}
				else if (ft_strncmp("pwd", data->token_fullcmd->str,
						ft_strlen(data->token_fullcmd->str)) == 0)
				{
					init_cmds(data);
					ft_pwd(data);
				}
				else if (ft_strncmp("env", data->token_fullcmd->str,
						ft_strlen(data->token_fullcmd->str)) == 0)
				{
					init_cmds(data);
					ft_env(data);
				}
				else
					exec(data);
			}
		}
	}
	free(prompt);
}
