/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnussler <mnussler@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 04:18:03 by mnussler          #+#    #+#             */
/*   Updated: 2025/06/10 18:32:11 by mnussler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_process_regular_char(char c, int *pos);
static int	ft_process_format_specifier(const char *format, int *pos,
				va_list *args);
static int	ft_print_format_specifier(char c, va_list *args, t_opts *options);

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		pos;
	int		sub_count;
	int		total_count;

	if (!format)
		return (-1);
	va_start(args, format);
	total_count = 0;
	pos = 0;
	while (format[pos])
	{
		if (format[pos] == '%')
			sub_count = ft_process_format_specifier(format, &pos, &args);
		else
			sub_count = ft_process_regular_char(format[pos], &pos);
		if (sub_count == -1)
			return (-1);
		total_count += sub_count;
	}
	va_end(args);
	return (total_count);
}

static int	ft_process_regular_char(char c, int *pos)
{
	if (ft_putchar(c) == -1)
		return (-1);
	(*pos)++;
	return (1);
}

static int	ft_process_format_specifier(const char *format, int *pos,
		va_list *args)
{
	int		count;
	t_opts	options;

	if (ft_parse_format_opts(format, pos, &options) == -1)
		return (-1);
	count = ft_print_format_specifier(format[*pos], args, &options);
	if (count == -1)
		return (-1);
	(*pos)++;
	return (count);
}

static int	ft_print_format_specifier(char c, va_list *args, t_opts *options)
{
	int	count;

	if (!ft_strchr(ALLOWED_FORMAT_SPECIFIERS, c))
		return (-1);
	count = 0;
	if (c == 'c')
		count = ft_printf_char(va_arg(*args, int), options);
	else if (c == 's')
		count = ft_printf_str(va_arg(*args, char *), options);
	else if (c == 'p')
		count = ft_printf_ptr(va_arg(*args, void *), options);
	else if (c == 'd' || c == 'i')
		count = ft_printf_nbr(va_arg(*args, int), options);
	else if (c == 'u')
		count = ft_printf_unbr(va_arg(*args, unsigned int), options);
	else if (c == 'x' || c == 'X')
		count = ft_printf_hex(va_arg(*args, unsigned int), options, c);
	else if (c == '%')
		count = ft_putchar('%');
	else
		return (-1);
	return (count);
}
