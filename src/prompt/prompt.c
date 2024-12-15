/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neleon <neleon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:23:30 by neleon            #+#    #+#             */
/*   Updated: 2024/12/15 17:21:40 by neleon           ###   ########.fr       */
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

void	handle_prompt_signals(void)
{
	handle_signals();
	signal(SIGQUIT, SIG_IGN);
}

char	*read_prompt(void)
{
	char	*prompt;

	printf(CYAN);
	prompt = readline("Minishell> \033[0m");
	signal(SIGQUIT, &handle_sigquit2);
	return (prompt);
}

void	process_prompt(char *prompt, t_data *data)
{
	t_fullcmd	*tokens;

	tokens = parse_tokens(prompt, data);
	if (!check_errors(tokens))
	{
		expand_var(data);
		find_cmds(data);
	}
}

void	ft_prompt(t_data *data)
{
	char	*prompt;

	while (1)
	{
		handle_prompt_signals();
		prompt = read_prompt();
		if (!prompt)
		{
			handle_ctrl_d(data, prompt);
			continue ;
		}
		if (*prompt && !empty_line(prompt))
		{
			add_history(prompt);
			if (check_open_quotes(prompt))
				error_mess("error", "open quote\n");
			else
			{
				process_prompt(prompt, data);
				exec(data);
			}
		}
		free(prompt);
	}
	gc_mem_env(FULL_CLEAN, 0, NULL);
}

// void	ft_prompt(t_data *data)
// {
// 	char		*prompt;
// 	t_fullcmd	*tokens;

// 	tokens = NULL;
// 	while (1)
// 	{
// 		handle_signals();
// 		printf(CYAN);
// 		signal(SIGQUIT, SIG_IGN);
// 		prompt = readline("Minishell> \033[0m");
// 		signal(SIGQUIT, &handle_sigquit2);
// 		if (!prompt)
// 			handle_ctrl_d(data, prompt);
// 		if (prompt && *prompt)
// 		{
// 			if (empty_line(prompt))
// 				continue ;
// 			add_history(prompt);
// 			if (check_open_quotes(prompt))
// 			{
// 				error_mess("error", "open quote\n");
// 				continue ;
// 			}
// 			tokens = parse_tokens(prompt, data);
// 			if (!check_errors(tokens))
// 			{
// 				expand_var(data);
// 				find_cmds(data);
// 				exec(data);
// 			}
// 		}
// 		free(prompt);
// 	}
// 	gc_mem_env(FULL_CLEAN, 0, NULL);
// }
