
#include "../inc/minishell.h"

// void	ft_copy_env(t_env **env_var, char *env)
// {
// 	int	size;
// 	int	i;

// 	size = 0;
// 	while (env_var[size])
// 		size++;
// 	env->env_var = (char **)malloc(sizeof(char *) * (size + 1));
// 	i = 0;
// 	while (env_var[i])
// 	{
// 		env->env_var[i] = ft_strdup(env_var[i]);
// 		i++;
// 	}
// 	env->env_var[i] = 0;
// }

// freeing functions below 
void free_double_array(char **array)
{
    int i = 0;
    while (array[i] != NULL)
    {
        free(array[i]);
        i++;
    }
    free(array);
}

void free_env(t_env *env)
{
    free_double_array(env->env_var);
    free_double_array(env->ev_name);
    free_double_array(env->ev_value);
	// if (env->lst_exit_value)
    // 	free(env->lst_exit_value);
    free(env); // not sure about this line
}

char    *join_input (char    *first_part, char    *second_part)
{
    char    *returned_input;

    returned_input = ft_strjoin(first_part, second_part);
    free (second_part);
    free (first_part);
    return (returned_input);
}

char *handle_ending_pipe(char *input)
{
    char    *extra_input;

    while (input[strlen(input) - 1] == '|')
    {
        manage_signals();
        extra_input = readline (LIGHT_GREEN SIGN RESET);
        if (extra_input == NULL)
        {
            add_history(input);
            printf("%s", "syntax error: unexpected end of file\n");
            free(input);
            return (NULL);
        }
        input = join_input (input, extra_input);
        input = ft_trimmer (input);
    }
    return (input);
}

void ft_start_minishell(t_env * env_struct)
{
    char *input;
    t_cmd **commands;

    while(1) 
    {
        manage_signals();
        input = readline(LIGHT_GREEN PROMPT CYAN SIGN RESET);
        if (input == NULL)
            break ;
        input = ft_trimmer(input);
        if (!input[0])
            continue ;
        if (input[strlen(input) - 1] == '|')
            input = handle_ending_pipe(input);
        if (input == NULL)
            continue ;
        add_history(input);
        commands = begin_parsing(input, env_struct);
		execute(commands, env_struct);
        free(input);
    }
    free_env(env_struct);
}

int main(int argc, char **argv, char **env_sys)
{
    (void)argc;
    (void)argv;


	ft_terminal_non_print_off();
	manage_signals();
	ft_start_minishell(env_alloc_n_make(env_sys));
	return(0);
}

//free commands struct //to be written

//ft_exit function //to be written





