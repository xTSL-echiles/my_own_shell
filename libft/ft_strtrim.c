/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eoddish <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 20:18:44 by eoddish           #+#    #+#             */
/*   Updated: 2020/11/23 20:13:44 by eoddish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	ft_inset(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
		if (c == set[i++])
			return (1);
	return (0);
}

static char	*ft_start_eqs_finish(void)
{
	char	*res;

	res = malloc(1);
	res[0] = '\0';
	return (res);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	char	*res;
	size_t	start;
	size_t	finish;

	if (!s1 || !set)
		return (0);
	start = 0;
	finish = ft_strlen(s1) - 1;
	i = 0;
	while (ft_inset(s1[start], set))
		start++;
	if (start == finish + 1)
		return (ft_start_eqs_finish());
	while (ft_inset(s1[finish], set))
		finish--;
	res = malloc(finish - start + 2);
	if (!res)
		return (0);
	while (start <= finish)
		res[i++] = s1[start++];
	res[i] = '\0';
	return (res);
}
