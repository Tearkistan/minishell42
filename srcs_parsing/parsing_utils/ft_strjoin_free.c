/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolich <psmolich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:58:18 by psmolich          #+#    #+#             */
/*   Updated: 2026/02/16 11:37:24 by psmolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// S1 and s2 must be allocated.
// In case of error, both will be freed and NULL returned,
// so the caller should check for NULL
// and not use s1 or s2 after calling this function.
// Joins two strings and frees them. Returns the newly allocated string.
char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*ret;

	if (!s1 || !s2)
		return (NULL);
	ret = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (ret);
}
