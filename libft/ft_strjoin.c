/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npavelic <npavelic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 11:28:14 by npavelic          #+#    #+#             */
/*   Updated: 2022/12/26 17:15:22 by npavelic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*string_new;
	size_t	len_new;
	size_t	i;
	size_t	j;

	len_new = ft_strlen (s1) + ft_strlen (s2);
	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	string_new = (char *)malloc (sizeof(char) * (len_new + 1));
	if (!string_new)
		return (NULL);
	while (s1[i])
		string_new[j++] = s1[i++];
	i = 0;
	while (s2[i])
		string_new[j++] = s2[i++];
	string_new[j] = '\0';
	return (string_new);
}
