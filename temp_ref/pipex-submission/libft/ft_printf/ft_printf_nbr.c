/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_nbr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnussler <mnussler@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 18:20:44 by mnussler          #+#    #+#             */
/*   Updated: 2025/06/10 18:34:42 by mnussler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf_nbr(int n, t_opts *opts)
{
	unsigned int	u_num;
	char			*prefix_str;

	prefix_str = "";
	if (n < 0)
	{
		prefix_str = "-";
		u_num = (unsigned int)(-(long)n);
	}
	else
	{
		if (opts->plus_sign)
			prefix_str = "+";
		else if (opts->space_prefix)
			prefix_str = " ";
		u_num = n;
	}
	return (ft_printf_unbr_util(opts, prefix_str, u_num, DECIMAL_BASE));
}
