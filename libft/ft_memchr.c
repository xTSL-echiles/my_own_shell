/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eoddish <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 20:18:04 by eoddish           #+#    #+#             */
/*   Updated: 2020/11/19 22:15:50 by eoddish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char		*str;
	unsigned char			t;

	t = (unsigned char)c;
	str = (unsigned char *)s;
	while (n--)
	{
		if (*str++ == t)
		{
			str--;
			return ((void *)str);
		}
	}
	return (0);
}
