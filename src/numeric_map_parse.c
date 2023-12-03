/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numeric_map_parse.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npavelic <npavelic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 15:40:34 by npavelic          #+#    #+#             */
/*   Updated: 2023/12/02 18:56:04 by npavelic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// We need to first fill the int array with placeholders
// because we can't compare contents of an empty position
// with anything
//

int	*fill_with_placeholders (int *numeric_map, int i)
{
	numeric_map[i] = END;
	while (--i > -1)
		numeric_map[i] = PLACEHOLDER;
	return (numeric_map);
}


// TEST FUNC - DELETE LATER

void print_num_array(int *numeric_map, int null_pos, int j)
{
	printf ("\n");
	if (numeric_map == NULL)
	{	
		printf ("%p", NULL);
		return;
	}
	while (null_pos >= j)
	{
		printf ("%i", numeric_map[j]);
		j++;
	}	
}

//static void print_string_array(char ** string_array)
//{
//	int i = -1;
//
//	while (string_array[++i])
//		printf("\n%s", string_array[i]);
//}


/////////////////////new verison with changed functions for quotes 22.11.2023

int    *numeric_mapping(char *input)
{
    int    *numeric_map;

    numeric_map = malloc (sizeof(int) * (1 + ft_strlen(input)));
    numeric_map = fill_with_placeholders (numeric_map, ft_strlen(input));
    numeric_map = quotes_check (input, numeric_map, 0);
    if (numeric_map == NULL)
        return (NULL);

    // printf("test print: %s\n", "numeric_mapping");
    // ADD Unclosed Quote handling !!
    if (numeric_map == NULL)
        return (numeric_map);
    numeric_map = map_words_pipes_redirs (input, numeric_map, -1);
    //print_num_array(numeric_map, ft_strlen(input), 0);
	//printf("\nlast position is: %lu!\n", ft_strlen(input));
    numeric_map = adjust_redirs(numeric_map);
    //print_num_array(numeric_map, ft_strlen(input), 0);
    //print_num_array(numeric_map, ft_strlen(input), 0);

	numeric_map = mark_redirs(numeric_map);
    //print_num_array(numeric_map, ft_strlen(input), 0); // TEST FUNC - DELETE LATER
    //printf ("\n");
    numeric_map = map_commands (numeric_map, -1);
	//printf ("%s", input);
    //print_num_array(numeric_map, ft_strlen(input), 0); // TEST FUNC - DELETE LATER
    //printf ("\n");
    //printf ("\n%i\n", symbols_are_invalid(numeric_map));
    if (symbols_are_invalid(numeric_map))
        return(numeric_map) ;//HANDLE THIS LATER
    return (numeric_map); 
}


int    *quotes_are_open (char *input, int *numeric_map)
{
    free (input);
    free (numeric_map);
    printf ("Open quotes aren't handled");
    return (NULL);
}

int    put_redir_or_pipe (char c)
{
    if (c == '<')
        return (RD_LEFT);
    if (c == '>')
        return (RD_RIGHT);
    if (c == '|')
        return (PIPE);
    return (PLACEHOLDER);
}
int    *quotes_check(char *input, int *numeric_map, int i)
{
    char    q;
    bool    open_quotes;

    open_quotes = false;
    while (input[i])
    {
        numeric_map[i] = put_redir_or_pipe (input[i]);
        if (((input[i] == '\'') || (input[i] == '\"')) && (!open_quotes))
        {
            q = input[i];
            open_quotes = true;
            numeric_map[i++] = W_BODY;
            while ((input[i] != q) && (input[i]))
                numeric_map[i++] = W_BODY;
            if (input [i] == q)
                numeric_map[i] = W_BODY;
            else
                break;
            open_quotes = false;
        }
        i++;
    }
    if (open_quotes) // add options for error handling unclosed quotes
        return (quotes_are_open (input, numeric_map));
    return (numeric_map);
}

// int	appropriate_character(char *input, int i)
// {
// 		if (is_whitespace(input[i]))
// 			return (WHITESPACE);
// 		else if (input[i] == '<')
// 			return (RD_LEFT);
// 		else if (input[i] == '>')
// 			return (RD_RIGHT);
// 		else if (input[i] == '|')
// 			return (PIPE);
// 		//else if (input[i] == '$')
// 		//	return (DOLLAR);
// 		//else if (input[i] == '?')
// 		//	return (QUESTION_M);
// 		else
// 			return (PLACEHOLDER);
// }

// After marking everything in quotes as words, we proceed to
// mark the special characters

int	*map_words_pipes_redirs(char *input, int *numeric_map, int i)
{
	while (input[++i])
	{
		if ((numeric_map[i] == PLACEHOLDER) && (is_whitespace(input[i])))
			numeric_map[i] = WHITESPACE;
	}
	i = -1;
	while (input[++i])
	{
		if ((numeric_map[i] == PLACEHOLDER) || (numeric_map[i] == W_BODY))
		{
			numeric_map[i] = W_BEGINS;
			i++;
			while ((numeric_map[i] == PLACEHOLDER) || (numeric_map[i] == W_BODY))
			{				
				numeric_map[i] = W_BODY;
				i++;
			}
		}
	}
	return (numeric_map);
}
