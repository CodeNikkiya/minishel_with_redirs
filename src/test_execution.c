/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npavelic <npavelic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 09:44:26 by npavelic          #+#    #+#             */
/*   Updated: 2023/12/02 18:56:28 by npavelic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"


char	*strjoin_three(char *first, char *second, char *third)
{
	int		len;
	char	*joint_str;

	if (first == NULL || second == NULL || third == NULL)
		return (NULL);
	len = ft_strlen(first);
	len += ft_strlen(second);
	len += ft_strlen(third);
	joint_str = (char *)ft_calloc((len + 1), 1);
	ft_strlcpy(joint_str, first, ft_strlen(first) + 1);
	ft_strlcat(joint_str, second, ft_strlen(first) + ft_strlen(second) + 1);
	ft_strlcat(joint_str, third, len + 1);
	return (joint_str);
}

void	destroy_str_arr(char **string_arr)
{
	int	i;

	i = 0;
	while (string_arr[i] != NULL)
	{
		free(string_arr[i]);
		i++;
	}
	free(string_arr);
}

char	*check_command(char *cmd, char **envp)
{
	int		envp_index;
	int		path_index;
	char	*cmd_path;
	char	**path_list;

	envp_index = 0;
	while (ft_strncmp("PATH=", envp[envp_index], 5) != 0
		&& envp[envp_index] != NULL)
		envp_index++;
	//include handling for deleted path
	path_list = ft_split(envp[envp_index] + 5, ':');
	path_index = 0;
	while (path_list[path_index] != NULL)
	{
		cmd_path = strjoin_three(path_list[path_index], "/", cmd);
		if (access(cmd_path, X_OK) == 0)
		{
			destroy_str_arr(path_list);
			return (cmd_path);
		}
		free(cmd_path);
		path_index++;
	}
	destroy_str_arr(path_list);
	return (NULL);
}

void addStringToCharArray(char*** array, char* str)
{
    // Count the number of strings in the current array
    int count = 0;
    char** currentArray = *array;
	printf ("\nIn addStringToCharArray 1: \n");
	print_string_array(currentArray);
	printf ("\nIn addStringToCharArray 1: \n");
    while (currentArray[count] != NULL) {
        count++;
    }

    // Allocate memory for a new array with one additional element
    char** newArray = (char**)malloc((count + 2) * sizeof(char*));
    if (newArray == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }

    // Copy the new string to the first position
    newArray[0] = str;
    // Copy the existing strings to the new array starting from index 1
    for (int i = 0; i < count; i++) {
        newArray[i + 1] = currentArray[i];
    }

    // Set the last element to NULL to indicate the end of the array
    newArray[count + 1] = NULL;

    // Update the original array pointer
    *array = newArray;

	printf ("\nIn addStringToCharArray 2: \n");
	print_string_array(newArray);
}

void test_execution (char *cmd, char**args, char** envp)
{
	char *cmd_path;
	cmd_path = check_command(cmd, envp);
	addStringToCharArray(&args, cmd_path);
	// printf ("\nargs_in_execution:\n");
	print_string_array(args);
	// printf ("\n");
	// printf("\n EXECUTION OUTPUT:\n");
	execve(cmd_path, args, envp);
}