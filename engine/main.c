#include "../includes/minishell.h"

void	ft_setup_builtin(t_terminal *terminal)
{
	terminal->built_in = (char **)malloc(sizeof(char *) * 9);
	terminal->built_in[0] = ft_strdup("cd");
	terminal->built_in[1] = ft_strdup("echo");
	terminal->built_in[2] = ft_strdup("pwd");
	terminal->built_in[3] = ft_strdup("export");
	terminal->built_in[4] = ft_strdup("env");
	terminal->built_in[5] = ft_strdup("unset");
	terminal->built_in[6] = ft_strdup("exit");
	terminal->built_in[7] = ft_strdup("minishell");
	terminal->built_in[8] = NULL;
}

void	ft_setup_env(t_terminal *terminal, char **envp)
{
	char	**env;
	char	*str;
	int		n;
	int		i;

	n = 0;
	while (envp[n])
		n++;
	env = (char **)ft_calloc(n + 1, sizeof(char *));
	i = 0;
	while (envp[i])
	{
		env[i] = (char *)ft_calloc(ft_strlen(envp[i]) + 1, 1);
		ft_memcpy(env[i], envp[i], ft_strlen(envp[i]));
		i++;
	}
	terminal->envp = env;
	str = "SHLVL=1";
	ft_export(terminal, str, 1);
}

int	ft_setup_struct(t_terminal **terminal, char **envp)
{
	*terminal = (t_terminal *)malloc(sizeof(t_terminal));
	if (!terminal)
		return (0);
	(*terminal)->buf = NULL;
	(*terminal)->old_status = 0;
	(*terminal)->shell_lvl = 1;
	ft_setup_env(*terminal, envp);
	ft_setup_builtin(*terminal);
	return (1);
}

void	ft_cleaner(t_terminal *terminal)
{
	free(terminal->buf);
	ft_cleaner_mass(terminal->envp);
	ft_cleaner_mass(terminal->built_in);
	free(terminal);
}

int	main(int argc, char **argv, char **envp)
{
	t_terminal	*terminal;

	(void)argc;
	(void)argv;
	signal(SIGINT, ft_sig_ign);
	signal(SIGQUIT, SIG_IGN);
	if (!(ft_setup_struct(&terminal, envp)))
		return (0);
	ft_read_term(terminal);
	ft_cleaner(terminal);
	return (terminal->old_status);
}
