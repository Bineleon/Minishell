/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elilliu <elilliu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/12/12 17:23:59 by elilliu          ###   ########.fr       */
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
}				t_token;

typedef enum e_mem
{
	MALLOC,
	FREE,
	FULL_CLEAN
}				t_mem;

typedef enum e_bool
{
	false,
	true
}				t_bool;

/* ╔════════════════════════════════════╗ */
/* ║             STRUCTURES             ║ */
/* ╚════════════════════════════════════╝ */

typedef struct s_fullcmd
{
	char				*str;
	t_token				type;
	t_bool				is_cmd;
	t_bool				concat_next;
	struct s_fullcmd	*next;
}						t_fullcmd;

typedef struct s_redir
{
	t_token			type;
	char			*file_name;
	struct s_redir	*next;
}					t_redir;

typedef struct s_cmd
{
	struct s_cmd	*prev;
	char			*cmd;
	t_redir			*redir;
	t_bool			is_first;
	char			**args;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_garbage_co
{
	void					*ptr;
	struct s_garbage_co		*next;
}							t_garbage_co;

typedef struct s_garbage_env
{
	void					*ptr;
	struct s_garbage_env	*next;
}							t_garbage_env;

typedef struct s_env
{
	char			*key;
	t_bool			equal;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_heredoc
{
	t_bool	in_process;
	int		fd[2];
	char	*fullprompt;
}			t_heredoc;

typedef struct s_data
{
	t_env					*envp_cpy;
	size_t					cmds_count;
	int						fd[3];
	int						fd_;
	int						pid;
	int						exit_status;
	t_heredoc				*heredoc;
	t_bool					open_process;
	char					*delim;
	t_cmd					*cmds;
	t_fullcmd				*token_fullcmd;
	t_garbage_env			*garbage_env;
	t_garbage_co			*garbage;
// Chained list of all the malloced pointers
}							t_data;

void			find_cmds(t_data *data);

/* ╔════════════════════════════════════╗ */
/* ║              BUILTINS              ║ */
/* ╚════════════════════════════════════╝ */

void			ft_env(t_data *data);
void			ft_pwd(t_data *data);
void			ft_echo(t_cmd *cmds, int fd);
void			ft_export(t_cmd *cmds);
void			ft_unset(t_cmd *cmds);
void			ft_exit(t_cmd *cmds);
void			ft_cd(t_cmd *cmds);
t_bool			is_valid_key(char *key);
int				ft_longest(char *s1, char *s2);
void			update_env(t_env **env, char *key, char *value, t_bool equal);
char			*get_env_value(char *var_name, t_env *env_list);

/* ╔════════════════════════════════════╗ */
/* ║               ERROR                ║ */
/* ╚════════════════════════════════════╝ */

t_bool			check_errors(t_fullcmd *tokens);
t_bool			check_open_quotes(char *line);
t_bool			pipe_errors(t_fullcmd *tokens);
t_bool			redirect_errors(t_fullcmd *tokens);
t_bool			expand_errors(t_fullcmd *tokens);

/* ╔════════════════════════════════════╗ */
/* ║              PARSING               ║ */
/* ╚════════════════════════════════════╝ */

char			**cpy_envp(char **envp);
t_env			*env_cpy(char **envp);
t_data			*init_and_alloc_data(char **envp);
char			**get_cmds_in_pipe(char *prompt);
t_fullcmd		*parse_tokens(char *line, t_data *data);
int				process_word(char *str, int i, char **result);
char			*extract_var_name(char *str, int start, int end);
char			*extract_var(char *line, int *i, int start);
t_fullcmd		*create_token(t_fullcmd **current_token, t_fullcmd **head);
int				to_handle_quotes(char *line, int i, t_fullcmd *token);
int				to_handle_pipe(char *line, int i, t_fullcmd *token);
int				to_handle_in(char *line, int i, t_fullcmd *token);
int				to_handle_out(char *line, int i, t_fullcmd *token);
int				sub_handle_expand(char *line, int i, t_fullcmd *token);
int				to_handle_expand(char *line, int i, t_fullcmd *token);
t_bool			is_in_dquote(t_fullcmd *token);
t_bool			is_in_squote(t_fullcmd *token);
char			*get_env_value(char *var_name, t_env *env_list);
char			*expand_token_value(char *str, t_env *env_list);
void			expand_var(t_data *data);
char			*expand_token(char *str, t_env *env_list);
void			handle_expand(t_fullcmd *token, t_env *env_list);
void			handle_dquote_exp(t_fullcmd *token, t_env *env_list);
void			handle_squote_exp(t_fullcmd *token);
char			*init_result(void);
char			*expand_exit_st(char *str, char **result, int i);

/* ╔════════════════════════════════════╗ */
/* ║               EXEC                 ║ */
/* ╚════════════════════════════════════╝ */

void			exec(t_data *data);
void			which_child(t_data *data);
void			first_child(t_data *data);
void			middle_child(t_data *data);
void			last_child(t_data *data);
int				redir_input(t_data *data);
void			heredoc(t_data *data, t_redir *current_redir);
void			clean_heredoc(t_data *data);
void			new_heredoc(t_data *data);
int				redir_output(t_data *data, t_cmd *cmd);
void			exec_cmd(t_data *data);
char			*new_path(char *arg, t_env *env_cpy);
char			**all_paths(t_env *env);
char			*join(char *path, char *cmd);
void			init_cmds(t_data *data);
void			new_cmd(t_cmd *cmds, t_fullcmd **fullcmd);
char			*joinequal(char *key, char *value);
char			**ft_newenv(t_data *data);
void			exec_builtin(t_data *data, t_cmd *cmds);
t_bool			is_builtin(char *cmd);
void			redir_builtins(t_data *data);
int				is_delim(t_redir *current_redir, char *prompt);
int				new_input_fd(t_data *data, t_redir *current_redir, int *fd);
void			adding_new_redirs(t_cmd *cmds, t_fullcmd *current);
void			create_new_cmd(t_cmd *cmds, t_fullcmd *current);
void			add_redir(t_redir **redir_list, t_token type, char *file_name);

/* ╔════════════════════════════════════╗ */
/* ║              PROMPT                ║ */
/* ╚════════════════════════════════════╝ */

void			ft_prompt(t_data *data);

/* ╔════════════════════════════════════╗ */
/* ║              SIGNALS               ║ */
/* ╚════════════════════════════════════╝ */

void			handle_signals(void);
void			signal_open_process(void);

/* ╔════════════════════════════════════╗ */
/* ║               UTILS                ║ */
/* ╚════════════════════════════════════╝ */

t_data			*get_data(void);
void			init_data(t_data *data, char **envp);
void			init_env(t_env *env);
void			init_cmd(t_cmd *cmd);
t_bool			is_whitespace(char c);
t_bool			is_separator(char c);
t_bool			isquote(char c);
int				count_arguments(char *line);
int				skip_quotes(char *line, int i, char quote);
char			**allocate_args(int arg_count);
int				skip_spaces(char *line, int i);
int				in_quote_arg(char *line, char **args, int i, int *j);
int				not_quoted_arg(char *line, char **args, int i, int *j);
void			extract_args(char *line, char **args);
char			**split_args(char *line);
void			error_mess(char *input, char *mess);
void			error_cmd(char *cmd);
void			error_syntax(char *str);
char			*gc_strjoin(char const *s1, char const *s2);
char			*gc_strdup(const char *s1);
char			*gc_strdup_env(const char *s1);
char			*gc_itoa(int n);
void			free_env_node(t_env *node);
long long int	ft_atol(const char *nptr);
void			ciao(int exit_status);
t_bool			is_redi(t_fullcmd *token);
void			skip_var_name(char *line, int *i);
char			**gc_split(char const *s, char c);
void			free_post_prompt(t_data *data);

/* ╔════════════════════════════════════╗ */
/* ║        GARBAGE COLLECTOR           ║ */
/* ╚════════════════════════════════════╝ */

void			*gc_mem(t_mem type, size_t size, void *ptr);
void			*gc_mem_env(t_mem type, size_t size, void *ptr);
// Exemples :
// gc_mem(MALLOC, sizeof(char *), NULL) -->
// gc_mem(FREE, 0, str) ---> free pointer "str"
// gc_mem(FULL_CLEAN, 0, NULL)

#endif
