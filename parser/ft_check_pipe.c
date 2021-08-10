/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eoddish <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 18:08:47 by eoddish           #+#    #+#             */
/*   Updated: 2021/07/02 19:34:07 by eoddish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_check_pipe_2(char *idea, char c, int k)
{
	k++;
	while (idea[k] && idea[k] != c)
		k++;
	if (idea[k] == c)
		k++;
	return (k);
}

char	*ft_check_pipe(t_terminal *a, char *line)
{
	char	*idea;
	int		k;

	k = 0;
	idea = ft_strdup(line);
	while (idea && idea[k])
	{
		if (idea[k] == '\"')
			k = ft_check_pipe_2(idea, '\"', k);
		else if (idea[k] == '\'')
			k = ft_check_pipe_2(idea, '\'', k);
		else if (idea[k] == '|')
			idea[k++] = '\n';
		else
			k++;
	}
	free(a->buf);
	a->buf = idea;
	return (idea);
}
