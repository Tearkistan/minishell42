/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolich <psmolich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 03:56:40 by psmolich          #+#    #+#             */
/*   Updated: 2025/08/12 06:23:19 by psmolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// str needs to be provided as an address of a previously allocated string
int	ft_strdel(char **str, char *pattern)
{
	char	*new_str;
	char	*src;
	int		pat_len;
	int		i;

	if (!str || !*str || !pattern || !*pattern)
		return (-1);
	src = *str;
	pat_len = ft_strlen(pattern);
	new_str = malloc(sizeof(char) * (ft_strlen(src)
				- ft_strstr_count(src, pattern) * pat_len + 1));
	if (!new_str)
		return (-1);
	i = 0;
	while (*src)
	{
		if (ft_strncmp(src, pattern, pat_len) == 0)
			src += pat_len;
		new_str[i++] = *src++;
	}
	new_str[i] = '\0';
	free(*str);
	*str = new_str;
	return (0);
}
