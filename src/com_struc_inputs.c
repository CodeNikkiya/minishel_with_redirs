/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_struc_inputs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npavelic <npavelic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 12:36:17 by npavelic          #+#    #+#             */
/*   Updated: 2023/12/04 18:57:25 by npavelic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//void	redirs_into_struct_2_input(t_cmd	***command_table, char *input, t_env *envs, int* numeric_map)
//void	make_inputs_arrays(t_cmd ***cmnd_table, char *input, int* nu_map)
//void	test_fun_seg_(t_cmd *cmnd_table)
//t_cmd	*alloc_in_strings(int i, t_cmd *cmnd_table, int* nu_map)
//void	allocate_input_docs_arrays(t_cmd ***cmnd_table)
//t_cmd	*fill_struct_ins(int *i, char *input, t_cmd *cmnd_table, int* nu_map)
//void	map_n_count_ins(t_cmd	***command_table, int* numeric_map)
//void	alloc_in_types(int *sizes, t_cmd **command_table, int* numeric_map)
//void	fill_in_types(int *sizes, t_cmd **command_table, int* numeric_map, int count)





void	fill_in_types(int *sizes, t_cmd **command_table, int* numeric_map, int count)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (j < count)
	{
		(*command_table)[j].inp_doc_types = malloc ((1 + sizes[j]) * sizeof(char));
		k = 0;
		//printf ("\nmap: %i\n", numeric_map[i]);
		while ((numeric_map[i] != END) && (numeric_map[i] != PIPE))
		{
			//printf ("\n %i %i\n", numeric_map[i], k);
			if ((numeric_map[i] == RD_H_DOC) || (numeric_map[i] == RD_LEFT))
			{
				//printf ("\n We are adding this to dir map : %i\n", numeric_map[i]);
				if (numeric_map[i] == RD_H_DOC)
					(*command_table)[j].inp_doc_types[k] = 'H';
				if (numeric_map[i] == RD_LEFT)
					(*command_table)[j].inp_doc_types[k] = 'I';
				k++;
				//printf("\nTEST k: %i  j: %i\n", k, j);
			}
			i++;
		}
		if ((numeric_map[i] == END) || (numeric_map[i] == PIPE))
		{
			(*command_table)[j].inp_doc_types[k] = '\0';
			j++;
		}
		//printf("\nc--i-i-i-  %s\n", (*command_table)[j - 1].inp_doc_types);
		i++;
	}
}

void	alloc_in_types(int *sizes, t_cmd **command_table, int* numeric_map)
{
	int	i;
	int	j;
	int	k;
	int	count;

	i = 0;
	j = 0;
	k = 0;
	count = command_table[j]->num_of_structs;
	while (numeric_map[i] != END)
	{
		if ((numeric_map[i] == RD_H_DOC) || (numeric_map[i] == RD_LEFT))
			k++;
		i++;
		if ((numeric_map[i] == END) || (numeric_map[i] == PIPE))
		{
			sizes[j] = k;
			k = 0;
			j++;
		}
	}
	//printf ("SIZES ARE: \n");
	//print_num_array(sizes, count - 1, 0);
	//exit (0);
	fill_in_types(sizes, command_table, numeric_map, count);
	///printf("\nd--i-i-i-  %s\n", (*command_table)[0].inp_doc_types);
	///printf("\nd--i-i-i-  %s\n", (*command_table)[1].inp_doc_types);
	///printf("\nd--i-i-i-  %s\n", (*command_table)[2].inp_doc_types);
	free(sizes);
}


void	map_n_count_ins(t_cmd	***command_table, int* numeric_map)
{
	int *sizes;
	
	sizes = malloc((*command_table)[0]->num_of_structs * sizeof(int));
	alloc_in_types(sizes, *command_table, numeric_map);
	//printf("\ne--i-i-i-  %s\n", (**command_table)[0].inp_doc_types);
	//printf("\ne--i-i-i-  %s\n", (**command_table)[1].inp_doc_types);
	//printf("\ne--i-i-i-  %s\n", (**command_table)[2].inp_doc_types);



}
t_cmd	*fill_struct_ins(int *i, char *input, t_cmd *cmnd_table, int* nu_map)
{
	//write (1, "TTT", 4);
	int	k;
	int	l;

	k = 0;
	//printf ("\n I is %i \n ", *i) ;
	//printf("\n MAP %p %p\n ", nu_map, i);
	while ((nu_map[(*i)] != END) && (nu_map[(*i)] != PIPE))
	{
		//write(1, "in while", 9);
		if ((nu_map[*i] == HEREDOC) || (nu_map[*i] == INPUT_FILE))
		{
			l = 0;
			while ((nu_map[*i] == HEREDOC) || (nu_map[*i] == INPUT_FILE))
			{

				//printf("\nin input it is letter: %c\n", input[*i]);
				(*cmnd_table).input_docs[k][l++] = input[(*i)++];
			}
			(*cmnd_table).input_docs[k][l] = '\0';
			//printf ("AND THEY GIVE US: %s\n",(*cmnd_table).input_docs[k] );
			k++;
		}
		if ((nu_map[*i] != END) && (nu_map[*i] != PIPE))
			(*i)++;
	}
	(*cmnd_table).input_docs[k] = NULL;
	//printf("\n 0 is %s:\n" , cmnd_table->input_docs[0]);
	//printf("\n 1 is %s:\n" , cmnd_table->input_docs[1]);
	//printf("\nFull array is: \n");
	//print_string_array ((*cmnd_table).input_docs);
	(*i)++;
	return (cmnd_table);
}


void	allocate_input_docs_arrays(t_cmd ***cmnd_table)
{
	int	j;
	int siz;

	j = 0;
	while (j < (*cmnd_table)[0]->num_of_structs)
	{
		siz = 1 + ft_strlen((**cmnd_table)[j].inp_doc_types);
		(**cmnd_table)[j].input_docs = malloc(sizeof(char *) * (siz));
		j++;
	}


}


t_cmd	*alloc_in_strings(int i, t_cmd *cmnd_table, int* nu_map)
{
	int	k;
	int	l;

	k = 0;
	//write (1, "TEST_1", 6);
	while ((nu_map[i] != END) && (nu_map[i] != PIPE))
	{
		if ((nu_map[i] == HEREDOC) || (nu_map[i] == INPUT_FILE))
		{
			l = 0;
			while ((nu_map[i] == HEREDOC) || (nu_map[i] == INPUT_FILE))
			{
				i++;
				l++;
			}
			//printf("\nI is %i and L is %i\n", i , l);
			//write (1, "TEST_2", 6);
			(*cmnd_table).input_docs[k] = malloc(sizeof(char) * (1 + l));
			//write (1, "TEST_3", 6);
			k++;
		}
		if ((nu_map[i] != END) && (nu_map[i] != PIPE))
			i++;
	}
	return (cmnd_table);
}

//void	test_fun_seg_(t_cmd *cmnd_table)
//{
//	printf("UUUUUUU");
//	printf ("\n%s\n", (*cmnd_table).inp_doc_types);
//}


void	make_inputs_arrays(t_cmd ***cmnd_table, char *input, int* nu_map)
{
	int i;
	int j;

	i = 0;
	j = 0;
	//printf("\ng--i-i-i-  %s\n", (**cmnd_table)[0].inp_doc_types);
	//printf("\ng--i-i-i-  %s\n", (**cmnd_table)[1].inp_doc_types);
	//printf("\ng--i-i-i-  %s\n", (**cmnd_table)[2].inp_doc_types);
	allocate_input_docs_arrays(cmnd_table);
	//printf("\n--i-i-i-  %s\n", (**cmnd_table)[0].inp_doc_types);
	//printf("\n--i-i-i-  %s\n", (**cmnd_table)[1].inp_doc_types);
	//printf("\n--i-i-i-  %s\n", (**cmnd_table)[2].inp_doc_types);
	while (j < (*cmnd_table)[0]->num_of_structs)
	{

		//printf("\nAnd we got here %i!!!\n", j);
		*cmnd_table[j] = alloc_in_strings(i, (**cmnd_table)+j, nu_map);
		//test_fun_seg_((**cmnd_table)+j);
		//printf("\nAnd we got here %i _ after_aloc strings!!1!\n", j);
		*cmnd_table[j] = fill_struct_ins(&i, input, (**cmnd_table)+j, nu_map);
		j++;
	}


}


void    truncate_inputs(t_cmd ***c, t_env *e)
{
	int    j;
	int    k;

	j = 0;
	while (j < (**c)[0].num_of_structs)
	{
		k = 0;
		printf("string is %s\n", "test");
		printf("truncate input, map is %s\n", (**c)[j].inp_doc_types);
		printf("string is %s\n", (**c)[j].input_docs[k]);
		while ((**c)[j].input_docs[k])
		{
			printf("J is %i\n", j);
			if ((ft_strlen((**c)[j].input_docs[k]))
				&& ((**c)[j].inp_doc_types[k] == 'I'))
				(**c)[j].input_docs[k] = handle_word((**c)[j].input_docs[k], e);
			k++;
		}
		j++;
	}
}

// ls >tttt >rrrrr >>eee <erere <<2222

void	redirs_into_struct_2_input(t_cmd	***command_table, char *input, t_env *envs, int* numeric_map)
{
	(void)envs;
	//printf("\nWE Got HERE--- redirs\n");
	map_n_count_ins(command_table, numeric_map);
	//printf("\n--i-i-i-  %s\n", (**command_table)[0].inp_doc_types);
	//printf("\n--i-i-i-  %s\n", (**command_table)[1].inp_doc_types);
	//printf("\n--i-i-i-  %s\n", (**command_table)[2].inp_doc_types);
	//printf ("\n%s\n", (*command_table)[0]->inp_doc_types);
	//printf("\nAnd we got here after maop n count!!!\n");
	make_inputs_arrays(command_table, input, numeric_map);
	truncate_inputs (command_table, envs);
}