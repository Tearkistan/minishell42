/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_ptr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnussler <mnussler@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 18:22:07 by mnussler          #+#    #+#             */
/*   Updated: 2025/06/10 18:34:55 by mnussler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf_ptr(void *ptr, t_opts *opts)
{
	size_t	addr;
	char	*prefix_str;

	if (!ptr)
		return (ft_putlstr(POINTER_NULL, ft_strlen(POINTER_NULL)));
	prefix_str = "0x";
	if (opts->plus_sign)
		prefix_str = "+0x";
	else if (opts->space_prefix)
		prefix_str = " 0x";
	addr = (size_t)ptr;
	return (ft_printf_unbr_util(opts, prefix_str, addr, HEX_LOWER_BASE));
}
