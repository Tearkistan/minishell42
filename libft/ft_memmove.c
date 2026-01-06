/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolich <psmolich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 21:49:41 by psmolich          #+#    #+#             */
/*   Updated: 2025/05/23 14:04:30 by psmolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t					i;
	unsigned char			*ptr_dest;
	const unsigned char		*ptr_src;

	if (!dest && !src)
		return ((void *)0);
	ptr_dest = (unsigned char *)dest;
	ptr_src = (const unsigned char *)src;
	if (dest <= src)
		ft_memcpy(dest, src, n);
	else
	{
		i = n;
		while (i-- > 0)
			ptr_dest[i] = ptr_src[i];
	}
	return (dest);
}

// void	*ft_memmove(void *dest, const void *src, size_t n)
// {
// 	size_t					i;
// 	unsigned char			*ptr_dest;
// 	const unsigned char		*ptr_src;

// 	if (!dest && !src)
// 		return ((void *)0);
// 	ptr_dest = (unsigned char *)dest;
// 	ptr_src = (const unsigned char *)src;
// 	if (dest <= src)
// 	{
// 		i = 0;
// 		while (i < n)
// 		{
//             ptr_dest[i] = ptr_src[i];
//             i++;
//         }
// 	}
// 	else
// 	{
// 		i = n;
// 		while (i-- > 0)
// 			ptr_dest[i] = ptr_src[i];
// 	}
// 	return (dest);
// }