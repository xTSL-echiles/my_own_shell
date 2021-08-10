/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eoddish <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 20:06:59 by eoddish           #+#    #+#             */
/*   Updated: 2020/11/10 20:54:07 by eoddish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/errno.h>
#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	extern int	errno;
	char		*res;
	size_t		i;
	void		*fnlres;

	i = 0;
	res = malloc(count * size);
	if (!res)
	{
		errno = 12;
		return (0);
	}
	while (i < count * size)
	{
		res[i++] = '\0';
	}
	fnlres = (void *)res;
	ft_bzero(fnlres, count * size);
	return (fnlres);
}
