#include "../includes/minishell.h"

void	ft_exit_status(t_terminal *terminal, int status)
{
	if (WIFEXITED(status))
		terminal->old_status = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
		terminal->old_status = WTERMSIG(status) + 128;
	ft_close_fds(terminal);
}

void	ft_redirects(t_terminal *terminal, int fd_1, int fd_0)
{
	if (terminal->fd_out > 1)
		dup2 (terminal->fd_out, fd_1);
	if (terminal->fd_in > 0)
		dup2 (terminal->fd_in, fd_0);
	if (terminal->fd_in < 0)
		exit(1);
}

void	ft_cleaner_mass(char **ans)
{
	int	i;

	i = 0;
	while (ans && ans[i])
	{
		free(ans[i]);
		ans[i] = NULL;
		i++;
	}
	free(ans);
	ans = NULL;
}

void	my_handler(int sig)
{	
	if (sig == SIGQUIT)
		write(1, "Quit: 3", 7);
	write(1, "\n", 1);
	signal(sig, SIG_IGN);
}

void	ft_sig_ign(int sig)
{
	(void)sig;
	g_stat_errno = 1;
	rl_on_new_line();
	rl_redisplay();
	write(1, "  ", 2);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
