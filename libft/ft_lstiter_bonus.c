/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npavelic <npavelic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 08:04:31 by npavelic          #+#    #+#             */
/*   Updated: 2022/12/23 09:08:52 by npavelic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*neo;
	t_list	*onward;

	neo = lst;
	while (neo != NULL)
	{
		onward = neo -> next;
		f (neo -> content);
		neo = onward;
	}
}

/*

Parameters 

lst: The address of a pointer to a node.

f: The address of the function used to iterate on the list.

Return value None
External functs. None

Description: Iterates the list ’lst’ and applies the function
’f’ on the content of each node.

*/