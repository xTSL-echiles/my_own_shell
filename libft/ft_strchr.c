/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eoddish <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 17:47:22 by eoddish           #+#    #+#             */
/*   Updated: 2020/11/15 20:22:27 by eoddish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strchr(const char *s, int c)
{
	char	*str;
	char	t;

	str = (char *)s;
	t = (char)c;
	while (*str)
	{
		if (t == *str)
			return (str);
		str++;
	}
	if (*str == t)
		return (str);
	return (0);
}
