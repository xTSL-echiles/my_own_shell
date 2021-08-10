/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_call.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eoddish <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 19:21:37 by eoddish           #+#    #+#             */
/*   Updated: 2021/07/02 02:07:20 by eoddish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_call_2(char *builtin, char *str, t_terminal *a)
{
	char	*newstr;
	char	*temp;

	temp = ft_strjoin(builtin, " ");
	if (str)
	{
		newstr = ft_strjoin(temp, str);
		free(temp);
	}
	else
		newstr = temp;
	ft_daughter_execute(a, newstr, NULL);
}

void	ft_call_3(char *builtin, char *str, t_terminal *a, int fd)
{
	if (!ft_strncmp(builtin, "cd", 3))
		ft_cd(a, str);
	else if (!ft_strncmp(builtin, "echo", 5))
		ft_echo(str, fd);
	else if (!ft_strncmp(builtin, "pwd", 4))
		ft_pwd(fd);
	else if (!ft_strncmp(builtin, "export", 7))
		ft_export(a, str, fd);
	else if (!ft_strncmp(builtin, "env", 4))
		ft_env(a, fd);
	else if (!ft_strncmp(builtin, "unset", 6))
		ft_unset(a, str);
	else if (!ft_strncmp(builtin, "exit", 5))
		ft_exit_check(a, str);
	else if (!ft_strncmp(builtin, "minishell", 10))
		ft_shlvl(a, 1);
	else
		ft_call_2(builtin, str, a);
}

void	ft_call(char *builtin, char *str, t_terminal *a)
{
	int		i;
	int		fd;

	fd = a->fd_out;
	i = 0;
	if (builtin)
	{
		while (builtin && builtin[i])
		{
			builtin[i] = ft_tolower(builtin[i]);
			i++;
		}
		ft_call_3(builtin, str, a, fd);
	}
	else
		ft_daughter_execute(a, NULL, NULL);
}
