/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolich <psmolich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 19:54:47 by psmolich          #+#    #+#             */
/*   Updated: 2025/08/27 06:27:05 by psmolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *s, int c)
{
	unsigned int	i;
	unsigned char	d;

	d = (unsigned char) c;
	i = 0;
	while (s[i])
	{
		if (s[i] == d)
			return ((char *)(s + i));
		i++;
	}
	if (d == 0)
		return ((char *)(s + i));
	return ((void *)0);
}
