/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npavelic <npavelic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 20:05:35 by npavelic          #+#    #+#             */
/*   Updated: 2022/12/26 17:14:05 by npavelic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*neo;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	neo = *lst;
	neo = ft_lstlast(*lst);
	neo -> next = new;
}

// lst: The address of a pointer to the first link of
// a list.
// new: The address of a pointer to the node to be
// added to the list.

// Adds the node ’new’ at the end of the list.
