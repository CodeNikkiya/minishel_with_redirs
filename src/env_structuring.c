/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_structuring.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npavelic <npavelic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 15:55:36 by npavelic          #+#    #+#             */
/*   Updated: 2023/12/02 18:57:05 by npavelic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// copying env variables to our struct for the new struct


// int	ft_env(t_env *env)
// {
// 	int i;

// 	i = 0;
// 	while(env->env_var[i])
// 	{	
// 		printf("%s\n", env->env_var[i]);
// 		i++;
// 	}
// 	printf("\n____________%s____________________________________ num of vars is %i\n", env->env_var[i], i);
// 	i = 0;
// 	while(env->ev_name[i])
// 	{	
// 		printf("%s\n", env->ev_name[i]);
// 		i++;
// 	}
// 	printf("\n____________%s____________________________________ num of vars is %i\n", env->ev_name[i],i);
// 	i = 0;
// 	while(env->ev_value[i])
// 	{	
// 		printf("%s\n", env->ev_value[i]);
// 		i++;
// 	}
// 	printf("\n____________%s____________________________________ num of vars is %i\n", env->ev_value[i],i);
// 	return (0);
// }

/////////////////////////////////////////////////////////////////////// testing functions below
//int ft_strlen(const char *str) 
//{
//    int len = 0;
//    while (str[len] != 0) 
//        len++;
//    return len;
//}

static void    splitting_envs (t_env *e_vars, int i, int j, int k)
{

    while (e_vars->env_var[++i])
    {
		j = 0;
		while (e_vars->env_var[i][j] != '=')
		    j++;
		e_vars->ev_name[i] = malloc(sizeof(char) * (j + 1));
		k = ft_strlen(e_vars->env_var[i]) - j + 1;
		e_vars->ev_value[i] = malloc(sizeof(char) * (k));
		k = 0;
		while (k < j)
		{
		    e_vars->ev_name[i][k] = e_vars->env_var[i][k];
		    k++;
		}
		e_vars->ev_name[i][k++] = '\0';
		while (e_vars->env_var[i][k])
		{
		    e_vars->ev_value[i][k - j - 1] = e_vars->env_var[i][k];
		    k++;
		}
		e_vars->ev_value[i][k] = '\0';
    }
    e_vars->ev_name[i] = NULL;
    e_vars->ev_value[i] = NULL;
}

static void    make_t_env(t_env *e_vars, char** env)
{
    int    i;
    int    j;

    i = -1;
    while (env[++i])
    {
        j = 0;
        e_vars->env_var[i] = malloc((ft_strlen(env[i]) + 1) * sizeof(char));
        while (env[i][j])
        {    
            e_vars->env_var[i][j] = env[i][j];
            j++;
        }
        e_vars->env_var[i][j] = '\0';
    }
    e_vars->env_var[i] = NULL;
    splitting_envs (e_vars, -1, 0, 0);
}


t_env *env_alloc_n_make(char **env_sys)
{
	t_env *env_struct;

    env_struct = (t_env *)malloc(sizeof(t_env));
    int i = 0;
    while (env_sys[i] != NULL)
        i++;
    env_struct->env_var = (char **)malloc(sizeof(char *) * (i + 1));
    env_struct->ev_name = (char **)malloc(sizeof(char *) * (i + 1));
    env_struct->ev_value = (char **)malloc(sizeof(char *) * (i + 1));
	env_struct->lst_exit_value = 0;
    make_t_env(env_struct, env_sys);
	return (env_struct);
}