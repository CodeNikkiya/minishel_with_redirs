/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npavelic <npavelic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 09:15:55 by npavelic          #+#    #+#             */
/*   Updated: 2022/12/21 11:06:20 by npavelic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str1)
{
	char	*reza;
	size_t	l;

	l = ft_strlen(str1) + 1;
	reza = malloc (l);
	if (reza == 0)
		return (0);
	return ((char *) ft_memcpy (reza, str1, l));
}
