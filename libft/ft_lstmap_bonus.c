/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npavelic <npavelic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 09:21:14 by npavelic          #+#    #+#             */
/*   Updated: 2022/12/23 14:13:36 by npavelic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*neo;
	t_list	*reza;

	if ((lst == NULL) || ((f == NULL) && (del == NULL)))
		return (NULL);
	reza = ft_lstnew (f(lst -> content));
	neo = lst -> next;
	while (neo)
	{
		ft_lstadd_back(&reza, ft_lstnew(f(neo -> content)));
		if (reza == NULL && del != NULL)
		{
			ft_lstclear(&reza, del);
			return (NULL);
		}
		neo = neo -> next;
	}
	return (reza);
}

/*

Parameters:
lst: The address of a pointer to a node.

f: The address of the function used to iterate on the list.

del: The address of the function used to delete the content of a node if needed.


Return value: The new list. NULL if the allocation fails.

External functs. malloc, free

Description: Iterates the list ’lst’ and applies the function
’f’ on the content of each node. Creates a new
list resulting of the successive applications of
the function ’f’. The ’del’ function is used to
delete the content of a node if needed.

*/
