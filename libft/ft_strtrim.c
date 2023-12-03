/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npavelic <npavelic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 12:41:24 by npavelic          #+#    #+#             */
/*   Updated: 2022/12/26 17:16:08 by npavelic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	excluder(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	char	*final_str;
	int		i;
	int		begin;
	int		end;

	begin = 0;
	end = ft_strlen(s1);
	if (!s1 || !set)
		return (NULL);
	while (begin < end && (excluder(s1[begin], set)
			|| excluder(s1[end - 1], set)))
	{
		if (excluder(s1[begin], set) == 1)
			begin++;
		if (excluder(s1[end - 1], set) == 1)
			end--;
	}
	final_str = malloc((end - begin + 1) * sizeof(char));
	if (!final_str)
		return (NULL);
	final_str[end - begin] = '\0';
	i = 0;
	while (begin < end)
		final_str[i++] = s1[begin++];
	return (final_str);
}
