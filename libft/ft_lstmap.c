/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolich <psmolich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 20:41:26 by psmolich          #+#    #+#             */
/*   Updated: 2025/05/24 12:04:53 by psmolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// lst: The address of a pointer to a node.
// f: The address of the function applied to each
// node’s content.
// del: The address of the function used to delete a
// node’s content if needed.
// Return value The new list.
// NULL if the allocation fails.
// External functs. malloc, free

// Description Iterates through the list ’lst’, applies the
// function ’f’ to each node’s content, and creates
// a new list resulting of the successive applications
// of the function ’f’. The ’del’ function is used to
// delete the content of a node if needed.

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlst;
	t_list	*newnode;
	void	*newcontent;

	if (!lst || !f || !del)
		return (NULL);
	newlst = NULL;
	while (lst)
	{
		newcontent = f(lst->content);
		newnode = ft_lstnew(newcontent);
		if (!newnode)
		{
			del(newcontent);
			ft_lstclear(&newlst, del);
			return (NULL);
		}
		ft_lstadd_back(&newlst, newnode);
		lst = lst->next;
	}
	return (newlst);
}
