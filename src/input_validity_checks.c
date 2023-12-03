/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validity_checks.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npavelic <npavelic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:42:23 by npavelic          #+#    #+#             */
/*   Updated: 2023/12/02 18:55:10 by npavelic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// checks if symbol combinations that
// arent parts of words are in an 
// unusable order
// returns appropriate error status
// prints the error message

int	syn_error_print(char *signs, char c)
{
	if (c == 'p')
		printf ("parse error near `%s\'", signs);
	if (c == 's')
		printf("syntax error near unexpected token `%s\'", signs);
	return (0);
}

int	symbols_are_invalid(int *numeric_map)
{
	int	i;

	i = -1;
	while (numeric_map[++i] != END)
	{
		if ((numeric_map[i] == PIPE) && (numeric_map[i + 1] == PIPE))
			return (2 + syn_error_print("||", 'p'));
		if (numeric_map[0] == PIPE)
			return (258 + syn_error_print("|", 's'));
	}
	return (0);
}

//error handling should be discussed first