/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comm_struc_make.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npavelic <npavelic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:03:02 by npavelic          #+#    #+#             */
/*   Updated: 2023/12/04 18:55:24 by npavelic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//copies the 41111 command from the numeric map into the command in the struct
//including 

char *temporary_command_copy_function(int *numeric_map, char *input, int *i)
{
	int		k;
	int		size;
	char	*command;

	// printf("\ntest _1, i is %i\n", *i);
	k = *i; // orig i = -1
	
	size = 0;
	while ((numeric_map[++k] != END) && (numeric_map[k] != PIPE) && (k != *i))
	{
		if (numeric_map[k] == COM_START)
		{
			print_num_array(numeric_map,   ft_strlen(input),0);
			*i = k;
			size = 1;
			while (numeric_map[++k] == COM_BODY)
				size++;
			if ((numeric_map[k] == END) || (numeric_map[k] == PIPE))
				break ;
		}
	}
	// printf("\ntest _2, i is %i\n", *i);

	// maybe no_command handling in case size is 0 at this point
	k = 0;
	if (size == 0)
		return (NULL);
	command = malloc(sizeof(char) * (size +1));
	command[k] = input[*i];
	while(numeric_map[++*i] == COM_BODY)
		command[++k] = input[*i];
	command[++k] = '\0';
	while ((numeric_map[*i] != END) && (numeric_map[*i] != PIPE))
		++*i;
	// printf("\ntest _3, i is %i and the command is %s\n", *i, command);
	return (command);
}




char	*remove_quotes (char *word)
{
	char				*new_word;
	unsigned long		i;

	new_word = malloc (sizeof(char) * (ft_strlen(word) - 1));
	i = 1;
	while (i < (ft_strlen(word) - 1))
	{
		new_word[i - 1] = word[i];
		i++;
	}
	new_word[i - 1] = '\0';
	free (word);
	return (new_word);
}

int	*mark_quoted_words(char *word, int *numeric_word, int i)
{
	char	q;
	bool	open_quotes;

	open_quotes = false;
	while (numeric_word[++i] != END)
	{
		if (((word[i] == '\'') || (word[i] == '\"')) && (!open_quotes))
		{
			q = word[i];
			open_quotes = true;
			numeric_word[i] = W_BEGINS;
			i++;
			while ((word[i] != q) && (word[i]))
			{
				numeric_word[i] = W_BODY;
				i++;
			}
			numeric_word[i] = W_BODY;
			open_quotes = false;
		}
	}
	return (numeric_word);
}

// here we can finally tell the quoted parts apart from the rest of the word
int	*mark_subwords(char *word, int *numeric_word)
{
	int	i;

	i = -1;
	numeric_word = mark_quoted_words(word, numeric_word, i);
	while (numeric_word[++i] != END)
	{
		if (numeric_word[i] == PLACEHOLDER)
		{
			numeric_word[i] = W_BEGINS;
			while (numeric_word[++i] == PLACEHOLDER)
				numeric_word[i] = W_BODY;
		}
		if (numeric_word[i] == END)
			break;
	}
	return (numeric_word);
}

char	*restructure_word(char *word, int *numeric_word, t_env *env)
{
	int i;
	int word_count;
	char **subwords;
	
	i = -1;
	word_count = 0;
	while (numeric_word[++i] != END)
	{
		if (numeric_word[i] == W_BEGINS)
			word_count++;
	}
	i = -1;
	//subwords = malloc (sizeof(char *) * (word_count + 1));
	subwords = temporary_input_to_args (numeric_word, word, word_count, &i);
	if (subwords)
		print_string_array(subwords);
	subwords = interprete_subwords (subwords, 0, env);
	print_string_array(subwords);
	free(word);
	word = turn_str_array_into_one_str(subwords);
	return (word);
}

//now we handle a word's content. if it's between ' and ', it's just a matter of removing them

char	*handle_word(char *word, t_env *env)
{
	int	*numeric_word;

	numeric_word = malloc (sizeof(int) * (1 + ft_strlen(word)));
	fill_with_placeholders (numeric_word, ft_strlen(word));
	numeric_word = mark_subwords(word, numeric_word);
	print_num_array(numeric_word, ft_strlen(word), 0);
	word = restructure_word(word, numeric_word, env);
	free(numeric_word);
	return (word); //return NULL for now
	
}


int	num_of_comm_structs(int *numeric_map)
{
	int	i;
	int	count;

	i = 0;
	count = 1;
	while (numeric_map[i] != END)
	{
		if (numeric_map[i] == PIPE)
			count++;
		i++;
	}
	return (count);
}

///////// TESTING FUNC DELETE LATER!!! OR COMMENT OUT
 void test_print_struct(t_cmd **command_table, int structs_count)
 {
	int i = 0;
	while (i < structs_count)
	{
		printf("\nstruct %i\n", i);
		printf("\ncommand: %s\n", command_table[i]->command);
		printf("\narguments: \n");
		if (command_table[i]->arguments[0] == NULL)
			printf("%s", command_table[i]->arguments[0]);

		print_string_array(command_table[i]->arguments);
		i++;
	}
 }


///////// TESTING FUNC DELETE LATER!!! OR COMMENT OUT


void	test_func_print_comm_table(t_cmd **command_table)
{
	int	j = 0;
	while (j < command_table[0]->num_of_structs)
	{
		printf ("\n\ncom table nr : %i and the output map is \'%s\'\n output files:\n", j, (*command_table)[j].out_doc_types);
		print_string_array((*command_table + j)->output_docs);
		printf ("\n\ncom table nr : %i and the input map is \'%s\'\n input files:\n", j, (*command_table)[j].inp_doc_types);
		print_string_array((*command_table + j)->input_docs);
		j++;
	}
}


/// command >> file > file_2 | com_2  > file_3 argz
/// command >> file > file_2 | com_2  > file_3 >> FILE5 >4_file  argz | >more >FILESS command

t_cmd	**create_command_struct(int *numeric_map, char *input, t_env *envs)
{
	t_cmd	**command_table;
	int		i;
	int		j;
	int		structs_count;


	i = -1;
	j = 0;
	structs_count = num_of_comm_structs(numeric_map);
	// printf("\this many structs need to be made: %i\n", structs_count);
	command_table = malloc(sizeof(t_cmd*) * structs_count);

	print_num_array(numeric_map, ft_strlen(input),0);


	while (j < structs_count)
	{
		command_table[j] = malloc(sizeof(t_cmd));
		command_table[j]->command = temporary_command_copy_function(numeric_map, input, &i);
		// printf("\ntest _4, i is %i\n", i);
		if (command_table[j]->command)
			command_table[j]->command = handle_word(command_table[j]->command, envs);
		printf("in struct making %s\n", command_table[j]->command);
        command_table[j]->num_of_structs = structs_count;
        j++;
	}

	j = 0;
	i = -1;
	while (j < structs_count)
		command_table[j++]->arguments=temporary_token_function(numeric_map, input, envs, &i);

	redirs_into_struct(&command_table, input, envs, numeric_map);
	redirs_into_struct_2_input(&command_table, input, envs, numeric_map);
	test_func_print_comm_table(command_table);
	//exit (0); //testing delete later!!!
	// test_print_struct(command_table, structs_count); // testing function, delete later
	//command_table->command = temporary_command_copy_function(numeric_map, input, &i);
	//command_table->command = handle_word(command_table->command, envs);

	//printf("\n COMMAND is: %s\n", command_table->command);
	//test_execution (command_table->command, command_table->arguments, envs->env_var);
	//free(command_table->command);
	//free_str_arr(command_table->arguments);
	//free(command_table);
	//free(numeric_map);
	//free_env(envs);
	// exit (0);
	// printf("NOW WE WALGRIND\n");
	// VALGRIND_DO_LEAK_CHECK;
	return (command_table);
}
//  0x7f94ecc07f10
// 	printf("chop_and_reconstruct_word: %p\n", elements);
	//printf("\n ARGS are: \n");
	//if (command_table->arguments != NULL)
	//printf("%s \n",command_table->arguments[0]);
	//delete later, just for testing
	//printf("\n COMMAND is: %s\n", command_table->command);

//   command arg | com_2 arg_2 $PWD