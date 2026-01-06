/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolich <psmolich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 20:38:01 by psmolich          #+#    #+#             */
/*   Updated: 2025/05/23 21:50:07 by psmolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// lst: The address of a pointer to a node.
// f: The address of the function to apply to each
// node’s content.
// Iterates through the list ’lst’ and applies the
// function ’f’ to the content of each node.

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*temp;
	t_list	*curr;

	if (!lst || !f)
		return ;
	curr = lst;
	while (curr)
	{
		temp = curr->next;
		f(curr->content);
		curr = temp;
	}
}
