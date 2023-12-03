/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npavelic <npavelic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 14:11:01 by npavelic          #+#    #+#             */
/*   Updated: 2023/11/01 16:04:33 by npavelic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_test.h"
#include "libft/libft.h"

char	*text_to_input(char *text)
{
	char *input;
	int		i = -1;
	
	input = malloc ((ft_strlen(text) + 1) * sizeof(char));
	while (text[++i])
		input[i] = text[i];
	input[i] = '\0';
	return (input);
}

int	main (void)
{
	char text[] = "  |  command\'ar|g\' || $sgd?sf | \"arg <>\" <>    ";
	char	*input = text_to_input(text);


	printf ("\'%s\'", input); //for testing, remove after
	input = begin_parsing (input);

	free (input);
	return (0);
}


// int	ft_strncmp(const char *s1, const char *s2, size_t n)
// {
// 	size_t	i;
// 	i = 0;
// 	while ((i < n) && ((s1[i] != '\0') || (s2[i] != '\0')))
// 	{
// 		if (s1[i] != s2[i])
// 			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
// 		i++;
// 	}
// 	if (i == n)
// 	{
// 		return (0);
// 	}
// 	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
// }


// int	main (void)
// {
// 	char *c_aray[4];

// 	c_aray[0] = "ABCR";
// 	c_aray[1] = "ABCE";
// 	c_aray[2] = "ABCA";
// 	c_aray[3] = "ABCB";
	
// 	int i_aray[4] ={0, 1, 2, 3};

// 	int i = 0;
// 	printf("test_1\n");
// 	while (i < 4)
// 	{
// 		printf("%i %s\n",i_aray[i], c_aray[i_aray[i]]);
// 		i++;
// 	}
// 	i = 0;
// 	int j = 0;
// 	int temp = 0;

// 	while (i < 3)
// 	{
// 		j = 1 + i;
// 		while (j < 4)
// 		{
// 			if (ft_strncmp(c_aray[i_aray[i]], c_aray[i_aray[j]], 4) > 0)
// 			{
// 				temp = i_aray[i];
// 				i_aray[i] = i_aray[j];
// 				i_aray[j] = temp;
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// 	i = 0;
// 	while (i < 4)
// 	{
// 		printf("%s\n", c_aray[i_aray[i]]);
// 		i++;
// 	}
// 	return 0;
// }