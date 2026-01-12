/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolich <psmolich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:05:15 by psmolich          #+#    #+#             */
/*   Updated: 2025/08/10 08:23:55 by psmolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_record_flags(char c, t_spec	*conv)
{
	if (c == '-')
		(*conv).flags.minus++;
	else if (c == '+')
		(*conv).flags.plus++;
	else if (c == ' ')
		(*conv).flags.space++;
	else if (c == '0')
		(*conv).flags.zero++;
	else if (c == '#')
		(*conv).flags.hash++;
}

int	ft_is_conv(const char *format, int *move, t_spec	*conv)
{
	int	i;

	i = 0;
	if (format[i++] == '%')
	{
		while (ft_strchr(FLAGS_CHECK, format[i]))
			ft_record_flags(format[i++], conv);
		while (ft_strchr(DEC, format[i]))
			(*conv).width = (*conv).width * 10 + (format[i++] - '0');
		if (ft_strchr(PRECISION_CHECK, format[i]))
		{
			(*conv).prec.dot = 1;
			i++;
		}
		while (ft_strchr(DEC, format[i]))
			(*conv).prec.len = (*conv).prec.len * 10 + (format[i++] - '0');
		conv->zprec = (conv->prec.dot && conv->prec.len == 0);
		if (ft_strrchr(TYPE_CHECK, format[i]))
		{
			(*conv).type = format[i];
			*move += i;
			return (1);
		}
	}
	return (0);
}
