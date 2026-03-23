/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolich <psmolich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 17:02:17 by twatson           #+#    #+#             */
/*   Updated: 2026/03/23 07:59:56 by psmolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/* NOT allocated / return value never to be freed! */
char	*shell_getenv(char *key, t_shell *sh)
{
	char	*ptr_to_value;
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(key);
	while (sh->envp[i])
	{
		if (ft_strncmp(key, sh->envp[i], len) == 0 && sh->envp[i][len] == '=')
		{
			ptr_to_value = ft_strchr(sh->envp[i], '=') + 1;
			return (ptr_to_value);
		}
		i++;
	}
	return (NULL);
}
