/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolich <psmolich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 11:29:48 by psmolich          #+#    #+#             */
/*   Updated: 2025/06/18 15:05:04 by psmolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static uintptr_t	ft_abs(long value)
{
	return (((value < 0) * (-value)) + ((value >= 0) * value));
}

static void	ft_sign(int nb, t_spec *conv, int *p_count)
{
	if (nb < 0)
		*p_count += ft_putchar_rv('-');
	else if (conv->flags.plus && nb >= 0)
		*p_count += ft_putchar_rv('+');
	else if (conv->flags.space && nb >= 0)
		*p_count += ft_putchar_rv(' ');
}

void	ft_putint_base_rvf(int nb, char *base, t_spec *conv, int *p_count)
{
	int	nblen;
	int	sign;

	sign = ((nb < 0) || conv->flags.plus || conv->flags.space);
	nblen = ft_unblen_base(ft_abs(nb), ft_strlen(base));
	conv->prec.len = (conv->prec.len > nblen) * (conv->prec.len - nblen);
	conv->width -= nblen + sign + conv->prec.len - (conv->zprec && nb == 0);
	conv->width *= (conv->width > 0);
	if (!conv->flags.minus && !conv->flags.zero)
		ft_padding(conv->width, p_count, ' ');
	ft_sign(nb, conv, p_count);
	if (conv->flags.zero)
		ft_padding(conv->width, p_count, '0');
	if (conv->prec.dot && conv->prec.len)
		ft_padding(conv->prec.len, p_count, '0');
	if (!(conv->zprec && nb == 0))
		ft_putunb_base(ft_abs(nb), base, p_count);
	if (conv->flags.minus)
		ft_padding(conv->width, p_count, ' ');
}
