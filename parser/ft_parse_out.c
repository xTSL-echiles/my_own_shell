/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_out.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eoddish <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 19:26:15 by eoddish           #+#    #+#             */
/*   Updated: 2021/07/02 20:32:32 by eoddish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_parse_out_2(char **file, char *line, int i)
{
	while (line[i] == ' ')
		i++;
	while (line[i] && line[i] != ' ')
	{
		ft_append(file, line[i]);
		if (line[i] == ' ' || line[i] == '>' || line[i] == '<')
		{
			if (line[i] != ' ')
				i--;
			break ;
		}
		i++;
	}
	return (i);
}

int	ft_parse_out_3(t_terminal *a, char *line, int i, int *append)
{
	if (a->fd_out > 1)
		close(a->fd_out);
	if (line[i] == '>')
	{
		*append = 1;
		i++;
		if (line[i] == '>')
		{
			printf("%s\n", "minishell: syntax error near unexpected token `>'");
			a->err = 1;
			return (ft_strlen(line));
		}
	}
	return (i);
}

int	ft_parse_out(char *line, t_terminal *a)
{
	int		i;
	int		append;
	char	*file;

	file = 0;
	append = 0;
	i = ft_parse_out_3(a, line, 1, &append);
	i = ft_parse_out_2(&file, line, i);
	if (!file && !a->err)
	{
		printf("%s\n",
			"minishell: syntax error near unexpected token `newline'");
		a->err = 1;
		return (i);
	}
	if (file && !append)
		a->fd_out = open(file, O_CREAT | O_RDWR | O_TRUNC, 0777);
	else if (file)
		a->fd_out = open(file, O_CREAT | O_RDWR | O_APPEND, 0777);
	if (file)
		free(file);
	while (line[i] && line[i] == ' ')
		i++;
	return (i);
}
