/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_begins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npavelic <npavelic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 13:10:09 by npavelic          #+#    #+#             */
/*   Updated: 2023/12/02 18:56:06 by npavelic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// We begin parsing by trimming whitespace from the start and
// from the end using ft_trimmer.
//
// 
//
//

int	is_whitespace(char c)
{
	if ((c == ' ') || (c == '\n') || (c == '\t'))
		return (1);
	return (0);
}

char	*ft_trimmer(char *input)
{
	int		i;
	int		j;
	int		k;
	char	*result;

	i = 0;
	k = 0;
	while (is_whitespace(input[i]))
		i++;
	j = ft_strlen(input) - 1;
	while (is_whitespace(input[j]) && (j > -1))
		j--;
	result = malloc(sizeof(char) * (2 + j - i));
	while (i <= j)
		result[k++] = input[i++];
	result [k] = '\0';
	free (input);
	return (result);
}

t_cmd **begin_parsing(char *input, t_env * env_struct)
{
	int	*numeric_map;
	(void) env_struct;

	if ((input == NULL) || (input[0] == '\0'))
		return (NULL);
	if ((is_whitespace(input[0])) || (is_whitespace(input[ft_strlen(input)])))
			input = ft_trimmer(input);

	// printf("test print: %s\n", "begin_parsing");
	// printf ("\n\'%s\'", input); //remove after testing
	numeric_map = numeric_mapping(input);
	// printf ("\n"); //remove after testing
	return(create_command_struct(numeric_map, input, env_struct));
}
