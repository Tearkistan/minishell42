/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnussler <mnussler@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 23:46:58 by mnussler          #+#    #+#             */
/*   Updated: 2025/06/10 18:31:09 by mnussler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/**
 * @brief Formats character output with width padding and alignment.
 *
 * Generation steps:
 *
 * 1. Calculate width padding requirements (width - 1)
 *
 * 2. Output order: [width_pad] [char] [left_pad]
 *
 * @param opts Format options (flags, width)
 * @param c Character to format
 * @return Characters written, or -1 on error
 */
static int	ft_printf_char_util(t_opts *opts, char c)
{
	int	total_count;
	int	width_pad;
	int	sub_count;

	total_count = 0;
	width_pad = ft_max(0, opts->width - 1);
	if (!opts->left_align)
	{
		sub_count = ft_putpad(width_pad, ' ');
		if (sub_count == -1)
			return (-1);
		total_count += sub_count;
	}
	sub_count = ft_putchar(c);
	if (sub_count == -1)
		return (-1);
	total_count += sub_count;
	if (opts->left_align)
	{
		sub_count = ft_putpad(width_pad, ' ');
		if (sub_count == -1)
			return (-1);
		total_count += sub_count;
	}
	return (total_count);
}

int	ft_printf_char(char c, t_opts *opts)
{
	return (ft_printf_char_util(opts, c));
}
