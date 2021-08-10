/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eoddish <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 19:35:56 by eoddish           #+#    #+#             */
/*   Updated: 2021/07/02 20:17:35 by eoddish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_pipe_err(t_terminal *a, char ***pipe_line)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
	a->old_status = 258;
	ft_cleaner_mass(*pipe_line);
}

int	ft_parse_pipe_2(t_terminal *a, char ***pipe_line)
{
	char	*temp;

	a->pipe_total = 0;
	if ((*pipe_line)[a->pipe_total] == NULL)
	{
		ft_pipe_err(a, pipe_line);
		return (-1);
	}
	while ((*pipe_line)[a->pipe_total] != NULL)
	{
		temp = ft_strtrim((*pipe_line)[a->pipe_total], " ");
		if (!temp || !ft_strcmp(temp, ""))
		{
			ft_pipe_err(a, pipe_line);
			free(temp);
			return (-1);
		}
		free(temp);
		(a->pipe_total)++;
	}
	return (0);
}

int	ft_parse_pipe_3(t_terminal *a, char *line, char ***pipe_line)
{
	int		j;
	int		cnt;

	j = 0;
	cnt = 0;
	while (line[j])
		if (line[j++] == '\n')
			cnt++;
	if (cnt + 1 != a->pipe_total)
	{
		ft_pipe_err(a, pipe_line);
		return (-1);
	}
	return (0);
}

void	ft_parse_pipe(t_terminal *a, char *line)
{
	char	**pipe_line;
	int		i;

	pipe_line = ft_split(line, '\n');
	if (ft_parse_pipe_2(a, &pipe_line))
		return ;
	if (ft_parse_pipe_3(a, line, &pipe_line))
		return ;
	i = -1;
	a->pipes = ft_calloc(a->pipe_total, (sizeof(int *)));
	while (++i < a->pipe_total)
		a->pipes[i] = ft_calloc(2, sizeof(int));
	i = 0;
	while (i < a->pipe_total)
	{
		(a->no_pipe)++;
		ft_parser(pipe_line[i], a);
		i++;
	}
	a->is_pipe = 0;
	i = -1;
	while (++i < a->pipe_total)
		free(a->pipes[i]);
	free(a->pipes);
	ft_cleaner_mass(pipe_line);
}
