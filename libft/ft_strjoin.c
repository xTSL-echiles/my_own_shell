/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eoddish <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 19:55:37 by eoddish           #+#    #+#             */
/*   Updated: 2020/11/23 20:10:24 by eoddish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	size_t	n1;
	size_t	n2;
	size_t	i;

	if (!s1 || !s2)
		return (0);
	n1 = ft_strlen(s1);
	n2 = ft_strlen(s2);
	i = 0;
	res = malloc(n1 + n2 + 1);
	if (!res)
		return (0);
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	while (s2[i - n1])
	{
		res[i] = s2[i - n1];
		i++;
	}
	res[i] = '\0';
	return (res);
}
