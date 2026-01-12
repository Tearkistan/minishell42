/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnussler <mnussler@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 18:31:23 by mnussler          #+#    #+#             */
/*   Updated: 2025/06/10 18:31:31 by mnussler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/**
 * @brief Formats string output with width padding and alignment.
 *
 * Generation steps:
 *
 * 1. Calculate width padding requirements
 *
 * 2. Output order: [width_pad] [string] [left_pad]
 *
 * 3. Precision limits string length if specified
 *
 *
 * @param opts Format options (flags, width, precision)
 * @param content_len Actual string length to output
 * @param str String content to format
 * @return Characters written, or -1 on error
 */
static int	ft_printf_str_util(t_opts *opts, int content_len, char *str)
{
	int	total_count;
	int	width_pad;
	int	sub_count;

	total_count = 0;
	width_pad = ft_max(0, opts->width - content_len);
	if (!opts->left_align)
	{
		sub_count = ft_putpad(width_pad, ' ');
		if (sub_count == -1)
			return (-1);
		total_count += sub_count;
	}
	sub_count = ft_putlstr(str, content_len);
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

int	ft_printf_str(char *str, t_opts *opts)
{
	int	len;

	if (!str)
		str = STRING_NULL;
	len = ft_strlen(str);
	if (opts->has_precision)
		len = ft_min(len, opts->precision);
	return (ft_printf_str_util(opts, len, str));
}
