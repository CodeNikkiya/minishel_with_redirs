/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp_arg_array.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npavelic <npavelic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 12:50:12 by npavelic          #+#    #+#             */
/*   Updated: 2023/12/03 16:40:32 by npavelic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"


// goes through the args in the input map and turns them into 
// a string array, possibly needs to be changed to only do this for the args of the relevant command

char **allocate_args(int *numeric_map, int word_count, int *i)
{
	int		k;
	int		j;
	int		size;
	char	**args;

	k = *i + 1;
	j = 0;
	// printf ("\nword count in allocate args  is %i and the position is %i\n", word_count, k);
	args = malloc (sizeof(char *) * (word_count + 1));
	args[word_count] = NULL;
	while ((numeric_map[k] != END) && (numeric_map[k] != PIPE))
	{
		size = 1;
		if (numeric_map[k] == W_BEGINS)
		{
			size++;
			while (numeric_map[++k] == W_BODY)
				size++;
			args[j] = malloc (sizeof(char) * size);

			// printf ("\nin allocate args  word %i is size %i \n", j, size);
			j++;
		}
		if ((numeric_map[k] != W_BEGINS) && (numeric_map[k] != END) && (numeric_map[k] != PIPE))
			k++;
	}
	return (args);
}

char **temporary_input_to_args (int *numeric_map, char *input, int word_count, int *i)
{
	char	**args;
	int		j;
	int		k;

	j = 0;
	
	args = allocate_args(numeric_map, word_count, i);
	// printf ("\nhere it's still good (temporary_input_to_args) i is %i\n", *i);
	(*i)++;
	while ((numeric_map[*i] != END) && (numeric_map[*i] != PIPE))
	{
		// printf("test100000 i:%i\n", *i);
		if (numeric_map[*i] == W_BEGINS)
		{
			// printf("test_first_if \n");
			k = 1;
			// printf("test_222 \n");
			args[j][0] = input[*i];
			// printf("test_333 \n");
			while (numeric_map[++*i] == W_BODY)
				{
					// printf("test_iside_while_loop nummeric_map:%i\n", numeric_map[*i]);
					args[j][k++] = input[*i];
				}
			args[j][k] = '\0';
			j++;
		}
		if ((numeric_map[*i] != W_BEGINS) && (numeric_map[*i] != END) && (numeric_map[*i] != PIPE))
			{
				// printf("test_second_if \n");
				(*i)++;
			}
	}
	return (args);

}
//// TESTING FUNC
void print_string_array(char ** string_array)
{
	int i = 0;
	while (string_array[i])
	{
		printf("\n%s", string_array[i]);
		i++;
	}
// 	printf("\n");
}

/////

char **temporary_token_function (int *numeric_map, char *input, t_env *envs, int *i)
{
	int		k;
	int		word_count;
	char	**args;
	
	k = *i;
	word_count = 0;
	// printf ("%i", k);
	// printf ("\n  first env :%s\n", envs->ev_name[0]);
	print_num_array(numeric_map,   ft_strlen(input),0);
	while ((numeric_map[++k] != END) && (numeric_map[k] != PIPE))
	{
		// printf ("\n %i, ", k);
		if (numeric_map[k] == W_BEGINS)
			word_count++;
	}
	//printf ("%i", word_count);
	//printf ("\nhere it's still good (temporary_token_function)\n");
	args = temporary_input_to_args (numeric_map, input, word_count, i);
	word_count = -1;
	while (args[++word_count])
	{
		args[word_count] = handle_word(args[word_count], envs);
	}

	//print_string_array (args);
	// free(args);
	return (args); //temp for test
}


//"comm"$?$USER'$USER' argzie 666 uk | c'o'm'a'"nnn"$sock$$$ $PWD $$$ $?$USER | 9 000'$be good'$be bad