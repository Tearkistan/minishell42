/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putpad.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnussler <mnussler@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 00:42:02 by mnussler          #+#    #+#             */
/*   Updated: 2025/06/07 00:42:19 by mnussler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putpad(int count, char pad_char)
{
	int	total;

	total = 0;
	while (count > 0)
	{
		if (ft_putchar(pad_char) == -1)
			return (-1);
		total++;
		count--;
	}
	return (total);
}
