#include "../inc/minishell.h"

// #include <stdlib.h>
// #include <stdio.h>
//  #include <string.h>

// // export should sort the variables if the argument contains a $ sign at the beginning
// typedef struct s_env
// {
//     char            **env_var;
//     char            **ev_name;
//     char            **ev_value;

//     int                last_result;
// }            t_env;


// int ft_strlen(const char *str) 
// {
//     int len = 0;
//     while (str[len] != 0) 
//         len++;
//     return len;
// }

int find_char(char *str, char c);


static void print_sorted_env(int *int_arr, t_env *env, int size)
{
	int i;
	int env_index;
	int has_equal_sign;

	i = 0;
	while (i < size)
	{
		env_index = int_arr[i];
		printf("env_index: %i\n", env_index);
		printf("env_var: %s\n", env->env_var[env_index]);
		printf("ev_name: %s\n", env->ev_name[env_index]);
		printf("ev_value: %s\n", env->ev_value[env_index]);
		has_equal_sign = find_char(env->env_var[env_index], '=');
		if (has_equal_sign == 0)
			printf("declare -x %s\n", env->ev_name[env_index]);
		else
			printf("declare -x %s=\"%s\"\n", env->ev_name[env_index], env->ev_value[env_index]);
		i++;
	}
}




// int find_equal_sign(char *arg) // copied from 1/new_files/export_variables.c
// {
// 	int i;

// 	i = 0;
// 	while (arg[i] != '\0')
// 	{
// 		if (arg[i] == '=')
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }
void sort_env_ascii(char **env, int size, t_env *env_struct)
{

	int i = 0;
	int *i_aray;
	i_aray = (int *)malloc(sizeof(int) * size);
	while (i < size)
	{
		i_aray[i] = i;
		i++;
	} 
	int j = 0;
	int temp;
	while (j < size - 1)
	{
		i = 0;
		while (i < size - 1)
		{
			if (strncmp(env[i], env[i + 1], ft_strlen(env[i])) > 0)
			{
				temp = i_aray[i];
				i_aray[i] = i_aray[i + 1];
				i_aray[i + 1] = temp;
			}
			i++;
		}
		j++;
	}
	print_sorted_env(i_aray, env_struct, size);
}


//////////////////////////////////JUST FOR TESTING
// static void    splitting_envs (t_env *e_vars, int i, int j, int k)
// {

//     while (e_vars->env_var[++i])
//     {
//         j = 0;
//         while (e_vars->env_var[i][j] != '=')
//             j++;
//         e_vars->ev_name[i] = malloc(sizeof(char) * j);
//         k = ft_strlen(e_vars->env_var[i]) - j + 1;
//         e_vars->ev_value[i] = malloc(sizeof(char) * (k));
//         k = 0;
//         while (k < j)
//         {
//             e_vars->ev_name[i][k] = e_vars->env_var[i][k];
//             k++;
//         }
//         e_vars->ev_name[i][k++] = '\0';
//         while (e_vars->env_var[i][k])
//         {
//             e_vars->ev_value[i][k - j - 1] = e_vars->env_var[i][k];
//             k++;
//         }
//     }
//     e_vars->ev_name[i] = NULL;
//     e_vars->ev_value[i] = NULL;
// }

// void    make_t_env(t_env *e_vars, char** env)
// {
//     int    i;
//     int    j;

//     i = -1;
//     while (env[++i])
//     {
//         j = 0;
//         e_vars->env_var[i] = malloc((ft_strlen(env[i]) + 1) * sizeof(char));
//         while (env[i][j])
//         {    
//             e_vars->env_var[i][j] = env[i][j];
//             j++;
//         }
//         e_vars->env_var[i][j] = '\0';
//     }
//     e_vars->env_var[i] = NULL;
//     splitting_envs (e_vars, -1, 0, 0);
// }
//////////////////////////// I think it's working, but need more testing
// int	main(int argc, char **argv, char **env)
// {
//     (void)(argc);
// 	(void)(argv);
// 	int has_equal_sign;
//     t_env *env_struct;
// 	has_equal_sign = 0;
//     env_struct = (t_env *)malloc(sizeof(t_env));
//     int i = 0;
//     while (env[i] != 0)
//     {
//         i++;
//     }
//     env_struct->env_var = (char **)malloc(sizeof(char *) * (i + 1));
//     env_struct->ev_name = (char **)malloc(sizeof(char *) * (i + 1));
//     env_struct->ev_value = (char **)malloc(sizeof(char *) * (i + 1));
// 	// has_equal_sign = find_equal_sign(argv[1]);
//     make_t_env(env_struct, env);
//     print_export(env_struct, has_equal_sign);

//   return 0;
// }