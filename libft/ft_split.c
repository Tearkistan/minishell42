/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolich <psmolich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 19:16:04 by psmolich          #+#    #+#             */
/*   Updated: 2025/06/08 17:44:56 by psmolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(char const *s, char c)
{
	int	i;
	int	count;

	if (!s[0])
		return (0);
	i = 0;
	count = (s[i] != c);
	while (s[i])
	{
		while (s[i] && s[i] != c)
			i++;
		while (s[i] && s[i] == c)
		{
			if (s[i + 1] && s[i + 1] != c)
				count++;
			i++;
		}
	}
	return (count);
}

static char	*ft_strdup_split(char **str_ptr, char c)
{
	char	*dup;
	int		i;
	int		j;

	i = 0;
	while ((*str_ptr)[i] && (*str_ptr)[i] == c)
		i++;
	*str_ptr += i;
	i = 0;
	while ((*str_ptr)[i] && (*str_ptr)[i] != c)
		i++;
	dup = (char *)malloc(sizeof(char) * (i + 1));
	if (!dup)
		return ((void *)0);
	j = 0;
	while (j < i)
	{
		dup[j] = (*str_ptr)[j];
		j++;
	}
	dup[i] = '\0';
	*str_ptr += i;
	return (dup);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	int		i;
	char	*str_ptr;
	int		count_words;

	count_words = ft_count_words(s, c);
	array = (char **)malloc(sizeof(char *) * (count_words + 1));
	if (!array)
		return ((void *)0);
	str_ptr = (char *)s;
	i = 0;
	while (i < count_words)
	{
		array[i] = ft_strdup_split(&str_ptr, c);
		if (!array[i])
		{
			while (--i >= 0)
				free(array[i]);
			free(array);
			return ((void *)0);
		}
		i++;
	}
	array[count_words] = (void *)0;
	return (array);
}
