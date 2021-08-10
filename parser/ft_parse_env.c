/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eoddish <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 19:17:37 by eoddish           #+#    #+#             */
/*   Updated: 2021/07/02 01:26:24 by eoddish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_spec_char(char c)
{
	if ((c >= 32 && c <= 47)
		|| (c >= 58 && c <= 64)
		|| (c >= 91 && c <= 96)
		|| (c >= 123 && c <= 126))
		return (1);
	return (0);
}

void	ft_parse_env_2(char *env, char **s)
{
	int	k;

	k = 0;
	while (env[k])
		ft_append(s, env[k++]);
}

int	ft_parse_env(t_terminal *a, char **s, char *line)
{
	int		i;
	char	*env;
	char	*sub;

	i = 1;
	while (!ft_spec_char(line[i]) && line[i] && line[i] != '\n')
		i++;
	sub = ft_substr(line, 1, i - 1);
	env = ft_search(a->envp, sub);
	free(sub);
	if (!env && line[i] == '?')
	{
		env = ft_itoa(a->old_status);
		i++;
	}
	if (env)
		ft_parse_env_2(env, s);
	if (i == 1)
		ft_append(s, '$');
	if (line[i - 1] == '?')
		free(env);
	return (i);
}
