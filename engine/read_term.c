#include "../includes/minishell.h"

int	ft_exit_check_arg(t_terminal *terminal, char **s2)
{
	int	i;

	i = -1;
	while (s2[0] && s2[0][++i])
	{
		if (!ft_isdigit(s2[0][i]))
		{
			terminal->old_status = 255;
			write(2, "minishell: exit:", 16);
			write(2, s2[0], ft_strlen(s2[0]));
			write(2, " numeric argument required\n", 27);
			ft_cleaner_mass(s2);
			ft_shlvl(terminal, -1);
			return (1);
		}
	}
	return (0);
}

void	ft_exit_check(t_terminal *terminal, char *s)
{
	int		i;
	char	**s2;

	s2 = NULL;
	s2 = ft_split(s, ' ');
	write(1, "exit\n", 5);
	if (s2 && s2[0])
	{
		if ((ft_exit_check_arg(terminal, s2)))
			return ;
		i = 0;
		while (s2 && s2[i])
			i++;
		if (i > 1)
		{
			terminal->old_status = 2;
			write(2, "minishell: exit: too many arguments\n", 36);
			ft_cleaner_mass(s2);
			return ;
		}
		if (s2[0])
			terminal->old_status = ft_atoi(s2[0]);
		ft_cleaner_mass(s2);
	}
	ft_shlvl(terminal, -1);
}

void	ft_read_term(t_terminal *terminal)
{
	int	i;

	while (terminal->shell_lvl)
	{
		i = 0;
		free(terminal->buf);
		terminal->buf = NULL;
		terminal->is_pipe = 0;
		terminal->buf = readline("minishell> ");
		if (g_stat_errno == 1)
			terminal->old_status = 1;
		g_stat_errno = 0;
		if (!ft_strcmp(terminal->buf, "\4"))
		{
			write(1, "exit\n", 5);
			ft_shlvl(terminal, -1);
			free(terminal->buf);
			terminal->buf = NULL;
			i = 10;
		}
		if (ft_strlen(terminal->buf) > 0)
			add_history(terminal->buf);
		if (!i)
			ft_parser(terminal->buf, terminal);
	}
}
