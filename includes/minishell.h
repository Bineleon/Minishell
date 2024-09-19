/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bineleon <neleon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 17:40:23 by bineleon          #+#    #+#             */
/*   Updated: 2024/09/19 18:42:18 by bineleon         ###   ########.fr       */
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

/* ╔════════════════════════════════════╗ */
/* ║             STRUCTURES             ║ */
/* ╚════════════════════════════════════╝ */

typedef enum e_token
{
	WORD = -1,
	PIPE = '|',
	IN = '<',
	OUT = '>',
	EXPAND = '$',
	SQUOTE = '\'',
	DQUOTE = '\"',
	SPC = ' ',
}						t_token;

typedef struct s_cmd
{
	// char			*cmd;
	char				**args;
	char				**redi;
}						t_cmd;

typedef struct s_lst
{
	t_cmd				*cmd;
	struct s_lst		*next;
}						t_lst;

typedef struct s_garbage_co
{
	void				*ptr;
	struct s_garbage_co	*next;
}						t_garbage_co;

typedef enum e_mem
{
	MALLOC,
	FREE,
    FULL_CLEAN
}						t_mem;

typedef enum e_bool
{
	false,
	true
}						t_bool;

typedef struct s_data
{
	char				**envp_cpy;
	size_t				cmds_count;
  void         *ptr1;
  void         *ptr2;
  void         *ptr3;
    t_garbage_co        *garbage;    // Chained list of all the malloced pointers
}						t_data;

/* ╔════════════════════════════════════╗ */
/* ║              PARSING               ║ */
/* ╚════════════════════════════════════╝ */

char					**cpy_envp(char **envp);
t_data					*init_and_alloc_data(char **envp);
char					**get_cmds_in_pipe(char *prompt);
void					add_cmd_to_lst(char **cmds, t_lst *lst);

/* ╔════════════════════════════════════╗ */
/* ║               EXEC                 ║ */
/* ╚════════════════════════════════════╝ */



/* ╔════════════════════════════════════╗ */
/* ║              PROMPT                ║ */
/* ╚════════════════════════════════════╝ */

void					ft_prompt(t_lst **cmd);

/* ╔════════════════════════════════════╗ */
/* ║              SIGNALS               ║ */
/* ╚════════════════════════════════════╝ */



/* ╔════════════════════════════════════╗ */
/* ║               UTILS                ║ */
/* ╚════════════════════════════════════╝ */

t_lst					*ft_lstnew(t_cmd *cmd);
void					ft_lstadd_back(t_lst **lst, t_lst *new);
void					ft_print_lst(t_lst *cmd);
t_data                  *get_data(void);

/* ╔════════════════════════════════════╗ */
/* ║        GARBAGE COLLECTOR           ║ */
/* ╚════════════════════════════════════╝ */

void          *gc_mem(t_mem type, size_t size, void *ptr);
// Exemples :
  // gc_mem(MALLOC, sizeof(char *), str)
  // gc_mem(FREE, 0, str) ---> free pointer
  // gc_mem(FULL_CLEAN, 0, NULL)

#endif
