/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eoddish <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 17:48:03 by eoddish           #+#    #+#             */
/*   Updated: 2020/11/23 20:08:54 by eoddish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static char	*ft_start_is_out(void)
{
	char	*res;

	res = malloc(1);
	res[0] = '\0';
	return (res);
}

char	*ft_substr(char const *s, unsigned int start,
size_t len)
{
	char	*res;
	size_t	i;
	size_t	n;

	if (!s)
		return (0);
	i = 0;
	if (start >= ft_strlen(s))
		return (ft_start_is_out());
	n = ft_strlen(s + start);
	if (len < n)
		res = malloc(len + 1);
	else
		res = malloc(n + 1);
	if (!res)
		return (0);
	while (s[start] && len)
	{
		res[i++] = s[start++];
		len--;
	}
	res[i] = '\0';
	return (res);
}
