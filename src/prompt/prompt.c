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
#include <sys/ioctl.h>

void	print_tokens(t_fullcmd *tokens)
{
	t_fullcmd	*current;

	current = tokens;
	while (current)
	{
		printf("Token: Type = ");
		if (current->type == PIPE)
			printf("PIPE");
		else if (current->type == WORD)
			printf("WORD");
		else if (current->type == IN)
			printf("IN");
		else if (current->type == OUT)
			printf("OUT");
		else if (current->type == HEREDOC)
			printf("HEREDOC");
		else if (current->type == APPEND)
			printf("APPEND");
		else if (current->type == EXPAND)
			printf("EXPAND");
		else if (current->type == SQUOTE)
			printf("SQUOTE");
		else if (current->type == DQUOTE)
			printf("DQUOTE");
		printf(", token = (%s)\n", current->str);
		current = current->next;
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
		// printf(CYAN);
		// if (isatty(STDIN_FILENO) == 1)
		// 	printf("OK\n");
		// else
		// 	printf("NOT OK\n");
		// rl_bind_key('\t', rl_insert);
		// Uncomment to insert "\t" with TAB on prompt
		handle_signals();
		prompt = readline("Minishell> ");
		if (!prompt)
		{
			printf(MAGENTA);
			printf("\e[4mCIAO BABY!\e[0m\n");
			printf(RESET);
			free(prompt);
			prompt = NULL;
			rl_clear_history();
			gc_mem(FULL_CLEAN, 0, NULL);
			exit(data->exit_status);
		}
		// if (*prompt && !prompt[0])
		// 	continue ;
		if (prompt && *prompt)
		{
			if (empty_line(prompt))
				continue ;
			add_history(prompt);
			if (check_open_quotes(prompt))
			{
				error_mess("error", "open quote");
				continue ;
			}
			tokens = parse_tokens(prompt, data);
			// print_tokens(tokens);
			// printf("\n");
			if (!check_errors(tokens))
			{
				expand_var(data);
				find_cmds(data);
				// print_tokens(tokens);
				// printf("\n");
				// print_tokens(data->token_fullcmd);
				exec(data);
			}
		}
		free(prompt);
	}
}
