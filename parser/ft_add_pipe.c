/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eoddish <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 19:31:33 by eoddish           #+#    #+#             */
/*   Updated: 2021/07/03 17:28:58 by eoddish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_add_pipe_2(char *func, char *str)
{
	char	*newstr;
	char	*temp;

	temp = ft_strjoin(func, " ");
	if (str)
	{
		newstr = ft_strjoin(temp, str);
		free(temp);
	}
	else
		newstr = temp;
	return (newstr);
}

void	ft_add_pipe(char *func, char *str, t_terminal *a)
{
	char	*newstr;
	char	**s1;

	newstr = ft_add_pipe_2(func, str);
	if (a->no_pipe == 1)
		a->for_perror = ft_calloc(a->pipe_total + 1, sizeof(char *));
	a->for_perror[a->no_pipe - 1] = ft_strdup(func);
	a->for_perror[a->no_pipe] = NULL;
	s1 = ft_split(newstr, ' ');
	free(newstr);
	if (s1)
		ft_daughter_execute(a, s1[0], s1);
	else
		ft_daughter_execute(a, NULL, s1);
	if (a->no_pipe == 1)
		ft_first_pipe(a, s1);
	else if (a->no_pipe < a->pipe_total)
		ft_middle_pipe(a, s1, a->no_pipe - 1);
	else
		ft_last_pipe(a, s1);
	unlink("./temp.txt");
	ft_cleaner_mass(s1);
}
