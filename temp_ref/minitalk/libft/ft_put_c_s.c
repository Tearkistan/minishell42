/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_c_s.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolich <psmolich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 11:27:28 by psmolich          #+#    #+#             */
/*   Updated: 2025/08/27 06:20:59 by psmolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

int	ft_putchar_rv(char c)
{
	return (write(1, &c, 1));
}

void	ft_putchar_rvf(char c, t_spec *conv, int *p_count)
{
	conv->width--;
	if (!conv->flags.minus)
		ft_padding(conv->width, p_count, ' ');
	*p_count += ft_putchar_rv(c);
	if (conv->flags.minus)
		ft_padding(conv->width, p_count, ' ');
}

void	ft_putstr_rvf(char *str, t_spec *conv, int *p_count)
{
	int		strlen;
	int		printlen;
	int		i;

	if (!str)
	{
		if (conv->prec.dot && conv->prec.len < 6)
			ft_putstr_rvf("", conv, p_count);
		else
			ft_putstr_rvf("(null)", conv, p_count);
		return ;
	}
	strlen = ft_strlen(str);
	printlen = !conv->prec.dot * strlen + conv->prec.dot * (conv->prec.len
			- (conv->prec.len > strlen) * (conv->prec.len - strlen));
	conv->width -= printlen;
	if (!conv->flags.minus)
		ft_padding(conv->width, p_count, ' ');
	i = 0;
	while (str[i] && i < printlen)
		*p_count += ft_putchar_rv(str[i++]);
	if (conv->flags.minus)
		ft_padding(conv->width, p_count, ' ');
}
