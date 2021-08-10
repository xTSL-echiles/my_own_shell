/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eoddish <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 19:22:33 by eoddish           #+#    #+#             */
/*   Updated: 2021/07/01 18:06:09 by eoddish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_parse_dquotes(t_terminal *a, char **s, char *line)
{
	int		i;

	i = 1;
	while (line[i] != '\"' && line[i])
	{
		if (line[i] == '$')
			i += ft_parse_env(a, s, line + i);
		if (line[i] != '\"')
			ft_append(s, line[i]);
		i++;
	}
	return (i);
}

int	ft_parse_squotes(char **s, char *line)
{
	int		i;

	i = 1;
	while (line[i] != '\'' && line[i])
	{
		ft_append(s, line[i]);
		i++;
	}
	return (i);
}
