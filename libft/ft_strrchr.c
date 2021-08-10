/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eoddish <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 18:19:01 by eoddish           #+#    #+#             */
/*   Updated: 2020/11/15 20:26:24 by eoddish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*str;
	char	t;
	int		i;

	str = (char *)s;
	t = (char)c;
	i = ft_strlen(str);
	str = str + i;
	while (i + 1)
	{
		if (*str == t)
			return (str);
		i--;
		str--;
	}
	return (0);
}
