/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolich <psmolich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 20:05:09 by psmolich          #+#    #+#             */
/*   Updated: 2025/05/23 21:51:31 by psmolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// lst: The address of a pointer to a node.
// del: The address of the function used to delete
// the content of the node.
// Description Deletes and frees the given node and all its
// successors, using the function ’del’ and free(3).
// Finally, set the pointer to the list to NULL.

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*temp;
	t_list	*curr;

	if (!lst || !*lst || !del)
		return ;
	curr = *lst;
	while (curr)
	{
		temp = curr->next;
		del(curr->content);
		free(curr);
		curr = temp;
	}
	*lst = NULL;
}
