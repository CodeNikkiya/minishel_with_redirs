/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npavelic <npavelic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 09:37:50 by npavelic          #+#    #+#             */
/*   Updated: 2022/12/26 17:16:23 by npavelic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*reza;
	size_t	orig_len;
	size_t	i;
	size_t	j;

	if (!s)
		return (NULL);
	orig_len = ft_strlen(s);
	if (start > orig_len)
		return (ft_strdup(""));
	if (orig_len - start < len)
		len = orig_len - start;
	reza = malloc(sizeof(char) * (len + 1));
	if (!reza)
		return (NULL);
	i = start;
	j = 0;
	while ((s[i]) && (j < len))
		reza[j++] = s[i++];
	reza[j] = '\0';
	return (reza);
}
