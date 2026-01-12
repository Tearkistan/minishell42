/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolich <psmolich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 04:36:07 by psmolich          #+#    #+#             */
/*   Updated: 2025/08/26 18:10:27 by psmolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// str needs to be provided as an address of a previously allocated string
static void	copy_with_replace(char *dst, char *src, char *del, char *rep)
{
	int		i;
	int		j;
	int		del_len;
	int		rep_len;

	del_len = ft_strlen(del);
	rep_len = ft_strlen(rep);
	i = 0;
	while (*src)
	{
		if (ft_strncmp(src, del, del_len) == 0)
		{
			src += del_len;
			j = 0;
			while (j < rep_len)
				dst[i++] = rep[j++];
		}
		else
			dst[i++] = *src++;
	}
	dst[i] = '\0';
}

int	ft_strrep(char **str, char *del, char *rep)
{
	char	*new_str;

	if (!str || !*str || !del || !*del || !*rep)
		return (-1);
	if (!*rep)
		return (ft_strdel(str, del));
	if (ft_strcmp(del, rep) == 0)
		return (0);
	new_str = malloc(sizeof(char) * (ft_strlen(*str)
				+ ft_strstr_count(*str, del)
				* (ft_strlen(rep) - ft_strlen(del)) + 1));
	if (!new_str)
		return (-1);
	copy_with_replace(new_str, *str, del, rep);
	free(*str);
	*str = new_str;
	return (0);
}
