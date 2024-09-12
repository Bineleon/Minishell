/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neleon <neleon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 17:40:23 by bineleon          #+#    #+#             */
/*   Updated: 2024/09/12 16:55:46 by neleon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/ft_printf/includes/ft_printf.h"
# include "../libft/gnl/get_next_line_bonus.h"
# include "../libft/libft/libft.h"
# include "./constants.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>

/*-------------STRUCT----------------*/

typedef struct s_lst
{
	char			**cmd;
	struct s_lst	*next;
}					t_lst;

typedef struct s_cmd
{
	char			*cmd;
	char			**args;
	char			**redi;
}					t_cmd;

typedef enum e_bool
{
	false,
	true
}					t_bool;

/*-------------PARSING---------------*/

/*-------------PROMPT----------------*/

void				ft_prompt(t_lst **cmd);

/*-------------SIGNAL----------------*/

/*-------------UTILS-----------------*/

t_lst				*ft_lstnew(char **cmd);
void				ft_lstadd_back(t_lst **lst, t_lst *new);
void				ft_print_lst(t_lst *cmd);

#endif
