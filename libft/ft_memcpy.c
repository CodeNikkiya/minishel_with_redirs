/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npavelic <npavelic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 09:51:29 by npavelic          #+#    #+#             */
/*   Updated: 2022/12/21 09:51:29 by npavelic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Copies count bytes from the object pointed to by src
// to the object pointed to by dest. 
// Both objects are reinterpreted as arrays of unsigned char.
// If the objects overlap, the behavior is undefined.
// If either dest or src is an invalid or null pointer,
// the behavior is undefined, even if count is zero.

char	*ft_memcpy(void *destination, const void *source, size_t num)
{
	size_t		i;
	char		*d;
	const char	*s = (const char *) source;

	i = 0;
	d = (char *)destination;
	if (d < s)
	{
		i = 0;
		while (i < num)
		{
			d[i] = s[i];
			i++;
		}
	}
	else if (d > s)
	{
		i = num;
		while (i > 0)
		{
			d[i - 1] = s[i - 1];
			i--;
		}
	}
	return (destination);
}
