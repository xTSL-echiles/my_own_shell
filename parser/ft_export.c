/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eoddish <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 20:07:54 by eoddish           #+#    #+#             */
/*   Updated: 2021/07/01 22:31:47 by eoddish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**ft_ins_sort(char **envpp)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (envpp[i])
	{
		j = i;
		while (j > 0 && ft_strncmp(envpp[j],
				envpp[j - 1], ft_strlen(envpp[j])
				+ 1) < 0)
		{
			temp = envpp[j];
			envpp[j] = envpp[j - 1];
			envpp[j - 1] = temp;
			j--;
		}
		i++;
	}
	return (envpp);
}

void	ft_export_noarg_2(char **envpp, int fd, int i)
{
	int	j;

	ft_putstr_fd("declare -x ", fd);
	j = 0;
	while (envpp[i][j] && envpp[i][j] != '=')
		write(fd, envpp[i] + j++, 1);
	if (envpp[i][j])
	{
		write(fd, envpp[i] + j++, 1);
		if (envpp[i][j])
		{
			ft_putchar_fd('\"', fd);
			ft_putstr_fd(envpp[i] + j, fd);
			ft_putchar_fd('\"', fd);
		}
	}
	ft_putchar_fd('\n', fd);
}

void	ft_export_noarg(char **envp, int fd)
{
	int		n;
	int		i;
	char	**envpp;

	n = 0;
	while (envp[n])
		n++;
	envpp = (char **)ft_calloc(n + 1, sizeof(char *));
	i = 0;
	while (envp[i])
	{
		envpp[i] = ft_strdup(envp[i]);
		i++;
	}
	envpp = ft_ins_sort(envpp);
	i = 0;
	while (envpp[i])
	{
		if (ft_strncmp(envpp[i], "_=", 2))
			ft_export_noarg_2(envpp, fd, i);
		i++;
	}
	ft_cleaner_mass(envpp);
}

int	ft_export_2(t_terminal *a, char *print)
{
	int		n;
	char	*name;

	n = 0;
	while (print[n] != '=' && print[n])
		n++;
	name = ft_strdup(print);
	name[n] = '\0';
	ft_unset(a, name);
	n = ft_strlen(print);
	if (!ft_strncmp(print, name, n))
		n++;
	free(name);
	return (n);
}

void	ft_export(t_terminal *a, char *print, int fd)
{
	char	**envpp;
	int		i;
	int		n;

	if (!print)
		ft_export_noarg(a->envp, fd);
	else
	{
		i = 0;
		n = ft_export_2(a, print);
		while ((a->envp)[i])
			i++;
		envpp = ft_calloc(i + 2, sizeof(char *));
		i = 0;
		while ((a->envp)[i + 1])
		{
			envpp[i] = ft_strdup((a->envp)[i]);
			i++;
		}
		envpp[i] = ft_calloc(n + 1, 1);
		ft_memcpy(envpp[i], print, ft_strlen(print));
		envpp[i + 1] = ft_strdup((a->envp)[i]);
		ft_cleaner_mass(a->envp);
		a->envp = envpp;
	}
}
