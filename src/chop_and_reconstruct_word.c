/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chop_and_reconstruct_word.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npavelic <npavelic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 19:29:57 by npavelic          #+#    #+#             */
/*   Updated: 2023/12/02 18:57:01 by npavelic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"


//think about redoing the whole thing tomorrow. Now we're splitting the subword that cointains variables before expanding and reassembling

char	**split_subword (char *word, int *subw_num, char **elems)
{
	int		i;
	int		j;
	int		k;

	i = -1;
	k = 0;
	while (subw_num[++i] != END)
	{
		if ((subw_num[i] == VAR_START)
			|| (subw_num[i] == EX_VAL_1) || (subw_num[i] == W_BEGINS))
			{
				j = i - 1;
				while ((subw_num[++i] != VAR_START) && (subw_num[i] != EX_VAL_1) 
					&& (subw_num[i] != W_BEGINS) && (subw_num[i] != END))
					printf("\ni = %i\n", i);
				printf("\ni = %i\n", i);
				elems[k] = malloc(sizeof(char) * (i - j));
				elems[k][i - j -1] = '\0';
				while (j < --i)
				{
					elems[k][i - j -1 ] = word[i];
					printf("position %i: %c\n",i - j -1, word[i]);
				}
				i++;
			 	k++;
			}
	}
	// printf("end of split subword: %s\n", elems[k-1]);
	//elems[k] = NULL; //perhaps better to remove because it's given in chop_and_reconstruct_word
	return (elems);
}

char	*expand_exit_value(char *element, t_env *env)
{
	free (element);
	element = ft_itoa(env->lst_exit_value);
	return (element);
}

char	*remove_dollar(char *element)
{
	int		i;
	char	*result;

	i = 0;
	result = malloc(sizeof(char) * (ft_strlen(element)));
	while(element[++i])
		result[i - 1] = element[i];
	result[i - 1] = '\0';
	free (element);
	return (result);
}

char	*expand_variable(char *element, t_env *env)
{
	int		i;
	size_t	n;

	i = -1;
	// printf ("\n 1 element to expand:%s\n", element);
	element = remove_dollar(element);
	// printf ("\n  element after removing $:%s\n", element);
	// printf ("\n  first env :%s\n", env->ev_name[0]);
	while (env->ev_name[++i])
	{
		n = ft_strlen(element) + ft_strlen(env->ev_name[i]);
		if (!ft_strncmp(element, env->ev_name[i], n))
		{
			free (element);
			element = ft_strdup(env->ev_value[i]);
			return (element);
		}
	}
	// printf ("\n  element before freeing: %s\n", element);
	free(element);
	element = malloc(sizeof(char));
	element[0] = '\0';
	// printf ("\n  element after emptying string: %s\n", element);
	return (element);
}

char	**expand_elements (int *subw_numeric, char **elements, t_env *env)
{
	int	i;
	int	k;

	i = -1;
	k = 0;
	while (subw_numeric[++i] != END)
	{
		if (subw_numeric[i] == VAR_START)
		{
			elements[k] = expand_variable(elements[k], env);
			k++;
		}
		else if (subw_numeric[i] == EX_VAL_1)
		{
			elements[k] = expand_exit_value(elements[k], env);
			k++;
		}
		else if (subw_numeric[i] == W_BEGINS)
			k++;
	}
	return (elements);
}

void	free_str_arr(char	**str_ar)
{
	int	i;

	i = 0;
	// printf("The string array to free is: \n");
	print_string_array(str_ar);
	while (str_ar[i])
		free (str_ar[i++]);
	free (str_ar);
}


char	*turn_str_array_into_one_str(char **array)
{
	int		i;
	int		j;
	int		k;
	char	*result;

	i = -1;
	k = 0;
	while (array[++i])
		k += ft_strlen(array[i]);
	result = malloc(sizeof(char) * (k + 1));
	i = -1;
	j = -1;
	while(array[++i])
	{
		k = -1;
		while (array[i][++k])
		{
			j++;
			result[j] = array[i][k];
		}
	}
	j++;
	result[j] = '\0';
	free_str_arr (array);
	return (result);	
}

char	*chop_and_reconstruct_word(char *word, int *subw_numeric, t_env *env)
{
	int		num_of_elements;
	char	**elements;
	int		i;

	i = -1;
	num_of_elements = 0;
	// printf("\n4 -%s: ", word);
	// printf ("Subword Numeric :");
	print_num_array(subw_numeric, ft_strlen(word), 0);
	while (subw_numeric[++i] != END)
	{
		if ((subw_numeric[i] == VAR_START)
			|| (subw_numeric[i] == EX_VAL_1) || (subw_numeric[i] == W_BEGINS))
			num_of_elements++;
	}
	elements = malloc(sizeof(char*) * (1 + num_of_elements));
	//free(elements);
	
	elements[num_of_elements] = NULL;
	elements = split_subword (word, subw_numeric, elements);
	// printf("\n5 -%s: ", elements[0]);
	elements = expand_elements (subw_numeric, elements, env);
	free (word);
	word = turn_str_array_into_one_str(elements);
	word = vars_handler(word, env);
	return (word);
}
