/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eoddish <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 18:34:20 by eoddish           #+#    #+#             */
/*   Updated: 2020/11/23 18:28:31 by eoddish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static char	*ft_iszero(void)
{
	char	*res;

	res = malloc(sizeof(char) * 2);
	res[0] = '0';
	res[1] = '\0';
	return (res);
}

static int	ft_size(int nbr)
{
	int	cnt;

	cnt = 0;
	if (nbr < 0)
		cnt++;
	while (nbr)
	{
		nbr = nbr / 10;
		cnt++;
	}
	return (cnt);
}

char	*ft_itoa(int n)
{
	int		cnt;
	char	*res;

	if (n == 0)
		return (ft_iszero());
	cnt = ft_size(n);
	res = malloc(sizeof(char) * (cnt + 1));
	if (!res)
		return (0);
	res[cnt] = '\0';
	if (n < 0)
		res[0] = '-';
	while (n)
	{
		if (n < 0)
			res[cnt - 1] = '0' - n % 10;
		else
			res[cnt - 1] = '0' + n % 10;
		n = n / 10;
		cnt--;
	}
	return (res);
}
