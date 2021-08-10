/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eoddish <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 18:51:03 by eoddish           #+#    #+#             */
/*   Updated: 2020/11/23 21:05:27 by eoddish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	int		i;
	int		n;
	char	*str;

	str = (char *)haystack;
	if (ft_strlen(needle) == 0)
		return (str);
	if (len == 0)
		return (0);
	while (*str && len)
	{
		i = 0;
		n = len;
		while (n && needle[i] && str[i] == needle[i])
		{
			i++;
			n--;
		}
		if (needle[i] == '\0')
			return (str);
		str++;
		len--;
	}
	return (0);
}
