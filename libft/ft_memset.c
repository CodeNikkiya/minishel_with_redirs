/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npavelic <npavelic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 09:45:34 by npavelic          #+#    #+#             */
/*   Updated: 2022/12/21 09:45:34 by npavelic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, register int c, size_t n)
{
	register unsigned char	*mid;

	mid = (unsigned char *)str;
	while (n-- > 0)
		*mid++ = c;
	return (str);
}
