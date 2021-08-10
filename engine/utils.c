#include "../includes/minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1)
		return (0);
	while (s1 && s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

void	ft_print_errors(t_terminal *terminal, char *s)
{
	errno = terminal->error_st;
	if (terminal->error_st != 0)
		perror(s);
	else
		printf("minishell: %s: command not found\n", s);
}

void	ft_check_stat(t_terminal *terminal, char *check_s)
{
	struct stat	st_info;

	if (!(stat(check_s, &st_info)))
	{
		if (S_ISDIR(st_info.st_mode))
		{
			terminal->error_st = 21;
			terminal->old_status = 126;
		}
		else if (S_ISREG(st_info.st_mode))
		{
			if ((st_info.st_mode & S_IXUSR))
				return ;
			else
			{
				terminal->error_st = 13;
				terminal->old_status = 126;
			}
		}
	}
}

void	ft_check_builtin2(t_terminal *t, char **s2, char **s1, int j)
{
	int		i;
	char	*execute;

	execute = NULL;
	i = 1;
	if (s1 && s1[i])
	{
		while (s1 && s1[i])
		{
			if (i == 1)
				execute = ft_strdup(s1[i]);
			else
			{	
				execute = ft_strjoin_f(execute, " ");
				execute = ft_strjoin_f(execute, s1[i]);
			}
			i++;
		}
	}
	ft_call(s2[j], execute, t);
	free(execute);
}

int	ft_check_builtin(t_terminal *t, char **s1)
{
	char	**s2;
	int		i;
	int		j;

	i = 0;
	s2 = ft_split(s1[0], '/');
	i = -1;
	while (++i < 7)
	{
		j = -1;
		while (s2 && s2[++j])
		{
			if (!(ft_strncmp(s2[j], t->built_in[i], ft_strlen(s2[j]))))
			{
				i = 10;
				ft_check_builtin2(t, s2, s1, j);
				break ;
			}
		}
	}
	ft_cleaner_mass(s2);
	return (i);
}
