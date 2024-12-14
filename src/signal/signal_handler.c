#include "../../includes/minishell.h"

void	handle_sigquit2(int sig)
{
	t_data	*data;

	(void)sig;
	data = get_data();
	if (data->open_process)
	{
		data->exit_status = 131;
		ft_putstr_fd("\033[1;31mQuit (core dumped)\033[0m\n", 2);
	}
}

static void	replace_redisplay(void)
{
	rl_replace_line("", 0);
	ft_putstr_fd("\n", STDIN_FILENO);
	printf(CYAN);
	if (rl_on_new_line() != 0)
		return (perror("rl_on_new_line"));
	rl_redisplay();
	printf(RESET);
}

static void	sigint_process(void)
{
	t_data	*data;

	data = get_data();
	signal(SIGINT, NULL);
	data->open_process = false;
	printf("\n");
	// ft_prompt(data);
}

static void	sigint_herdeoc(void)
{
	t_data	*data;

	data = get_data();
	clean_heredoc(data);
	printf("\n");
	replace_redisplay();
	ft_prompt(data);
}

void	handle_sigint(int sig)
{
	t_data	*data;

	// ft_putstr_fd("NOT open_proc\n\n", 2);
	(void)sig;
	data = get_data();
	data->exit_status = 130;
	// if (data->open_process)
	// 	ft_putstr_fd("open_proc\n\n", 2);
	// else
	if (data->heredoc)
		sigint_herdeoc();
	else if (!data->open_process)
	{
		replace_redisplay();
	}
	else
	{		// ft_putstr_fd("ICI\n", 2);
		sigint_process();
	}
}

void	handle_signals(void)
{
	t_data	*data;

	data = get_data();
	signal(SIGINT, &handle_sigint);
	signal(SIGQUIT, &handle_sigquit2);
	// if (!data->open_process)
	// {
	// 	signal(SIGQUIT, SIG_IGN);
	// }
	// else
	// {
	// 	printf("\n");
	// }
}