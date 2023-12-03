/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npavelic <npavelic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 19:12:18 by npavelic          #+#    #+#             */
/*   Updated: 2022/12/26 17:15:51 by npavelic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	j;
	size_t	i;

	if (little[0] == '\0')
		return ((char *)big);
	i = 0;
	while (i < len && big[i])
	{
		j = 0;
		while ((i < len) && (little[j]) && (big[i]) && (little[j] == big[i]))
		{
			++j;
			++i;
		}
		if (little[j] == '\0')
			return ((char *)&big[i - j]);
		i = i - j + 1;
	}
	return (0);
}
