/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npavelic <npavelic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 14:08:18 by npavelic          #+#    #+#             */
/*   Updated: 2023/12/03 20:50:52 by npavelic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//includes
# include <colors.h>

# include "../libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <signal.h>

# include <readline/readline.h>
# include <readline/history.h>

# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>

# include <fcntl.h>

# include <string.h>
# include <limits.h>
# include <stdarg.h>
# include <errno.h>
# include <stdbool.h>

// # include <termios.h> not needed anymore until the sigint stops working correctly

//variables
# define PROMPT "Bash4Cash💸"
# define SIGN "-> "
// # define MAX_LEN_COMMAND = 1024; //not needed most probably
# include <valgrind/valgrind.h> // testing purposes
# include <valgrind/memcheck.h> // testing purposes


//copied
typedef struct s_env
{
    char	**env_var;
    char	**ev_name;
    char	**ev_value;
    int		lst_exit_value;
}            t_env;

//copied for now //will be changed
typedef struct s_cmd
{
	char	*command;
	char	**arguments;
	
	int		fd[2];
	int		pid;

	char	**input_docs;
	char	*inp_doc_types;

	char	**output_docs;
	char	*out_doc_types;

	int 	num_of_structs;
}			t_cmd;

//signals.c
void	sigquit_signal(int signum);
void	sigint_signal(int signum);
void	manage_signals(void);

//non_print_off.c
void	ft_terminal_non_print_off(void);

// env.c + 2 static functions
void	create_env(char **env, t_env *e_vars);


//for input mapping

# define W_BEGINS 3
# define W_BODY 2
# define COM_START 4
# define COM_BODY 1
# define PIPE 7
# define RD_RIGHT 8
# define RD_LEFT 9
# define RD_RG_AP -8
# define RD_H_DOC -9
# define FLAG_START 6
# define FLAG_BODY 5
# define END -11
# define WHITESPACE 0
# define PLACEHOLDER -2
# define OUTPT_APPEND -7
# define OUTPT_OVER -5
# define INPUT_FILE -4
# define HEREDOC -6

# define VAR_START 5
# define VAR_BODY 4
# define EX_VAL_1 1
# define EX_VAL_2 6

//main
void free_double_array(char **array);
char    *join_input (char    *first_part, char    *second_part);
char *handle_ending_pipe(char *input);
void ft_start_minishell(t_env * env_struct);

// parsing_begins.c

t_cmd	**begin_parsing(char *input, t_env * env_struct);
int		is_whitespace(char c);
char	*ft_trimmer(char *input);

// numeric_map_parse.c

int		*numeric_mapping(char *input);
int		*quotes_check(char *input, int *numeric_map, int i);
int		*map_words_pipes_redirs(char *input, int *numeric_map, int i);
int		*fill_with_placeholders (int *numeric_map, int i);

void print_num_array(int *numeric_map, int null_pos, int j); //test function, delete later

// input_validity_checks;

int		syn_error_print(char *signs, char c);
int		symbols_are_invalid(int *numeric_map);

//TEST temporary token executable
char **temporary_token_function (int *numeric_map, char *input, t_env *envs, int *i);
void print_string_array(char ** string_array);


// env_structuring.c
t_env *env_alloc_n_make(char **env_sys);
//int	ft_env(t_env *env); //test func delete later

// map_comm_pip_redir.c
int*	map_commands (int *numeric_map, int i);
int	*mark_redirs(int *numeric_map);
int	*adjust_redirs(int *numeric_map);

// comm_struc_make.c
t_cmd	**create_command_struct(int *numeric_map, char *input, t_env *envs);
char	*remove_quotes (char *word);
char	*handle_word(char *word, t_env *env);


// temp_arg_array.c
char **temporary_input_to_args (int *numeric_map, char *input, int word_count, int *i);

// interpreting_subwords.c
char	**interprete_subwords(char **subwords, int i, t_env *env);
char	*vars_handler(char *word, t_env *env);

// chop_and_reconstruct_word.c
char	*chop_and_reconstruct_word(char *word, int *subw_numeric, t_env *env);
char	*turn_str_array_into_one_str(char **array);
void	free_str_arr(char	**str_ar);


// com_struc_docs.c
void	redirs_into_struct(t_cmd	***command_table, char *input, t_env *envs, int* numeric_map);

// com_struc_inputs.c
void	redirs_into_struct_2_input(t_cmd	***command_table, char *input, t_env *envs, int* numeric_map);


// execution.c
void create_pipes(t_cmd **cmds);
void close_pipes_parent(t_cmd **cmds);
int wait_for_children(t_cmd *cmds, t_env *env);
char *find_script(char *script, t_env *env);
char **change_command_to_argv(t_cmd cmd);
void proc_signal_handler(void);
int execute_path(char *bin_path, t_env *env, t_cmd cmd);
int find_in_path(t_cmd cmd, t_env *env);
int execute_fork_command(t_cmd *cmd, t_env *env);
void close_pipes_children(t_cmd **cmds, int i);

int execute(t_cmd **cmds, t_env *env);

// TEST EXECUTION
void test_execution (char *cmd, char**args, char** envp);
void addStringToCharArray(char*** array, char* str);




void sort_env_ascii(char **env, int size, t_env *env_struct);
#endif