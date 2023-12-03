/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npavelic <npavelic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 11:52:24 by npavelic          #+#    #+#             */
/*   Updated: 2022/12/26 17:14:02 by npavelic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_bas_l(int n)
{
	int	bas_l;

	bas_l = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n /= 10;
		bas_l += 1;
	}
	return (bas_l);
}

static char	*build_string(int n, int negpo, int bas_l)
{
	char	*reza;

	reza = (char *)malloc (sizeof(char) * (bas_l--));
	if (!reza)
		return (NULL);
	if (negpo == -1)
		reza[0] = '-';
	reza[bas_l--] = '\0';
	while (bas_l >= 0)
	{
		reza[bas_l--] = n % 10 + 48;
		n /= 10;
		if ((bas_l == 0) && (negpo == -1))
			break ;
	}
	return (reza);
}

char	*ft_itoa(int n)
{
	int	negpo;
	int	bas_l;

	negpo = 0;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n < 0)
	{
		negpo = -1;
		n *= negpo;
	}
	bas_l = get_bas_l(n) + 1 - negpo;
	return (build_string(n, negpo, bas_l));
}
