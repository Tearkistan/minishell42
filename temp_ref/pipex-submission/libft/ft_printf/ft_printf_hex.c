/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnussler <mnussler@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 18:21:56 by mnussler          #+#    #+#             */
/*   Updated: 2025/06/10 18:34:51 by mnussler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf_hex(unsigned int n, t_opts *opts, char c)
{
	char	*prefix_str;

	prefix_str = "";
	if (c == 'x')
	{
		if (opts->hash_prefix && n != 0)
			prefix_str = HEX_LOWER_PREFIX;
		return (ft_printf_unbr_util(opts, prefix_str, n, HEX_LOWER_BASE));
	}
	if (c == 'X')
	{
		if (opts->hash_prefix && n != 0)
			prefix_str = HEX_UPPER_PREFIX;
		return (ft_printf_unbr_util(opts, prefix_str, n, HEX_UPPER_BASE));
	}
	return (-1);
}
