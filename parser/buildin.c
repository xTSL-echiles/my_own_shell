/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eoddish <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 19:10:50 by eoddish           #+#    #+#             */
/*   Updated: 2021/07/03 17:28:36 by eoddish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_echo(char *print, int fd)
{
	int		n_l1;

	n_l1 = 1;
	if (print)
	{
		if (!ft_strncmp(print, "-n ", 3))
		{
			n_l1 = 0;
			write(fd, print + 3, ft_strlen(print) - 3);
		}
		else if (!ft_strncmp(print, "-n", 3))
			n_l1 = 0;
		else
			write(fd, print, ft_strlen(print));
	}
	if (n_l1)
		write(fd, "\n", 1);
}

char	*ft_search(char **env, char *var)
{
	int		i;

	i = 0;
	while (env[i] && (ft_strncmp(env[i], var, ft_strlen(var))
			|| env[i][ft_strlen(var)] != '='))
		i++;
	if (env[i])
		return (env[i] + ft_strlen(var) + 1);
	else
		return (NULL);
}

void	ft_cd_2(t_terminal *a)
{
	char	*buf;
	char	*c_pwd;
	int		i;

	i = 0;
	buf = 0;
	c_pwd = 0;
	while (ft_strncmp((a->envp)[i], "PWD=", 4))
		i++;
	free((a->envp)[i]);
	buf = ft_calloc(MAXPATHLEN, sizeof(char));
	c_pwd = getcwd(buf, MAXPATHLEN);
	(a->envp)[i] = ft_calloc(ft_strlen(c_pwd) + 5, 1);
	ft_memcpy((a->envp)[i], "PWD=", 4);
	ft_memcpy((a->envp)[i] + 4, c_pwd, ft_strlen(c_pwd));
	free(buf);
}

void	ft_cd(t_terminal *a, char *print)
{
	char	*err;
	int		ret;

	if (!print)
		print = ft_search(a->envp, "HOME");
	if (print)
	{
		ret = chdir(print);
		if (ret < 0)
		{
			err = strerror(errno);
			printf("cd: n%s: %s\n", err + 1, print);
		}
		else
			ft_cd_2(a);
	}
}

void	ft_pwd(int fd)
{
	char	*buf;

	buf = (char *)malloc(MAXPATHLEN);
	ft_putstr_fd(getcwd(buf, MAXPATHLEN), fd);
	ft_putchar_fd('\n', fd);
	free(buf);
	buf = NULL;
}
