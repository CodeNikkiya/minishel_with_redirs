/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npavelic <npavelic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 17:21:45 by npavelic          #+#    #+#             */
/*   Updated: 2022/12/22 17:58:05 by npavelic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		i;
	t_list	*neo;

	i = 0;
	neo = lst;
	while (neo != NULL)
	{
		i++;
		neo = neo -> next;
	}
	return (i);
}

// Parameters lst: The beginning of the list.
// Return value The length of the list
// External functs. None
// Description Counts the number of nodes in a list.