/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_split.c										 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: npavelic <npavelic@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2022/12/17 10:04:53 by npavelic		  #+#	#+#			 */
/*   Updated: 2022/12/25 16:10:14 by npavelic		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

static int	word_counter(char c, char const *s)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		if ((s[i] != c) && ((s[i + 1] == c) || (s[i + 1] == '\0')))
			count++;
		i++;
	}
	return (count);
}

static void	gib_wort(char **wort, int *len_wort, char c)
{
	int	i;

	i = 0;
	*wort += *len_wort;
	*len_wort = 0;
	while (**wort && **wort == c)
		(*wort)++;
	while ((*wort)[i])
	{
		if ((*wort)[i] == c)
			return ;
		(*len_wort)++;
		i++;
	}
}

static char	**destroy_all(char **reza, int i)
{
	while (i >= 0)
	{
		free(reza[i]);
		i--;
	}
	free (reza);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**reza;
	char	*wort;
	int		i;
	int		len_wort;

	i = 0;
	if (s == NULL)
		return (NULL);
	reza = (char **)malloc(sizeof(char *) * (1 + word_counter(c, s)));
	if (!reza)
		return (NULL);
	wort = (char *) s;
	len_wort = 0;
	while (i < word_counter(c, s))
	{
		gib_wort(&wort, &len_wort, c);
		reza[i] = (char *)malloc(sizeof(char) * (len_wort + 1));
		if (!reza[i])
			return (destroy_all(reza, i));
		ft_strlcpy(reza[i], wort, (len_wort + 1));
		i++;
	}
	reza[i] = NULL;
	return (reza);
}
