/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neleon <neleon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 17:40:23 by bineleon          #+#    #+#             */
/*   Updated: 2024/09/10 19:00:16 by neleon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "./constants.h"
#include "../libft/ft_printf/includes/ft_printf.h"
#include "../libft/gnl/get_next_line_bonus.h"
#include "../libft/libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

/*-------------STRUCT----------------*/

typedef struct s_cmd
{
	char			**cmd;
	struct s_cmd	*next;
}					t_cmd;

/*-------------PROMPT----------------*/

void  ft_prompt(void);

/*-------------SIGNAL----------------*/

void	s_handler(int signum, siginfo_t *info, void *context);

#endif
