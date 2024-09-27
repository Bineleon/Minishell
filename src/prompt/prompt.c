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

void print_tokens(t_fullcmd *tokens)
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

void	ft_prompt(t_data *data)
{
	char	*prompt;
	// char	**cmds;
	// t_lst	*new;

	// new = NULL;
  // cmds = NULL;
	printf(CYAN);
	prompt = readline("Minishell>\033[0m ");
	if (prompt && *prompt)
	{
		add_history(prompt);
    check_open_quotes(prompt);
    t_fullcmd *tokens = parse_tokens(prompt, data);
    print_tokens(tokens);
		// cmds = get_cmds_in_pipe(prompt);
		// add_cmd_to_lst(cmds, &cmd);
		// while((*cmd))
		// {

		// }
	}
	free(prompt);
}
