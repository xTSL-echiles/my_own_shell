/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eoddish <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 19:54:46 by eoddish           #+#    #+#             */
/*   Updated: 2021/07/02 01:19:54 by eoddish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_unset_2(t_terminal *a, int i, int n)
{
	char	**envpp;

	envpp = ft_calloc(n, sizeof(char *));
	n = 0;
	while (n < i)
	{
		envpp[n] = ft_strdup((a->envp)[n]);
		n++;
	}
	while ((a->envp)[n + 1])
	{
		envpp[n] = ft_strdup((a->envp)[n + 1]);
		n++;
	}
	ft_cleaner_mass(a->envp);
	a->envp = envpp;
}

void	ft_unset(t_terminal *a, char *print)
{
	int		i;
	int		n;

	if (!print)
		return ;
	i = 0;
	n = 0;
	while ((a->envp)[n])
		n++;
	while ((a->envp)[i])
	{
		if (!ft_strncmp((a->envp)[i], print,
			ft_strlen(print))
			&& ft_strncmp(print, "_", 1))
		{
			ft_unset_2(a, i, n);
			break ;
		}
		i++;
	}
}
