#include "../inc/minishell.h"

// 		t_cmd ;

// int ft_strlen(const char *str) 
// {
// 	int len = 0;
// 	while (str[len] != 0) 
// 		len++;
// 	return len;
// }


static int find_ev_var(t_env *env, char *ev_name) {
  int i = 0;
  while (env->env_var[i] != NULL) 
  {
    if (strcmp(env->ev_name[i], ev_name) == 0) //has to be chnage for libft
        return (i);
    i++;
  }
  return (-1);
}

static int find_dollar_sign(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[0] == '$' && i > 0)
			return (1);
		i++;
	}
	return (0);
}
static int count_env(char **env)
{
	int i;

	i = 0;
	while (env[i] != 0)
		i++;
	return (i);
}

int print_export(t_cmd *command, t_env *env)
{
	int size;

	// size = 0;
	// while (env->env_var[size] != NULL)
	// {
	// 	printf("env_var: %s\n", env->env_var[size]);
	// 	size++;
	// }
	if (!command->arguments[0] || find_dollar_sign(command->arguments[0]) == 1)
		{
		
			size = count_env(env->env_var);
			printf("size after %i\n", size);
			sort_env_ascii(env->env_var, size, env);
			return (1);
		}
	return (0);
}

int is_alphanumeric_or_special_char(char c) 
{
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '=' || c == '_') 
	{
        return 1;
    }
    return 0;
}
static int check_for_valid_args(t_cmd *command)  // chck if the firt char of work is valid can be letter or _
{
	int i;
	int j;

	i = 0;
	while (command->arguments[i] != (void *)0)
	{
		j = 0;
		while (command->arguments[i][j] != '\0' && command->arguments[i][j] != '=')
		{
			if (is_alphanumeric_or_special_char(command->arguments[i][j]) == 0)
			{
				printf("%s: export: `%s': not a valid identifier\n", PROMPT, command->arguments[i]);
				return (1);
			}
			else if (command->arguments[i][j] == '$' && command->arguments[i][j + 1] == '\0')
			{
				printf("%s: export: `%s': not a valid identifier\n", PROMPT, command->arguments[i]);
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}


int find_char(char *str, char c)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}
// static int find_equal_sign(char *arg)
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

static int count_len_til(char *arg, char c)
{
	int i;

	i = 0;
	while (arg[i] != '\0')
	{
		if (arg[i] == c)
			break;
		i++;
	}
	return (i);
}

static char *find_name(char *arg)
{
	int i;
	char *name;

	i = count_len_til(arg, '=');
	name = malloc(sizeof(char) * (i + 1));
	if (name == NULL)
		return (NULL);
	i = 0;
	while (arg[i] != '\0')
	{
		if (arg[i] == '=')
			break;
		name[i] = arg[i];
		i++;
	}
	name[i] = '\0';
	return (name);
}

static char *find_value(char *arg) // returns char poinrt to NULL if there's no equal sign
{
	int i;
	int j;
	char *value;

	i = count_len_til(arg, '=');
	j = ft_strlen(arg) - i;
	if (find_char(arg, '=') == 0)
		j = 0;
	i++;
	value = malloc(sizeof(char) * (j + 1));
	if (value == NULL)
		return (NULL);
	j = 0;
	while (arg[i] != '\0')
	{
		value[j] = arg[i];
		i++;
		j++;
	}	
	value[j] = '\0';
	return (value);
}

static void change_env_val_for_ev_value(t_env *env, char *value, int var_index)
{
	size_t new_env_var_len;
	char *new_env_var;

	new_env_var_len = ft_strlen(value) + 1;
	new_env_var = malloc(new_env_var_len);
	if (new_env_var == NULL) // not sure it will stay like this
		return;
	memcpy(new_env_var, value, ft_strlen(value));
	new_env_var[new_env_var_len - 1] = '\0';
	free(env->ev_value[var_index]);
	env->ev_value[var_index] = new_env_var;
}

static void change_env_val(t_env *env, char *name, char *value, int var_index, int has_equal_sign)
{
	size_t new_env_var_len;
	char *new_env_var;

	if (has_equal_sign)
		new_env_var_len = ft_strlen(name) + ft_strlen(value) + 2; //one more for equal sign
	else
		new_env_var_len = ft_strlen(name) + ft_strlen(value) + 1; //  
  	new_env_var = malloc(new_env_var_len);
	if (new_env_var == NULL) // not sure it will stay like this
		return;
	memcpy(new_env_var, name, ft_strlen(name));
	if (has_equal_sign)
	{
			new_env_var[ft_strlen(name)] = '=';
			memcpy(new_env_var + ft_strlen(name) + 1, value, ft_strlen(value));
	}
	else
		memcpy(new_env_var + ft_strlen(name), value, ft_strlen(value)); //has to be changed for libft
	change_env_val_for_ev_value(env, value, var_index);
}

static char **ft_add_str_to_array(char **array, char *str)
{
	int i;
	int size;
	char **new_array;
	printf("test: ft_add_str_to_array: %s\n", str);
	i = 0;
	size = 0;
	while (array[size] != NULL)
		size++;
	new_array = malloc(sizeof(char *) * (size + 2));
	if (new_array == NULL)
		return (NULL);
	while (i < size)
	{
		new_array[i] = array[i];
		i++;
	}
	new_array[i] = str;
	new_array[i + 1] = NULL;
	free(array);
	return (new_array);
}

static void add_new_var(t_env *env, char *name, char *value, int has_equal_sign)
{
	int size;
	char *env_var;

	size = ft_strlen(name) + ft_strlen(value);
	if (has_equal_sign)
		size = ft_strlen(name) + ft_strlen(value) + 1;
	env_var = malloc(sizeof(char) * (size + 1));
	if (env_var == NULL)
	  return; // may need a change
	strcpy(env_var, name); // has to be chned for the libft version
	if (has_equal_sign)
		strcat(env_var, "="); //has to be change for the libft version
	strcat(env_var, value); 

	env->env_var = ft_add_str_to_array(env->env_var, env_var);
	env->ev_name = ft_add_str_to_array(env->ev_name, name);
	env->ev_value = ft_add_str_to_array(env->ev_value, value);
	// for testing
	// size = 0;
	// while (env->env_var[size] != NULL)
	// {
	// 	printf("env_var: %s\n", env->env_var[size]);
	// 	size++;
	// }
}
	



int ft_export(t_cmd *command, t_env *env)
{
	char *name;
	char *value;
	int i;
	int var_index;
	int has_equal_sign;

	i = 0;

	if (print_export(command, env) == 1 || check_for_valid_args(command) == 1)
		return (0); // not sure if it should be 1 or 0 or something else
	while (command->arguments[i]) // not sure if there's NULL at th end of args
	{	
		name = find_name(command->arguments[i]); 
		value = find_value(command->arguments[i]);
		has_equal_sign = find_char(command->arguments[i], '=');
		var_index = find_ev_var(env, name);
		if (var_index == -1)
			add_new_var(env, name, value, has_equal_sign); //has to be changed
		else
			change_env_val(env, name, value, var_index, has_equal_sign); //has to be changed
		free(name);
		free(value);
		var_index = -1;
		i++;
	}
	return (0);

	
}