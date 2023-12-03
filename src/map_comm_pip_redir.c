/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_comm_pip_redir.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npavelic <npavelic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 20:48:13 by npavelic          #+#    #+#             */
/*   Updated: 2023/12/02 18:55:20 by npavelic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	*adjust_redirs(int *numeric_map)
{
	int	i;

	i = 1;
	while (numeric_map[i] != END)
	{
		if ((numeric_map[i] == PIPE) && (numeric_map[i - 1] == RD_RIGHT))
			numeric_map[i] = WHITESPACE;
		if ((numeric_map[i] == RD_RIGHT) && (numeric_map[i - 1] == RD_RIGHT))
		{
			numeric_map[i] = WHITESPACE;
			numeric_map[i - 1] = RD_RG_AP;
		}
		if ((numeric_map[i] == RD_LEFT) && (numeric_map[i - 1] == RD_LEFT))
		{
			numeric_map[i] = WHITESPACE;
			numeric_map[i - 1] = RD_H_DOC;
		}
		i++;
	}
	return (numeric_map);
}



int	filename_marker(int	k)
{
	if (k == RD_RIGHT)
		return (OUTPT_OVER);
	if (k == RD_LEFT)
		return (INPUT_FILE);
	if (k == RD_RG_AP)
		return (OUTPT_APPEND);
	if (k == RD_H_DOC)
		return (HEREDOC);
	return (k);
}


int	*next_word_is_redir(int *i, int *numeric_map)
{
	int	k;

	k = *i;
	(*i)++;
	while (numeric_map[*i] == WHITESPACE)
		(*i)++;
	if (numeric_map[*i] == W_BEGINS)
	{
		//printf("\ncurrently k at position %i is %i \n", k, numeric_map[k]);
		numeric_map[*i] = filename_marker(numeric_map[k]);
		while (numeric_map[++*i] == W_BODY)
			numeric_map[*i] = filename_marker(numeric_map[k]);
	}
	return (numeric_map);
	 //((numeric_map[i] != RD_RIGHT) && (numeric_map[i] != ) && (numeric_map[i] != END) && (numeric_map[i] != PIPE) && (numeric_map[i] != RD_RG_AP) && (numeric_map[i] != PIPE))
}

int	*mark_redirs(int *numeric_map)
{
	int	i;

	i = 0;
	//printf ("\n We started mark_redirs with i = %i \n", i);
	while (numeric_map[i] != END)
	{
		//printf ("\n %i", i);
		if ((numeric_map[i] == RD_RIGHT) || (numeric_map[i] == RD_LEFT)
			|| (numeric_map[i] == RD_H_DOC) || (numeric_map[i] == RD_RG_AP))
		{
			numeric_map = next_word_is_redir(&i, numeric_map);
			i--;
		}
		i++;
	}
	//printf ("\n End position should be %i, and there we have %i \n", i, numeric_map[i]);
    //print_num_array(numeric_map, i, 0);
	return (numeric_map);
}
//command > file arg >> file_2


int*	map_commands (int *numeric_map, int i)
{
	int	command_not_done;

	command_not_done = 1;
	while (numeric_map[++i] != END)
	{
		if (numeric_map[i] == PIPE)
			command_not_done = 1;
		if ((numeric_map[i] == W_BEGINS) && (command_not_done))
		{
			command_not_done = 0;
			numeric_map[i] = COM_START;
			i++;
			while (numeric_map[i] == W_BODY)
				numeric_map[i++] = COM_BODY;
			if (numeric_map[i] == END)
				break;
		}
	}
	return (numeric_map);
}