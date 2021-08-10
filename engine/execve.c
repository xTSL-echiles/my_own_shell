#include "../includes/minishell.h"

char	**ft_s_finder(t_terminal *terminal)
{
	char	*env;
	char	**all_vars;
	int		i;
	char	*real_env;

	env = NULL;
	real_env = NULL;
	all_vars = NULL;
	i = -1;
	while (terminal->envp[++i])
	{
		if (!ft_strncmp(terminal->envp[i], "PATH=", 5))
		{
			env = ft_strdup(terminal->envp[i]);
			i = 4;
			real_env = (char *)ft_calloc(ft_strlen(env) - 3, sizeof(char));
			while (env && env[++i])
				real_env[i - 5] = env[i];
			break ;
		}
	}
	free(env);
	all_vars = ft_split(real_env, ':');
	free(real_env);
	return (all_vars);
}

int	ft_setup_name_p2(t_terminal *terminal, char **all_vars,
						struct stat *st_info, int i)
{
	if (!(stat(all_vars[i], st_info)))
	{
		if (S_ISDIR(st_info->st_mode))
		{
			terminal->old_status = 126;
			terminal->error_st = 21;
		}
		else if (S_ISREG(st_info->st_mode))
		{
			if ((st_info->st_mode & S_IXUSR))
				return (1);
			else
			{
				terminal->old_status = 126;
				terminal->error_st = 13;
			}
		}
	}
	return (0);
}

void	ft_setup_name(t_terminal *terminal, char *save, char **execute)
{
	struct stat	st_info;
	char		**all_vars;
	int			i;

	i = -1;
	all_vars = ft_s_finder(terminal);
	terminal->argv = ft_split(save, ' ');
	while (all_vars && all_vars[++i])
	{
		all_vars[i] = ft_strjoin_f(all_vars[i], "/");
		all_vars[i] = ft_strjoin_f(all_vars[i], terminal->argv[0]);
	}
	i = -1;
	while (all_vars && all_vars[++i] && terminal->error_st == 0)
	{
		free(*execute);
		if (ft_setup_name_p2(terminal, all_vars, &st_info, i))
		{
			*execute = ft_strdup(all_vars[i]);
			break ;
		}
		*execute = ft_strdup(terminal->argv[0]);
	}
	ft_cleaner_mass(all_vars);
}

void	ft_execute_execve(t_terminal *terminal, char *execute)
{
	pid_t	d;
	int		check_status;
	int		status;

	d = fork();
	if (d == 0)
	{
		ft_redirects(terminal, 1, 0);
		check_status = execve(execute, terminal->argv, terminal->envp);
		if (check_status == -1 && !terminal->error_st)
			exit (127);
		else
			exit (126);
	}
	else if (d < 0)
		exit(0);
	else
	{
		waitpid(d, &status, 0);
		if (WEXITSTATUS(status) == 126 || WEXITSTATUS(status) == 127)
			ft_print_errors(terminal, terminal->argv[0]);
		ft_exit_status(terminal, status);
	}
}

void	ft_daughter_execute(t_terminal *terminal, char *save, char **s1)
{
	char	*execute;

	if (ft_check_red(terminal, save))
		return ;
	execute = NULL;
	terminal->error_st = 0;
	ft_setup_name(terminal, save, &execute);
	if (s1 == NULL)
	{
		ft_set_term(0);
		ft_execute_execve(terminal, execute);
		ft_set_term(10);
		free(save);
	}
	if (s1 != NULL)
	{
		free(s1[0]);
		if (execute == NULL)
			s1[0] = ft_strdup(terminal->argv[0]);
		else
			s1[0] = ft_strdup(execute);
	}
	ft_cleaner_mass(terminal->argv);
	free(execute);
}
