/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eoddish <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 19:30:13 by eoddish           #+#    #+#             */
/*   Updated: 2021/07/03 18:12:18 by eoddish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_parse_in_2(t_terminal *a, char **file, char *line, int i)
{
	while (line[i] == ' ')
		i++;
	while (line[i] && line[i] != ' ' && line[i] != '>' && line[i] != '<')
		ft_append(file, line[i++]);
	if (!(*file))
	{
		printf("%s\n",
			"minishell: syntax error near unexpected token `newline'");
		a->err = 1;
		return (i);
	}
	if (*file)
	{
		a->fd_in = open(*file, O_RDONLY);
		if (a->fd_in < 0)
		{
			a->err = 1;
			write(2, "minishell: ", 11);
			perror(*file);
			free(*file);
			return (i);
		}
		free(*file);
	}
	return (i);
}

int	ft_parse_in(char *line, t_terminal *a)
{
	char	*file;
	int		i;

	if (a->fd_in > 0)
		close(a->fd_in);
	file = 0;
	i = 1;
	if (line[i] == '<')
	{
		i++;
		if (a->fd_in >= 0)
			a->fd_in = a->fd_here;
		while (line && line[i] && line[i] == ' ')
			i++;
		while (line && line[i] && line[i] != ' ')
			i++;
	}
	else
		i = ft_parse_in_2(a, &file, line, i);
	while (line[i] && line[i] == ' ')
		i++;
	return (i);
}
