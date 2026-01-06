/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bitcount.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolich <psmolich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 07:58:45 by psmolich          #+#    #+#             */
/*   Updated: 2025/08/10 08:02:35 by psmolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_bitcount(int nbr)
{
	int	max_bits;

	max_bits = 0;
	while ((nbr >> max_bits) != 0)
		max_bits++;
	return (max_bits);
}
