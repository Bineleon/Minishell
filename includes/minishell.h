/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elilliu <elilliu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 17:40:23 by bineleon          #+#    #+#             */
/*   Updated: 2024/09/27 18:37:13 by elilliu          ###   ########.fr       */
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
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/wait.h>

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
	char				**str;
	char				*cmd;
	char				**args;
	int					input; // a initialiser a STDIN_FILENO
	int					output; // a initialiser a STDOUT_FILENO
	struct s_cmd		*next;
}						t_cmd;

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
	int					fd[2];
	int					pid;
	struct s_cmd		*cmds;
	t_garbage_co		*garbage; // Chained list of all the malloced pointers
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

int						redirection(t_data *data);
void					exec_cmd(t_data *data, t_cmd *cmd, int is_pipe);
void					redir_input(t_data *data, t_cmd *cmd);
void					redir_output(t_data *data, t_cmd *cmd, int is_pipe);
void					execute(t_data *data, t_cmd *cmd);
char					*new_path(char *av, char **env);
char					**all_paths(char **env);
char					**jointab(char **tab, char *str);
void					freetab(char **tab);

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
t_data					*get_data(void);

/* ╔════════════════════════════════════╗ */
/* ║        GARBAGE COLLECTOR           ║ */
/* ╚════════════════════════════════════╝ */

void					*gc_mem(t_mem type, size_t size, void *ptr);
// Exemples :
// gc_mem(MALLOC, sizeof(char *), str)
// gc_mem(FREE, 0, str) ---> free pointer
// gc_mem(FULL_CLEAN, 0, NULL)

#endif
