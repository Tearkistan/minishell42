/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolich <psmolich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 15:42:33 by psmolich          #+#    #+#             */
/*   Updated: 2025/08/27 06:16:23 by psmolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	ft_len(int n)
{
	int	len;

	len = (n <= 0);
	while (n)
	{
		len++;
		n /= 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*nb;
	long	nbr;

	len = ft_len(n);
	nbr = n;
	nb = (char *)malloc(sizeof(char) * (len + 1));
	if (!nb)
		return ((void *)0);
	nb[len] = '\0';
	if (nbr < 0)
	{
		nb[0] = '-';
		nbr = -nbr;
	}
	if (nbr == 0)
		nb[0] = '0';
	while (nbr)
	{
		nb[--len] = nbr % 10 + '0';
		nbr /= 10;
	}
	return (nb);
}
