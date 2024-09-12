/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bineleon <neleon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 17:40:23 by bineleon          #+#    #+#             */
/*   Updated: 2024/09/12 15:10:50 by bineleon         ###   ########.fr       */
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

typedef struct s_lst
{
	char			**cmd;
	struct s_lst	*next;
}					t_lst;

typedef enum e_bool
{
    false,
    true
}   t_bool;

/*-------------PARSING---------------*/



/*-------------PROMPT----------------*/

void  ft_prompt(void);

/*-------------SIGNAL----------------*/

t_lst	*ft_lstnew(char **cmd);
void	ft_lstadd_back(t_lst **lst, t_lst *new);

/*-------------UTILS----------------*/




#endif
