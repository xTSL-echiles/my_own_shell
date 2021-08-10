#include "../includes/minishell.h"

void	ft_set_term(int i)
{
	if (i == 0)
	{
		signal(SIGINT, my_handler);
		signal(SIGQUIT, my_handler);
	}
	else
	{
		signal(SIGINT, ft_sig_ign);
		signal(SIGQUIT, SIG_IGN);
	}
}

void	ft_close_fds(t_terminal *terminal)
{
	unlink("temp.txt");
	if (terminal->fd_in > 1)
		close(terminal->fd_in);
	if (terminal->fd_out > 1)
		close(terminal->fd_out);
}

int	ft_check_red(t_terminal *t, char *save)
{
	if (!save || save == NULL)
	{
		if (t->fd_in > 1)
			t->old_status = 0;
		free(save);
		ft_close_fds(t);
		return (1);
	}
	return (0);
}

char	*ft_strjoin_f(char const *s1, char const *s2)
{
	char	*res;
	size_t	n1;
	size_t	n2;
	size_t	i;

	n1 = ft_strlen(s1);
	n2 = ft_strlen(s2);
	i = 0;
	res = malloc(n1 + n2 + 1);
	if (!res)
		return (0);
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	while (s2[i - n1])
	{
		res[i] = s2[i - n1];
		i++;
	}
	res[i] = '\0';
	free((char *)s1);
	s1 = NULL;
	return (res);
}
