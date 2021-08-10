/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eoddish <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 16:15:06 by eoddish           #+#    #+#             */
/*   Updated: 2021/07/03 17:27:24 by eoddish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_append(char **s, char c)
{
	char	*temp;

	if (!(*s))
	{
		*s = ft_calloc(1, 2);
		(*s)[0] = c;
	}
	else
	{
		temp = ft_calloc(1, ft_strlen(*s) + 2);
		ft_memcpy(temp, *s, ft_strlen(*s));
		temp[ft_strlen(*s)] = c;
		free(*s);
		*s = temp;
	}
}

void	ft_shlvl(t_terminal *a, int nbr)
{
	char	*str;
	char	*newstr;

	if (nbr > 0)
		a->shell_lvl++;
	else if (nbr < 0)
		a->shell_lvl--;
	str = ft_itoa(a->shell_lvl);
	newstr = ft_strjoin("SHLVL=", str);
	ft_export(a, newstr, 1);
	free(str);
	free(newstr);
}

void	ft_parser_2(t_terminal *a, char *line, int i, char **str)
{
	while (line && line[i])
	{
		while (line[i] == ' ')
			i++;
		while (line[i] != ' ' && line[i])
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
		}
		while (line[i] == ' ')
			i++;
		i += ft_parse_arg(*str, line + i, a);
		free(*str);
		*str = 0;
	}
}

void	ft_parser(char *line, t_terminal *a)
{
	int		i;
	char	*str;

	i = 0;
	str = 0;
	a->err = 0;
	a->fd_out = 1;
	a->fd_in = 0;
	if (!a->is_pipe)
		line = ft_check_pipe(a, line);
	if (!a->is_pipe)
		if (ft_check_here(a))
			return ;
	if (strchr(line, '\n'))
	{	
		a->is_pipe = 1;
		a->no_pipe = 0;
		ft_parse_pipe(a, line);
	}
	else
		ft_parser_2(a, line, i, &str);
	if (str)
		free(str);
}
