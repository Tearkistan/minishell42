/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolich <psmolich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 14:20:51 by psmolich          #+#    #+#             */
/*   Updated: 2025/08/27 06:25:37 by psmolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdarg.h>

void	ft_padding(int n, int *p_count, char c)
{
	while (n-- > 0)
		*p_count += ft_putchar_rv(c);
}

static void	ft_ignore_flags(t_spec *conv)
{
	if ((conv->flags.zero && conv->flags.minus)
		|| (conv->flags.zero && conv->prec.dot))
		conv->flags.zero = 0;
	if (conv->flags.space && conv->flags.plus)
		conv->flags.space = 0;
	if (conv->flags.hash && conv->type == 'u')
		conv->flags.hash = 0;
}

static void	ft_printformat(t_spec *conv, va_list arg, int *p_count)
{
	ft_ignore_flags(conv);
	if (conv->type == 'c')
		ft_putchar_rvf(va_arg(arg, int), conv, p_count);
	else if (conv->type == 's')
		ft_putstr_rvf(va_arg(arg, char *), conv, p_count);
	else if (conv->type == 'p')
		ft_putptr_rvf((uintptr_t)va_arg(arg, void *), conv, p_count);
	else if (conv->type == 'd' || conv->type == 'i')
		ft_putint_base_rvf(va_arg(arg, int), DEC, conv, p_count);
	else if (conv->type == 'u')
		ft_putuint_base_rvf(va_arg(arg, unsigned int), DEC, conv, p_count);
	else if (conv->type == 'x')
		ft_putuint_base_rvf(va_arg(arg, unsigned int), HEX, conv, p_count);
	else if (conv->type == 'X')
		ft_putuint_base_rvf(va_arg(arg, unsigned int), HEX_B, conv, p_count);
	else if (conv->type == 'b')
		ft_putuint_base_rvf(va_arg(arg, unsigned int), "01", conv, p_count);
	else if (conv->type == '%')
		*p_count += ft_putchar_rv('%');
}

int	ft_printf(const char *format, ...)
{
	va_list	arg;
	t_spec	conv;
	int		p_count;
	int		i;

	if (!format)
		return (-1);
	p_count = 0;
	i = 0;
	va_start(arg, format);
	while (format[i])
	{
		ft_memset(&conv, 0, sizeof(conv));
		if (ft_is_conv(format + i, &i, &conv))
			ft_printformat(&conv, arg, &p_count);
		else
			p_count += ft_putchar_rv(format[i]);
		i++;
	}
	va_end(arg);
	return (p_count);
}
