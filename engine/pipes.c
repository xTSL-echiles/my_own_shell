#include "../includes/minishell.h"

void	ft_execute_pipes(t_terminal *terminal, char **s)
{
	int	check_status;

	terminal->error_st = 0;
	ft_check_stat(terminal, s[0]);
	if (ft_check_builtin(terminal, s) == 11)
		exit(0);
	check_status = execve(s[0], s, terminal->envp);
	if (check_status == -1 && terminal->error_st == 0)
		exit(127);
	else if (check_status == -1)
		exit(terminal->error_st);
}

void	ft_first_pipe(t_terminal *terminal, char **s1)
{
	terminal->pids = (int *)malloc(sizeof(int) * terminal->pipe_total);
	signal(SIGINT, my_handler);
	signal(SIGQUIT, my_handler);
	if (pipe(terminal->pipes[0]) == -1)
		perror("bad pipe first");
	terminal->pids[0] = fork();
	if (terminal->pids[0] == -1)
		perror("bad fork first_pipe");
	if (terminal->pids[0] == 0)
	{
		dup2(terminal->pipes[0][1], 1);
		ft_redirects(terminal, 1, 0);
		close(terminal->pipes[0][1]);
		close(terminal->pipes[0][0]);
		if (s1 == NULL)
			exit(0);
		ft_execute_pipes(terminal, s1);
	}
	else
	{
		if (s1 != NULL)
			ft_close_fds(terminal);
	}
}

void	ft_middle_pipe(t_terminal *terminal, char **s2, int i)
{
	if (pipe(terminal->pipes[i]) == -1)
		perror("bad pipe_mid");
	terminal->pids[i] = fork();
	if (terminal->pids[i] == -1)
		perror("bad fork_mid");
	else if (terminal->pids[i] == 0)
	{
		dup2(terminal->pipes[i - 1][0], 0);
		dup2(terminal->pipes[i][1], 1);
		ft_redirects(terminal, terminal->pipes[i][1], terminal->pipes[i][0]);
		close(terminal->pipes[i - 1][0]);
		close(terminal->pipes[i - 1][1]);
		close(terminal->pipes[i][1]);
		close(terminal->pipes[i][0]);
		ft_execute_pipes(terminal, s2);
	}
	else
	{
		close(terminal->pipes[i - 1][1]);
		close(terminal->pipes[i - 1][0]);
		if (s2 != NULL)
			ft_close_fds(terminal);
	}
}

void	ft_pipe_wait(t_terminal *terminal, int status, int i)
{
	i = -1;
	while (++i < terminal->pipe_total)
	{
		terminal->old_status = 0;
		waitpid(terminal->pids[i], &status, 0);
		terminal->error_st = 0;
		if (WEXITSTATUS(status) == 127)
		{
			terminal->old_status = 127;
			ft_print_errors(terminal, terminal->for_perror[i]);
		}
		else if (WEXITSTATUS(status) == 21 || WEXITSTATUS(status) == 13)
		{
			terminal->old_status = 126;
			terminal->error_st = (WEXITSTATUS(status));
			ft_print_errors(terminal, terminal->for_perror[i]);
		}
	}
	if (terminal->old_status == 0)
		ft_exit_status(terminal, status);
	signal(SIGINT, ft_sig_ign);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_last_pipe(t_terminal *terminal, char **s3)
{
	int	i;

	terminal->status = 0;
	i = terminal->pipe_total -1;
	terminal->pids[i] = fork();
	if (terminal->pids[i] == -1)
		perror("bad fork_last");
	else if (terminal->pids[i] == 0)
	{
		dup2(terminal->pipes[i - 1][0], 0);
		ft_redirects(terminal, 1, 0);
		close(terminal->pipes[i - 1][1]);
		close(terminal->pipes[i - 1][0]);
		ft_execute_pipes(terminal, s3);
	}
	else
	{
		close(terminal->pipes[i - 1][1]);
		close(terminal->pipes[i - 1][0]);
		ft_pipe_wait(terminal, terminal->status, i);
		if (s3 != NULL)
			ft_close_fds(terminal);
	}
	free(terminal->pids);
	ft_cleaner_mass(terminal->for_perror);
}
