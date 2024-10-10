/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bineleon <neleon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 17:40:23 by bineleon          #+#    #+#             */
/*   Updated: 2024/10/03 16:06:56 by bineleon         ###   ########.fr       */
*/
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
/* ║                ENUM                ║ */
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
  HEREDOC = -2,
  APPEND = -3
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

/* ╔════════════════════════════════════╗ */
/* ║             STRUCTURES             ║ */
/* ╚════════════════════════════════════╝ */

typedef struct s_fullcmd
{
	char		    	*str;
	t_token				type;
  struct s_fullcmd *next;
}						t_fullcmd;

typedef struct s_cmd
{
	t_fullcmd			*full_cmd;
	char				**str;
	char				*cmd;
	char				**args;
	int					input; // a initialiser a STDIN_FILENO
	int					output; // a initialiser a STDOUT_FILENO
	struct s_cmd		*next;
}						t_cmd;

typedef struct s_garbage_co
{
	void				        *ptr;
	struct s_garbage_co	*next;
}						t_garbage_co;

typedef struct s_env
{
  char          *key;
  char          *value;
  struct s_env  *next;
}         t_env;


typedef struct s_data
{
	t_env				  *envp_cpy;
	size_t				cmds_count;
	int					  fd[2];
	int					pid;
	t_cmd		      *cmds;
  t_fullcmd       *token_fullcmd;
	t_garbage_co  *garbage; // Chained list of all the malloced pointers
}						t_data;

/* ╔════════════════════════════════════╗ */
/* ║               ERROR                ║ */
/* ╚════════════════════════════════════╝ */

t_bool  check_errors(t_fullcmd *tokens);
t_bool check_open_quotes(char *line);
t_bool pipe_errors(t_fullcmd *tokens);
t_bool redirect_errors(t_fullcmd *tokens);
t_bool expand_errors(t_fullcmd *tokens);

/* ╔════════════════════════════════════╗ */
/* ║              PARSING               ║ */
/* ╚════════════════════════════════════╝ */

char					**cpy_envp(char **envp);
t_env *env_cpy(char **envp);
t_data					*init_and_alloc_data(char **envp);
char					**get_cmds_in_pipe(char *prompt);
t_fullcmd *parse_tokens(char *line, t_data *data);
// void					add_cmd_to_lst(char **cmds, t_lst *lst);

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

void					ft_prompt(t_data *data);

/* ╔════════════════════════════════════╗ */
/* ║              SIGNALS               ║ */
/* ╚════════════════════════════════════╝ */

/* ╔════════════════════════════════════╗ */
/* ║               UTILS                ║ */
/* ╚════════════════════════════════════╝ */

// t_lst					*ft_lstnew(t_cmd *cmd);
// void					ft_lstadd_back(t_lst **lst, t_lst *new);
// void					ft_print_lst(t_lst *cmd);
t_data					*get_data(void);
void  init_data(t_data *data, char **envp);
void init_env(t_env *env);
t_bool	is_whitespace(char c);
t_bool is_separator(char c);
t_bool  isquote(char c);
int count_arguments(char *line);
int skip_quotes(char *line, int i, char quote);
char **allocate_args(int arg_count);
int skip_spaces(char *line, int i);
int in_quote_arg(char *line, char **args, int i, int *j);
int not_quoted_arg(char *line, char **args, int i, int *j);
void extract_args(char *line, char **args);
char **split_args(char *line);

/* ╔════════════════════════════════════╗ */
/* ║        GARBAGE COLLECTOR           ║ */
/* ╚════════════════════════════════════╝ */

void					*gc_mem(t_mem type, size_t size, void *ptr);
// Exemples :
// gc_mem(MALLOC, sizeof(char *), NULL) -->
// gc_mem(FREE, 0, str) ---> free pointer "str"
// gc_mem(FULL_CLEAN, 0, NULL)



#endif
