/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npavelic <npavelic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 17:24:46 by npavelic          #+#    #+#             */
/*   Updated: 2022/12/26 17:13:12 by npavelic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t num, size_t size)
{
	void	*finpo;

	if (num == 0 || size == 0)
	{
		num = 1;
		size = 1;
	}
	finpo = malloc (num * size);
	if (finpo)
		ft_bzero (finpo, num * size);
	return (finpo);
}
