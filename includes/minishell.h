/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bineleon <neleon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/11/23 13:24:06 by bineleon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/ft_printf/includes/ft_printf.h"
# include "../libft/gnl/get_next_line_bonus.h"
# include "../libft/libft/libft.h"
# include "./constants.h"
# include <fcntl.h>
# include <linux/limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <sys/wait.h>
# include <unistd.h>

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
	char				*str;
	t_token				type;
	struct s_fullcmd	*next;
}						t_fullcmd;

typedef struct s_cmd
{
	struct s_cmd		*prev;
	char				**str;
	char				*cmd;
	char				**args;
	struct s_cmd		*next;
}						t_cmd;

typedef struct s_garbage_co
{
	void				*ptr;
	struct s_garbage_co	*next;
}						t_garbage_co;

typedef struct s_env
{
	char				*key;
  t_bool      equal;
	char				*value;
	struct s_env		*next;
}						t_env;

typedef struct s_data
{
	t_env				*envp_cpy;
	size_t				cmds_count;
	int					fd[3];
	int					pid;
	int					exit_status;
	t_cmd				*cmds;
	t_fullcmd			*token_fullcmd;
	t_garbage_co		*garbage; // Chained list of all the malloced pointers
}						t_data;

/* ╔════════════════════════════════════╗ */
/* ║              BUILTINS              ║ */
/* ╚════════════════════════════════════╝ */

void					ft_env(t_env *env_cpy);
void					ft_pwd(void);
void          ft_echo(t_data *data);
void          ft_export(t_data *data);
void          ft_unset(t_data *data);
void          ft_exit(t_data *data);
t_bool        is_valid_key(char  *key);
int           ft_longest(char *s1, char *s2);

/* ╔════════════════════════════════════╗ */
/* ║               ERROR                ║ */
/* ╚════════════════════════════════════╝ */

t_bool					check_errors(t_fullcmd *tokens);
t_bool					check_open_quotes(char *line);
t_bool					pipe_errors(t_fullcmd *tokens);
t_bool					redirect_errors(t_fullcmd *tokens);
t_bool					expand_errors(t_fullcmd *tokens);

/* ╔════════════════════════════════════╗ */
/* ║              PARSING               ║ */
/* ╚════════════════════════════════════╝ */

char					**cpy_envp(char **envp);
t_env					*env_cpy(char **envp);
t_data					*init_and_alloc_data(char **envp);
char					**get_cmds_in_pipe(char *prompt);
t_fullcmd				*parse_tokens(char *line, t_data *data);

char					*get_env_value(char *var_name, t_env *env_list);
char					*expand_token_value(char *str, t_env *env_list);
void					expand_var(t_data *data);
char          *expand_token(char *str, t_env *env_list);
void					handle_expand(t_fullcmd *token, t_env *env_list);
void					handle_dquote_exp(t_fullcmd *token, t_env *env_list);
void					handle_squote_exp(t_fullcmd *token);

/* ╔════════════════════════════════════╗ */
/* ║               EXEC                 ║ */
/* ╚════════════════════════════════════╝ */

void					exec(t_data *data);
void					which_child(t_data *data);
void					first_child(t_data *data);
void					middle_child(t_data *data);
void					last_child(t_data *data);
void					redir_input(t_data *data);
void					redir_output(t_data *data);
void					exec_cmd(t_data *data);
char					*new_path(char *arg, t_env *env_cpy);
char					**all_paths(t_env *env);
char					*join(char *path, char *cmd);
void					init_cmds(t_data *data);
void					new_cmd(t_cmd *cmds, t_fullcmd **fullcmd);
void					new_str(t_cmd *cmds, t_fullcmd **fullcmd);
char					*joinequal(char *key, char *value);
char					**ft_newenv(t_data *data);

/* ╔════════════════════════════════════╗ */
/* ║              PROMPT                ║ */
/* ╚════════════════════════════════════╝ */

void					ft_prompt(t_data *data);

/* ╔════════════════════════════════════╗ */
/* ║              SIGNALS               ║ */
/* ╚════════════════════════════════════╝ */

void					handle_signals(void);

/* ╔════════════════════════════════════╗ */
/* ║               UTILS                ║ */
/* ╚════════════════════════════════════╝ */

t_data					*get_data(void);
void					init_data(t_data *data, char **envp);
void					init_env(t_env *env);
void					init_cmd(t_cmd *cmd);
t_bool					is_whitespace(char c);
t_bool					is_separator(char c);
t_bool					isquote(char c);
int						count_arguments(char *line);
int						skip_quotes(char *line, int i, char quote);
char					**allocate_args(int arg_count);
int						skip_spaces(char *line, int i);
int						in_quote_arg(char *line, char **args, int i, int *j);
int						not_quoted_arg(char *line, char **args, int i, int *j);
void					extract_args(char *line, char **args);
char					**split_args(char *line);
void					error_mess(char *input, char *mess);
char					*gc_strjoin(char const *s1, char const *s2);
char					*gc_strdup(const char *s1);
char					*gc_itoa(int n);
void          free_env_node(t_env *node);
long long int   ft_atol(const char *nptr);
void          ciao(int exit_status);

/* ╔════════════════════════════════════╗ */
/* ║        GARBAGE COLLECTOR           ║ */
/* ╚════════════════════════════════════╝ */

void					*gc_mem(t_mem type, size_t size, void *ptr);
// Exemples :
// gc_mem(MALLOC, sizeof(char *), NULL) -->
// gc_mem(FREE, 0, str) ---> free pointer "str"
// gc_mem(FULL_CLEAN, 0, NULL)

#endif
