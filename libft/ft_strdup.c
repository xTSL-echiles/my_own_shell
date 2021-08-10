/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eoddish <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 21:11:48 by eoddish           #+#    #+#             */
/*   Updated: 2021/05/27 21:21:50 by eoddish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <sys/errno.h>
#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	char	*pst;
	size_t	size;
	int		i;

	i = 0;
	size = ft_strlen((char *)s1) + 1;
	pst = (char *)malloc(sizeof(char) * size + 1);
	if (!(pst))
		return (NULL);
	while (s1 && s1[i])
	{
		pst[i] = s1[i];
		i++;
	}
	pst[i] = '\0';
	return (pst);
}
