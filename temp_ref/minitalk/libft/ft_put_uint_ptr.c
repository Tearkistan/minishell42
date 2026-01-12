/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_uint_ptr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolich <psmolich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 12:17:21 by psmolich          #+#    #+#             */
/*   Updated: 2025/08/26 18:10:58 by psmolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_unblen_base(uintptr_t nb, uintptr_t base_len)
{
	int	i;

	i = (nb == 0);
	while (nb)
	{
		i++;
		nb /= base_len;
	}
	return (i);
}

void	ft_putunb_base(uintptr_t nb, char *base, int *p_count)
{
	uintptr_t	base_len;

	base_len = ft_strlen(base);
	if (nb >= base_len)
		ft_putunb_base(nb / base_len, base, p_count);
	*p_count += ft_putchar_rv(base[(nb % base_len)]);
}

void	ft_putptr_rvf(uintptr_t ptr, t_spec *conv, int *p_count)
{
	if (ptr == 0)
	{
		ft_putstr_rvf("(nil)", conv, p_count);
		return ;
	}
	conv->width -= 2 + ft_unblen_base(ptr, HEX_LEN);
	if (!conv->flags.minus)
		ft_padding(conv->width, p_count, ' ');
	*p_count += ft_putchar_rv('0') + ft_putchar_rv('x');
	ft_putunb_base(ptr, HEX, p_count);
	if (conv->flags.minus)
		ft_padding(conv->width, p_count, ' ');
}

void	ft_putuint_base_rvf(unsigned int nb, char *base,
	t_spec *conv, int *p_count)
{
	int	nblen;

	nblen = ft_unblen_base(nb, ft_strlen(base));
	conv->prec.len = (conv->prec.len > nblen) * (conv->prec.len - nblen);
	conv->width -= nblen - (conv->zprec && !nb)
		+ 2 * (conv->flags.hash && nb > 0) + conv->prec.len;
	conv->width *= (conv->width > 0);
	if (!conv->flags.minus && !conv->flags.zero)
		ft_padding(conv->width, p_count, ' ');
	if (conv->flags.hash && nb > 0 && ft_strncmp(base, HEX, HEX_LEN) == 0)
		*p_count += ft_putchar_rv('0') + ft_putchar_rv('x');
	if (conv->flags.hash && nb > 0 && ft_strncmp(base, HEX_B, HEX_LEN) == 0)
		*p_count += ft_putchar_rv('0') + ft_putchar_rv('X');
	if (conv->flags.zero)
		ft_padding(conv->width, p_count, '0');
	if (conv->prec.dot && conv->prec.len)
		ft_padding(conv->prec.len, p_count, '0');
	if (!(conv->zprec && nb == 0))
		ft_putunb_base(nb, base, p_count);
	if (conv->flags.minus)
		ft_padding(conv->width, p_count, ' ');
}
