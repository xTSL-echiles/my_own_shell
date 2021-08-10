/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_here.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eoddish <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 18:09:50 by eoddish           #+#    #+#             */
/*   Updated: 2021/07/03 17:30:28 by eoddish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_check_here_2(char *line, int i)
{
	int	k;
	int	cnt;

	k = i + 1;
	cnt = 0;
	while (line[k] && line[k] != '\n')
	{
		if (line[k] == ' ')
			cnt++;
		k++;
	}
	if (cnt == k - i - 1 || i == 0)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		return (-1);
	}
	return (0);
}

int	ft_check_here_3(char *line, int i)
{
	if (line[i] == '\n')
		if (ft_check_here_2(line, i))
			return (-1);
	if (line[i] == '\n' && line[i + 1] == '\n')
	{
		printf("%s\n", "minishell: syntax error near unexpected token `||'");
		return (-1);
	}
	if (line[i + 2] && line[i] == '>' && line[i + 1] == '>'
		&& line[i + 2] == '>')
	{
		printf("%s\n",
			"minishell: syntax error near unexpected token `>'");
		return (-1);
	}
	return (0);
}

int	ft_check_here(t_terminal *a)
{
	char	*line;
	int		i;

	line = a->buf;
	i = 0;
	a->fd_here = 0;
	while (line && line[i + 1])
	{
		if (ft_check_here_3(line, i))
			return (-1);
		if (line[i] == '<' && line[i + 1] == '<')
		{
			if (line[i + 2] == '<')
			{
				printf("%s\n",
					"minishell: syntax error near unexpected token `<'");
				return (-1);
			}
			i += 2;
			i += ft_here_redir(a, line + i);
		}
		else
			i++;
	}
	return (0);
}
