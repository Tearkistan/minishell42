/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnussler <mnussler@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 04:15:00 by mnussler          #+#    #+#             */
/*   Updated: 2025/06/10 01:57:18 by mnussler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_putunbr_recursive(size_t n, char *base)
{
	int		count;
	ssize_t	result;
	size_t	base_len;

	base_len = ft_strlen(base);
	count = 0;
	if (n >= base_len)
	{
		result = ft_putunbr_recursive(n / base_len, base);
		if (result == -1)
			return (-1);
		count += result;
	}
	if (ft_putchar(base[n % base_len]) == -1)
		return (-1);
	count++;
	return (count);
}

int	ft_putunbr(size_t n, char *base)
{
	return (ft_putunbr_recursive(n, base));
}
