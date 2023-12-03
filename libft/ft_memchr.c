/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npavelic <npavelic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:44:11 by npavelic          #+#    #+#             */
/*   Updated: 2022/12/24 14:33:11 by npavelic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *ptr, int value, size_t num)
{
	size_t		i;
	const char	*searched_string = ptr;

	i = 0;
	while (i != num)
	{
		if ((unsigned char)searched_string[i] == (unsigned char)value)
			return ((void *)ptr + i);
		i++;
	}
	return (NULL);
}
