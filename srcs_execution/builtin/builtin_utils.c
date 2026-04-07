/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twatson <twatson@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 17:02:17 by twatson           #+#    #+#             */
/*   Updated: 2026/04/07 14:35:56 by twatson          ###   ########.fr       */
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
	while (sh->envp && sh->envp[i])
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

/* NOT allocated / return value never to be freed! */
int	shell_check_no_eq(char *key, t_shell *sh)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(key);
	while (sh->no_eq && sh->no_eq[i])
	{
		if (ft_strncmp(key, sh->no_eq[i], len) == 0)
			return (1);
		i++;
	}
	return (0);
}
