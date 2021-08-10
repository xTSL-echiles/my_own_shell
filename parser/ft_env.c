/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eoddish <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 21:50:38 by eoddish           #+#    #+#             */
/*   Updated: 2021/07/01 22:36:06 by eoddish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_env(t_terminal *all, int fd)
{
	int	i;

	i = 0;
	while ((all->envp)[i])
	{
		if (!ft_strncmp((all->envp)[i], "_=", 2))
			write(fd, "_=/usr/bin/env", 14);
		else
			write(fd, (all->envp)[i], ft_strlen((all->envp)[i]));
		write(fd, "\n", 1);
		i++;
	}
}
