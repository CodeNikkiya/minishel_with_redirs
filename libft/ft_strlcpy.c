/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npavelic <npavelic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 08:29:05 by npavelic          #+#    #+#             */
/*   Updated: 2022/12/26 17:15:26 by npavelic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t siz)
{
	size_t	src_len;

	src_len = ft_strlen(src);
	if (siz == 0)
		return (src_len);
	if (src_len < siz)
	{
		ft_memcpy(dst, src, src_len + 1);
		return (src_len);
	}
	ft_memcpy(dst, src, siz - 1);
	dst[siz - 1] = '\0';
	return (src_len);
}
