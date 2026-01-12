/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_unbr_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnussler <mnussler@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 18:25:41 by mnussler          #+#    #+#             */
/*   Updated: 2025/06/10 18:39:00 by mnussler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/**
 * @brief Preprocesses unsigned numeric formatting requirements.
 *
 * Calculates all padding and length requirements for unsigned numeric output.
 *
 * @param opts Format options (flags, width, precision)
 * @param prefix_str Sign/prefix string
 * @param n Unsigned numeric value
 * @param base Number base for conversion
 */
static t_num_opts	preprocess_options(t_opts *opts, char *prefix_str, size_t n,
		char *base)
{
	t_num_opts	num_opts;

	num_opts.left_align = opts->left_align;
	num_opts.zero_pad = opts->zero_pad;
	num_opts.has_precision = opts->has_precision;
	num_opts.number = n;
	num_opts.base = base;
	num_opts.prefix_str = prefix_str;
	num_opts.prefix_len = ft_strlen(prefix_str);
	num_opts.content_len = ft_unsigned_numlen(n, ft_strlen(base));
	if (n == 0 && opts->has_precision && opts->precision == 0)
		num_opts.content_len = 0;
	num_opts.precision_pad = ft_max(0, opts->precision - num_opts.content_len);
	num_opts.width_pad = ft_max(0, opts->width - (num_opts.content_len
				+ num_opts.precision_pad + num_opts.prefix_len));
	return (num_opts);
}

/**
 * @brief Prints prefix and initial padding.
 *
 * @param num_opts Processed format options containing padding info
 * @return Characters written, or -1 on error
 */
static int	print_prefix_with_padding(t_num_opts *num_opts)
{
	int	count;
	int	res;

	count = 0;
	if (!num_opts->left_align && (num_opts->has_precision
			|| !num_opts->zero_pad))
	{
		res = ft_putpad(num_opts->width_pad, ' ');
		if (res == -1)
			return (-1);
		count += res;
	}
	if (num_opts->prefix_len > 0)
	{
		res = ft_putlstr(num_opts->prefix_str, num_opts->prefix_len);
		if (res == -1)
			return (-1);
		count += res;
	}
	return (count);
}

/**
 * @brief Prints unsigned numeric content with precision padding.
 *
 * @param num_opts Processed format options containing number and padding info
 * @return Characters written, or -1 on error
 */
static int	print_unsigned_number_with_precision(t_num_opts *num_opts)
{
	int	count;
	int	res;

	count = 0;
	if (!num_opts->left_align && num_opts->zero_pad && !num_opts->has_precision)
	{
		res = ft_putpad(num_opts->width_pad, '0');
		if (res == -1)
			return (-1);
		count += res;
	}
	res = ft_putpad(num_opts->precision_pad, '0');
	if (res == -1)
		return (-1);
	count += res;
	if (num_opts->content_len > 0)
	{
		res = ft_putunbr(num_opts->number, num_opts->base);
		if (res == -1)
			return (-1);
		count += res;
	}
	return (count);
}

/**
 * @brief Prints formatted unsigned numeric output with error handling.
 *
 * @param num_opts Processed format options containing padding and number info
 * @return Characters written, or -1 on error
 */
static int	print_formatted_unsigned_num(t_num_opts *num_opts)
{
	int	count;
	int	res;

	count = 0;
	res = print_prefix_with_padding(num_opts);
	if (res == -1)
		return (-1);
	count += res;
	res = print_unsigned_number_with_precision(num_opts);
	if (res == -1)
		return (-1);
	count += res;
	if (num_opts->left_align)
	{
		res = ft_putpad(num_opts->width_pad, ' ');
		if (res == -1)
			return (-1);
		count += res;
	}
	return (count);
}

int	ft_printf_unbr_util(t_opts *opts, char *prefix_str, size_t n, char *base)
{
	t_num_opts	num_opts;

	num_opts = preprocess_options(opts, prefix_str, n, base);
	return (print_formatted_unsigned_num(&num_opts));
}
