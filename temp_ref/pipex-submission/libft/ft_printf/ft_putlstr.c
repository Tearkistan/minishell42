/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putlstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnussler <mnussler@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 20:29:01 by mnussler          #+#    #+#             */
/*   Updated: 2025/06/06 20:29:02 by mnussler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putlstr(char *s, int len)
{
	int	count;

	count = 0;
	while (s[count] && count < len)
	{
		if (ft_putchar(s[count]) == -1)
			return (-1);
		count++;
	}
	return (count);
}
