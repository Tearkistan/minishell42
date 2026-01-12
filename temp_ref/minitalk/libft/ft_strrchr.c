/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolich <psmolich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 20:02:24 by psmolich          #+#    #+#             */
/*   Updated: 2025/08/27 06:30:20 by psmolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	int				i;
	unsigned char	d;

	d = (unsigned char) c;
	i = 0;
	while (s[i])
		i++;
	if (d == 0)
		return ((char *)(s + i));
	while (i >= 0)
	{
		if (s[i] == d)
			return ((char *)(s + i));
		i--;
	}
	return ((void *)0);
}
