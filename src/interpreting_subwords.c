/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreting_subwords.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npavelic <npavelic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 13:56:29 by npavelic          #+#    #+#             */
/*   Updated: 2023/12/02 18:55:13 by npavelic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

bool	cannot_be_in_var(char c)
{
	if ((ft_isdigit(c)) || (ft_isalpha(c)) || (c == '_'))
		return (false);
	return (true);
}

int	*map_non_vars (int *subw_numeric, int i)
{
	while (subw_numeric[++i] != END)
	{
		if (subw_numeric[i] == PLACEHOLDER)
		{
			subw_numeric[i] = W_BEGINS;
			while (subw_numeric[++i] == PLACEHOLDER)
				subw_numeric[i] = W_BODY;
		}
		if (subw_numeric[i] == END)
			break;
	}
	return (subw_numeric);
}

int	*map_vars (int *subw_numeric, char *word, int i)
{
	while (subw_numeric[++i] != END)
	{
		if ((word[i] == '$') && (word[i + 1] == '?'))
		{
			subw_numeric[i] = EX_VAL_1;
			subw_numeric[i + 1] = EX_VAL_2;
			i++;
		}
		else if ((word[i] == '$') && !(cannot_be_in_var(word[i + 1]))
			&& !(ft_isdigit(word[i + 1])))
		{
			subw_numeric[i] = VAR_START;
			subw_numeric[i + 1] = VAR_BODY;
			i++;
			while (!(cannot_be_in_var(word[++i])))
				subw_numeric[i] = VAR_BODY;
			i--;
		}
	}
	subw_numeric = map_non_vars(subw_numeric, -1);
	return (subw_numeric);
}

bool	has_no_vars(int *subw_numeric)
{
	int	i;

	i = -1;
	while (subw_numeric[++i] != END)
	{
		if ((subw_numeric[i] != W_BEGINS) && (subw_numeric[i] != W_BODY))
		{
			return (false);
		}
	}
	return (true);
}

char	*vars_handler(char *word, t_env *env)
{
	int	*subw_numeric;

	subw_numeric = malloc (sizeof(int) * (ft_strlen(word) + 1));
	subw_numeric = fill_with_placeholders(subw_numeric, ft_strlen(word));
	subw_numeric = map_vars (subw_numeric, word, -1);
	// printf("\n1 -%s: ", word);
	print_num_array(subw_numeric, ft_strlen(word), 0);
	if (has_no_vars(subw_numeric))
	{
		free (subw_numeric);
		return (word);
	}
	// printf("\n2 -%s: ", word);
	word = chop_and_reconstruct_word (word, subw_numeric, env);
	free (subw_numeric); // new added line
	return (word);
}


char	**interprete_subwords(char **subwords, int i, t_env *env)
{
	while (subwords[i])
	{
		if ((subwords[i][0] == '\'') 
			&& (subwords[i][ft_strlen(subwords[i]) - 1] == '\''))
			subwords[i] = remove_quotes (subwords[i]);
		else if ((subwords[i][0] == '\"') 
			&& (subwords[i][ft_strlen(subwords[i]) - 1] == '\"'))
		{
			subwords[i] = vars_handler(remove_quotes (subwords[i]), env);
		// 	printf("\n3 -%s: ", subwords[i]);
		}
		else
		{
			subwords[i] = vars_handler(subwords[i], env);
			// printf("\n3 -%s: ", subwords[i]);
		}
		i++;
	}
	return (subwords);
}
