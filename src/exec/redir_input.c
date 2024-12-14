/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bineleon <neleon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 21:20:10 by elilliu           #+#    #+#             */
/*   Updated: 2024/12/14 16:26:51 by bineleon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	new_heredoc(t_data *data)
{
	data->fd[0] = -1;
	data->fd[1] = -1;
	data->heredoc = gc_mem(MALLOC, sizeof(t_heredoc), NULL);
	data->heredoc->fullprompt = NULL;
	data->heredoc->in_process = true;
}

void	clean_heredoc(t_data *data)
{
	if (data->heredoc->fd[0] != -1)
		close(data->heredoc->fd[0]);
	if (data->heredoc->fd[1] != -1)
		close(data->heredoc->fd[1]);
	if (data->heredoc->fullprompt)
		gc_mem(FREE, (size_t)NULL, data->heredoc->fullprompt);
	gc_mem(FREE, (size_t)NULL, data->heredoc);
}

void save_terminal_state(struct termios *termios_p)
{
    if (tcgetattr(STDIN_FILENO, termios_p) == -1)
    {
        perror("tcgetattr");
        exit(1);
    }
}

void restore_terminal_state(const struct termios *termios_p)
{
    if (tcsetattr(STDIN_FILENO, TCSANOW, termios_p) == -1)
    {
        perror("tcsetattr");
        exit(1);
    }
}

void handle_hd_sigint(int sig)
{
    (void)sig;
    t_data *data;

    data = get_data();
    data->hd_active = true;
    write(STDOUT_FILENO, "^C\n", 3);
    clean_heredoc(data);
    gc_mem(FULL_CLEAN, 0, NULL);
    gc_mem_env(FULL_CLEAN, 0, NULL);
    exit(130);
}

void set_hd_signals(void)
{
    struct sigaction act;

    sigemptyset(&act.sa_mask);
    act.sa_handler = SIG_IGN;
    act.sa_flags = SA_RESTART;
    if (sigaction(SIGQUIT, &act, NULL) == -1)
        perror("sigaction");
    act.sa_handler = handle_hd_sigint;
    if (sigaction(SIGINT, &act, NULL) == -1)
        perror("sigaction");
}

void restore_dfl_signals(void)
{
    struct sigaction act;

    sigemptyset(&act.sa_mask);
    act.sa_handler = handle_sigquit2;
    act.sa_flags = SA_RESTART;
    if (sigaction(SIGQUIT, &act, NULL) == -1)
        perror("sigaction");
    act.sa_handler = SIG_DFL;
    if (sigaction(SIGINT, &act, NULL) == -1)
        perror("sigaction");
}

void heredoc(t_data *data, t_redir *current_redir)
{
    char *prompt;
    struct termios orig_state;

    data->hd_active = true;
    data->open_process = false;
    save_terminal_state(&orig_state);
    set_hd_signals();
    new_heredoc(data);
    if (pipe(data->heredoc->fd) == -1)
    {
        restore_terminal_state(&orig_state);
        data->hd_active = false;
        return ((void)clean_heredoc(data), (void)error_mess(NULL, NULL));
    }
    while (1)
    {
        signal(SIGQUIT, SIG_DFL);
        set_hd_signals();
        data->open_process = false;
        prompt = readline("> ");
        if (!prompt)
        {
            restore_terminal_state(&orig_state);
            data->hd_active = false;
            error_mess("warning", "heredoc delimited by EOF\n");
            clean_heredoc(data);
            return;
        }
        if (is_delim(current_redir, prompt))
        {
            data->hd_active = false;
            gc_mem(FREE, (size_t)NULL, prompt);
            break;
        }
        data->heredoc->fullprompt = gc_strjoin(data->heredoc->fullprompt, prompt);
        data->heredoc->fullprompt = gc_strjoin(data->heredoc->fullprompt, "\n");
        gc_mem(FREE, (size_t)NULL, prompt);
    }
    ft_putstr_fd(data->heredoc->fullprompt, data->heredoc->fd[1]);
    dup2(data->heredoc->fd[0], STDIN_FILENO);
    restore_terminal_state(&orig_state);
    restore_dfl_signals();
    data->hd_active = false;
    clean_heredoc(data);
}

// void	heredoc(t_data *data, t_redir *current_redir)
// {
// 	char	*prompt;

// 	new_heredoc(data);
// 	if (pipe(data->heredoc->fd) == -1)
// 		return ((void)clean_heredoc(data), (void)error_mess(NULL, NULL));
// 	prompt = NULL;
// 	while (1)
// 	{
// 		prompt = readline("> ");
// 		if (!data->heredoc)
// 		{
// 			gc_mem(FULL_CLEAN, 0, NULL);
// 			gc_mem_env(FULL_CLEAN, 0, NULL);
// 		}
// 		if (!prompt)
// 			return ((void)error_mess(NULL, NULL));
// 		if (is_delim(current_redir, prompt) == 1)
// 		{
// 			gc_mem(FREE, (size_t)NULL, prompt);
// 			break ;
// 		}
// 		data->heredoc->fullprompt = gc_strjoin(data->heredoc->fullprompt,
// 				prompt);
// 		gc_mem(FREE, (size_t)NULL, prompt);
// 		data->heredoc->fullprompt = gc_strjoin(data->heredoc->fullprompt, "\n");
// 	}
// 	ft_putstr_fd(data->heredoc->fullprompt, data->heredoc->fd[1]);
// 	dup2(data->heredoc->fd[0], STDIN_FILENO);
// 	clean_heredoc(data);
// }

int	redir_input(t_data *data)
{
	t_redir	*current_redir;
	int		fd;

	if (!data->cmds || !data->cmds->redir)
		return (0);
	current_redir = data->cmds->redir;
	fd = 0;
	while (current_redir)
	{
		if (current_redir->type == IN || current_redir->type == HEREDOC)
		{
			if (fd > 0)
			{
				close(fd);
				fd = 0;
			}
			if (new_input_fd(data, current_redir, &fd) == 0)
				return (2);
		}
		current_redir = current_redir->next;
	}
	if (fd > 0)
		return (dup2(fd, STDIN_FILENO), close(fd), 1);
	return (0);
}
