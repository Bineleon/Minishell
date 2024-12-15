/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bineleon <neleon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:23:30 by neleon            #+#    #+#             */
/*   Updated: 2024/12/15 11:16:30 by bineleon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// void	print_tokens(t_fullcmd *tokens)
// {
// 	t_fullcmd	*current;

// 	current = tokens;
// 	while (current)
// 	{
// 		printf("Token: Type = ");
// 		if (current->type == PIPE)
// 			printf("PIPE");
// 		else if (current->type == WORD)
// 			printf("WORD");
// 		else if (current->type == IN)
// 			printf("IN");
// 		else if (current->type == OUT)
// 			printf("OUT");
// 		else if (current->type == HEREDOC)
// 			printf("HEREDOC");
// 		else if (current->type == APPEND)
// 			printf("APPEND");
// 		else if (current->type == EXPAND)
// 			printf("EXPAND");
// 		else if (current->type == SQUOTE)
// 			printf("SQUOTE");
// 		else if (current->type == DQUOTE)
// 			printf("DQUOTE");
// 		printf(", token = (%s)\n", current->str);
// 		current = current->next;
// 	}
// }

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

void	handle_ctrl_d(t_data *data, char *prompt)
{
	printf(MAGENTA);
	printf("\e[4mCIAO BABY!\e[0m\n");
	printf(RESET);
	gc_mem(FULL_CLEAN, 0, NULL);
	gc_mem_env(FULL_CLEAN, 0, NULL);
	free(prompt);
	prompt = NULL;
	rl_clear_history();
	exit(data->exit_status);
}

void	ft_prompt(t_data *data)
{
	char		*prompt;
	t_fullcmd	*tokens;

	tokens = NULL;
	while (1)
	{
		handle_signals();
		printf(CYAN);
		signal(SIGQUIT, SIG_IGN);
		prompt = readline("Minishell> \033[0m");
		signal(SIGQUIT, &handle_sigquit2);
		if (!prompt)
			handle_ctrl_d(data, prompt);
		if (prompt && *prompt)
		{
			if (empty_line(prompt))
				continue ;
			add_history(prompt);
			if (check_open_quotes(prompt))
			{
				error_mess("error", "open quote\n");
				continue ;
			}
			tokens = parse_tokens(prompt, data);
			// print_tokens(tokens);
			if (!check_errors(tokens))
			{
				expand_var(data);
				find_cmds(data);
				// print_tokens(tokens);
				exec(data);
			}
		}
		free(prompt);
    prompt = NULL;
	}
	gc_mem_env(FULL_CLEAN, 0, NULL);
}
