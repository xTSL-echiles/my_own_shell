/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eoddish <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 19:33:09 by eoddish           #+#    #+#             */
/*   Updated: 2021/07/02 20:38:16 by eoddish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_parse_arg_2(t_terminal *a, char *line, char **str, int i)
{
	if (line[i] == '\"')
		i += ft_parse_dquotes(a, str, line + i) + 1;
	else if (line[i] == '\'')
		i += ft_parse_squotes(str, line + i) + 1;
	else if (line[i] == '$')
		i += ft_parse_env(a, str, line + i);
	else if (line[i] == '>')
		i += ft_parse_out(line + i, a);
	else if (line[i] == '<')
		i += ft_parse_in(line + i, a);
	else
		ft_append(str, line[i++]);
	return (i);
}

int	ft_parse_arg(char *builtin, char *line, t_terminal *a)
{
	int		i;
	char	*str;

	i = 0;
	str = 0;
	while (line[i])
	{
		while (line[i] != ' ' && line[i])
			i = ft_parse_arg_2(a, line, &str, i);
		if (line[i] == ' ')
		{
			ft_append(&str, ' ');
			while (line[i] == ' ')
				i++;
		}
	}
	if (!a->is_pipe && !a->err)
		ft_call(builtin, str, a);
	else if (a->is_pipe)
		ft_add_pipe(builtin, str, a);
	free(str);
	return (i);
}
