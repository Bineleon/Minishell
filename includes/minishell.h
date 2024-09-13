/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neleon <neleon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 17:40:23 by bineleon          #+#    #+#             */
/*   Updated: 2024/09/13 18:00:03 by neleon           ###   ########.fr       */
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

typedef struct s_data
{
	char			**envp_cpy;
	size_t			cmds_count;
}					t_data;

typedef struct s_cmd
{
	// char			*cmd;
	char			**args;
	char			**redi;
}					t_cmd;

typedef struct s_lst
{
	t_cmd			*cmd;
	struct s_lst	*next;
}					t_lst;

typedef enum e_bool
{
	false,
	true
}					t_bool;

/*-------------PARSING---------------*/

char				**cpy_envp(char **envp);
t_data				*init_and_alloc_data(char **envp);
char	**get_cmds_in_pipe(char *prompt);
void	add_cmd_to_lst(char **cmds, t_lst *lst);


/*-------------PROMPT----------------*/

void				ft_prompt(t_lst **cmd);

/*-------------SIGNAL----------------*/

/*-------------UTILS-----------------*/

t_lst				*ft_lstnew(t_cmd *cmd);
void				ft_lstadd_back(t_lst **lst, t_lst *new);
void				ft_print_lst(t_lst *cmd);

#endif
