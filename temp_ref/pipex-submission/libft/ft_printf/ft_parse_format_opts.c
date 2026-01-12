/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_format_opts.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnussler <mnussler@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 01:00:00 by mnussler          #+#    #+#             */
/*   Updated: 2025/06/06 20:17:48 by mnussler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_init_opts(t_opts *opts)
{
	opts->left_align = 0;
	opts->zero_pad = 0;
	opts->plus_sign = 0;
	opts->space_prefix = 0;
	opts->hash_prefix = 0;
	opts->width = 0;
	opts->precision = 0;
	opts->has_precision = 0;
	return (0);
}

static int	ft_parse_single_opt(char c, t_opts *opts)
{
	if (c == '-')
		opts->left_align = 1;
	else if (c == '0')
		opts->zero_pad = 1;
	else if (c == '+')
		opts->plus_sign = 1;
	else if (c == ' ')
		opts->space_prefix = 1;
	else if (c == '#')
		opts->hash_prefix = 1;
	else
		return (0);
	return (1);
}

static int	ft_parse_width(const char *format, int *pos, t_opts *opts)
{
	int	width;

	width = 0;
	while (format[*pos] && ft_isdigit(format[*pos]))
	{
		width = width * 10 + (format[*pos] - '0');
		(*pos)++;
	}
	opts->width = width;
	return (width > 0);
}

static int	ft_parse_precision(const char *format, int *pos, t_opts *opts)
{
	int	precision;

	if (format[*pos] != '.')
		return (0);
	(*pos)++;
	opts->has_precision = 1;
	precision = 0;
	while (format[*pos] && ft_isdigit(format[*pos]))
	{
		precision = precision * 10 + (format[*pos] - '0');
		(*pos)++;
	}
	opts->precision = precision;
	return (1);
}

int	ft_parse_format_opts(const char *format, int *pos, t_opts *opts)
{
	int	start_pos;

	start_pos = *pos;
	ft_init_opts(opts);
	(*pos)++;
	while (format[*pos] && ft_parse_single_opt(format[*pos], opts))
		(*pos)++;
	if (format[*pos] && ft_isdigit(format[*pos]))
		ft_parse_width(format, pos, opts);
	if (format[*pos] && format[*pos] == '.')
		ft_parse_precision(format, pos, opts);
	if (!format[*pos] || !ft_strchr(ALLOWED_FORMAT_SPECIFIERS, format[*pos]))
		return (-1);
	return (*pos - start_pos);
}
