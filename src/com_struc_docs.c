/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_struc_docs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npavelic <npavelic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 12:36:17 by npavelic          #+#    #+#             */
/*   Updated: 2023/12/04 18:44:05 by npavelic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	fill_out_types(int *sizes, t_cmd **command_table, int* numeric_map, int count)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (j < count)
	{
		(*command_table)[j].out_doc_types = malloc ((1 + sizes[j]) * sizeof(char));
		k = 0;
		//printf ("\nmap: %i\n", numeric_map[i]);
		while ((numeric_map[i] != END) && (numeric_map[i] != PIPE))
		{
			//printf ("\n %i %i\n", numeric_map[i], k);
			if ((numeric_map[i] == RD_RG_AP) || (numeric_map[i] == RD_RIGHT))
			{
				//printf ("\n We are adding this to dir map : %i\n", numeric_map[i]);
				if (numeric_map[i] == RD_RG_AP)
					(*command_table)[j].out_doc_types[k] = 'A';
				if (numeric_map[i] == RD_RIGHT)
					(*command_table)[j].out_doc_types[k] = 'O';
				k++;
				//printf("\nTEST k: %i  j: %i\n", k, j);
			}
			i++;
		}
		if ((numeric_map[i] == END) || (numeric_map[i] == PIPE))
		{
			(*command_table)[j].out_doc_types[k] = '\0';
			j++;
		}
		printf("\nc--i-i-i-  %s\n", (*command_table)[j - 1].out_doc_types);
		i++;
	}
}

void	alloc_out_types(int *sizes, t_cmd **command_table, int* numeric_map)
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
		if ((numeric_map[i] == RD_RG_AP) || (numeric_map[i] == RD_RIGHT))
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
	fill_out_types(sizes, command_table, numeric_map, count);
	///printf("\nd--i-i-i-  %s\n", (*command_table)[0].out_doc_types);
	///printf("\nd--i-i-i-  %s\n", (*command_table)[1].out_doc_types);
	///printf("\nd--i-i-i-  %s\n", (*command_table)[2].out_doc_types);
	free(sizes);

}


void	map_n_count_outs(t_cmd	***command_table, int* numeric_map)
{
	int *sizes;
	
	sizes = malloc((*command_table)[0]->num_of_structs * sizeof(int));
	alloc_out_types(sizes, *command_table, numeric_map);
	//printf("\ne--i-i-i-  %s\n", (**command_table)[0].out_doc_types);
	//printf("\ne--i-i-i-  %s\n", (**command_table)[1].out_doc_types);
	//printf("\ne--i-i-i-  %s\n", (**command_table)[2].out_doc_types);



}

t_cmd	*fill_struct_outs(int *i, char *input, t_cmd *cmnd_table, int* nu_map)
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
		if ((nu_map[*i] == OUTPT_APPEND) || (nu_map[*i] == OUTPT_OVER))
		{
			l = 0;
			while ((nu_map[*i] == OUTPT_APPEND) || (nu_map[*i] == OUTPT_OVER))
			{

				//printf("\nin input it is letter: %c\n", input[*i]);
				(*cmnd_table).output_docs[k][l++] = input[(*i)++];
			}
			(*cmnd_table).output_docs[k][l] = '\0';
			//printf ("AND THEY GIVE US: %s\n",(*cmnd_table).output_docs[k] );
			k++;
		}
		if ((nu_map[*i] != END) && (nu_map[*i] != PIPE))
			(*i)++;
	}
	(*cmnd_table).output_docs[k] = NULL;
	//printf("\n 0 is %s:\n" , cmnd_table->output_docs[0]);
	//printf("\n 1 is %s:\n" , cmnd_table->output_docs[1]);
	//printf("\nFull array is: \n");
	//print_string_array ((*cmnd_table).output_docs);
	(*i)++;
	return (cmnd_table);
}


void	allocate_output_docs_arrays(t_cmd ***cmnd_table)
{
	int	j;
	int siz;

	j = 0;
	while (j < (*cmnd_table)[0]->num_of_structs)
	{
		siz = 1 + ft_strlen((**cmnd_table)[j].out_doc_types);
		(**cmnd_table)[j].output_docs = malloc(sizeof(char *) * (siz));
		j++;
	}


}


t_cmd	*alloc_out_strings(int i, t_cmd *cmnd_table, int* nu_map)
{
	int	k;
	int	l;

	k = 0;
	//write (1, "TEST_1", 6);
	while ((nu_map[i] != END) && (nu_map[i] != PIPE))
	{
		if ((nu_map[i] == OUTPT_APPEND) || (nu_map[i] == OUTPT_OVER))
		{
			l = 0;
			while ((nu_map[i] == OUTPT_APPEND) || (nu_map[i] == OUTPT_OVER))
			{
				i++;
				l++;
			}
			//printf("\nI is %i and L is %i\n", i , l);
			//write (1, "TEST_2", 6);
			(*cmnd_table).output_docs[k] = malloc(sizeof(char) * (1 + l));
			//write (1, "TEST_3", 6);
			k++;
		}
		if ((nu_map[i] != END) && (nu_map[i] != PIPE))
			i++;
	}
	return (cmnd_table);
}

void	test_fun_seg_(t_cmd *cmnd_table)
{
	printf("UUUUUUU");
	printf ("\n%s\n", (*cmnd_table).out_doc_types);
}


void	make_outputs_arrays(t_cmd ***cmnd_table, char *input, int* nu_map)
{
	int i;
	int j;

	i = 0;
	j = 0;
	//printf("\ng--i-i-i-  %s\n", (**cmnd_table)[0].out_doc_types);
	//printf("\ng--i-i-i-  %s\n", (**cmnd_table)[1].out_doc_types);
	//printf("\ng--i-i-i-  %s\n", (**cmnd_table)[2].out_doc_types);
	allocate_output_docs_arrays(cmnd_table);

	//printf("\n--i-i-i-  %s\n", (**cmnd_table)[0].out_doc_types);
	//printf("\n--i-i-i-  %s\n", (**cmnd_table)[1].out_doc_types);
	//printf("\n--i-i-i-  %s\n", (**cmnd_table)[2].out_doc_types);
	while (j < (*cmnd_table)[0]->num_of_structs)
	{

		//printf("\nAnd we got here %i!!!\n", j);
		*cmnd_table[j] = alloc_out_strings(i, (**cmnd_table)+j, nu_map);
		//test_fun_seg_((**cmnd_table)+j);
		//printf("\nAnd we got here %i _ after_aloc strings!!1!\n", j);
		*cmnd_table[j] = fill_struct_outs(&i, input, (**cmnd_table)+j, nu_map);
		j++;
	}


}


void    truncate_outputs(t_cmd ***c, t_env *e)
{
	int    j;
	int    k;

	j = 0;
	while (j < (**c)[0].num_of_structs)
	{
		k = 0;
		printf("string is %s\n", "test");
		printf("string is %s\n", (**c)[j].output_docs[k]);
		while ((**c)[j].output_docs[k])
		{
			printf("J is %i\n", j);
			if (ft_strlen((**c)[j].output_docs[k]))
				(**c)[j].output_docs[k] = handle_word((**c)[j].output_docs[k], e);
			k++;
		}
		j++;
	}
}



void	redirs_into_struct(t_cmd	***command_table, char *input, t_env *envs, int* numeric_map)
{
	(void)envs;
	//printf("\nWE Got HERE--- redirs\n");
	map_n_count_outs(command_table, numeric_map);
	//printf("\n--i-i-i-  %s\n", (**command_table)[0].out_doc_types);
	//printf("\n--i-i-i-  %s\n", (**command_table)[1].out_doc_types);
	//printf("\n--i-i-i-  %s\n", (**command_table)[2].out_doc_types);
	//printf ("\n%s\n", (*command_table)[0]->out_doc_types);
	//printf("\nAnd we got here after maop n count!!!\n");

	make_outputs_arrays(command_table, input, numeric_map);
	truncate_outputs(command_table, envs);

}