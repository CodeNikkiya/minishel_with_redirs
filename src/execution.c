#include "../inc/minishell.h"

static int	ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

void	pc_clear_2d_tab(char **tab)
{
	int	i;

	i = -1;
	if (tab)
	{
		while (tab[++i])
			free(tab[i]);
		free(tab);
	}

}

static char *find_path(t_env *env, char *name) 
{
	int i;
	
	i = 0;
	while (env->env_var[i] != NULL) 
	{
		 if (ft_strcmp(env->ev_name[i], name) == 0)
		{
			// printf("%s\n", env->ev_value[i]);
			return (env->ev_value[i]);
		}
	i++;
	}
	return (NULL);
}
void create_pipes(t_cmd **cmds) 
{
    int i = 0;
	while (i < (cmds[0]->num_of_structs))
	{
		printf ("Pipe is nr %i out of %i\n", i , cmds[i]->num_of_structs);
        if (pipe(cmds[i]->fd) < 0) 
		{
            // exit_program(); // function that clears data and then stops the program have to be written here
        }
		printf ("Pipe that was just made is %i out of %i and the FD 0 and 1 are, %i & %i \n", i , cmds[i]->num_of_structs, cmds[i]->fd[0], cmds[i]->fd[1]);
        i++;
    }
}
void close_pipes_parent(t_cmd **cmds) // 
{
	int i;

	i = 0;
	printf("test: close_pipes_parent\n");
	while (i < (cmds[0]->num_of_structs))
	{
		printf("test: close_pipes_parent 2\n");
		close(cmds[i]->fd[0]);
		close(cmds[i]->fd[1]);
		i++;
	}
	printf("test: close_pipes_parent 333333333333\n");
}

int wait_for_children(t_cmd *cmds, t_env *env) // pc_wait_for_children
 {
	int	i;
	int	result;

	i = -1;
	
	while (cmds[++i].command)
		wait(&result);
	if (cmds[i - 1].pid == 0)
		return (env->lst_exit_value);
	return (WEXITSTATUS(result) % 255);
 }

char *find_script(char *script, t_env *env)
{
		char	*tmp;
	char	*tmp2;
	char	*result;

	if (script[0] == '.')
	{
		tmp = ft_substr(script, 1, ft_strlen(script) - 1);
		tmp2 = find_path(env, "PATH"); // function form cd.c / maybe some part needed in case there's no PWD
		result = ft_strjoin(tmp2, tmp);
		free(tmp);
		free(tmp2);
		return (result);
	}
	else
		return (script);
}

// char **change_command_to_argv(t_cmd cmd) // pc_change_command_to_str
// {
// 	char	**argv;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	while (cmd.arguments[i])
// 		i++;
// 	argv = malloc(sizeof(char *) * (i + 3));
// 	i = 0;
// 	argv[i] = ft_strdup(cmd.command);
// 	// if (cmd.flags)
// 	// 	argv[++i] = ft_strjoin("-", cmd.flags);
// 	j = 0;
// 	if (cmd.arguments)
// 	{
// 		while (cmd.arguments[j])
// 		{
// 			argv[++i] = ft_strdup(cmd.arguments[j++]);
// 		}
// 	}
// 	argv[++i] = 0;
// 	return (argv);
// }

void	proc_signal_handler(void) // copied from other code, we may put our own function here
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

int execute_path(char *bin_path, t_env *env, t_cmd cmd) // pc_execute_path
{
	pid_t	pid;
	int		result;
	// char	**argv;

	pid = fork();

	result = 0;
	proc_signal_handler();
	if (pid == 0)
	{
		printf("cmd:%s\n", cmd.command);
	
		addStringToCharArray(&cmd.arguments, cmd.command);
		printf("argv including command:\n");
		print_string_array(cmd.arguments);
		// printf("bbbbbbbbbbbbbb:\n");
		result = execve(bin_path, cmd.arguments, env->env_var);
	}
	else if (pid < 0)
	{
		free(bin_path);
		ft_putstr_fd("Fork failed", 2);
		return (-1);
	}
	wait(&result);
	free(bin_path);
	// pc_clear_2d_tab(argv);// that part not needed
	env->lst_exit_value = result;
	return (result);
}


static char	*ft_pathjoin(char *p1, char *p2)
{
	char	*tmp2;
	char	*tmp1;

	if (!p2 || !p1)
		return (NULL);
	if (!ft_strncmp(p1, "/", 1))
	{
		if (p2[0] == '/')
			return (ft_strjoin(p1, p2));
		else
		{
			tmp1 = ft_strjoin(p1, "/");
			tmp2 = ft_strjoin(tmp1, p2);
			free(tmp1);
			return (tmp2);
		}
	}
	else
	{
		if (p2[0] == '/')
			return (ft_strjoin(p1, p2 + 1));
		else
			return (ft_strjoin(p1, p2));
	}
}

static int	pc_check_permision(struct stat file)
{
	if ((file.st_mode > 0) && (S_IEXEC & file.st_mode) && S_ISREG(file.st_mode))
	{
		if (file.st_mode & S_IXUSR)
			return (1);
		else
			ft_putstr_fd("File is not executable", 2);
	}
	else
		ft_putstr_fd("This is not a file", 2);
	return (0);
}

int	pc_find_binary(t_env *env, t_cmd com, char *bin_path, char **path)
{
	struct stat	file;
	int			i;

	i = -1;
	while (path && path[++i])
	{
		bin_path = ft_pathjoin(path[i], com.command);
		if (lstat(bin_path, &file) != -1)
		{
			pc_clear_2d_tab(path); 
			if (pc_check_permision(file)) 
				return (execute_path(bin_path, env, com)); // pc_execute_path
		}
		else
			free(bin_path);
	}
	return (127);
}


int find_in_path(t_cmd cmd, t_env *env) // pc_find_path
{
	char		*bin_path;
	char		**path;
	char		*tmp;
	int			ret_val;

	if (cmd.command[0] == '.' || cmd.command[0] == '/')
	{
		bin_path = find_script(cmd.command, env); 
		return (execute_path(bin_path, env, cmd)); 
	}
	tmp = find_path(env, "PATH"); // function is from the cd.c
	if (!tmp)
		return (127);
	path = ft_split(tmp, ':');
	free(tmp);
	bin_path = 0;
	ret_val = pc_find_binary(env, cmd, bin_path, path); 
	if (ret_val == 127)
	{
		printf("%s: %s: command not found\n", PROMPT, cmd.command);
		pc_clear_2d_tab(path); // not sure about this functi

	}
	return (ret_val);
}

int execute_fork_command(t_cmd *cmd, t_env *env)
{
	// if (ft_strcmp(cmd.command, "echo", ft_strlen(cmd.command)) == 0)
	// 	return (ft_echo(cmd, env)); // for testing we will be using exceve here
	// else if (ft_strcmp(cmd.command, "env", ft_strlen(cmd.command)) == 0)
	// 	return (ft_env(cmd, env));
	
	return(find_in_path(*cmd, env)); // we have to write this function
	
}

void close_pipes_children(t_cmd **cmds, int i) // pc_close_pipes_children
{
	int j;

	j = 0;
	printf("test_cloe_pipes_childern\n");
	while (j < cmds[0]->num_of_structs)
	{
		printf("test_cloe_pipes_childern 2\n");
		if (j != i)
		{
			close(cmds[j]->fd[0]);
		if (j != i - 1)
			close(cmds[j]->fd[1]);
		}
		printf("test_cloe_pipes_childern 3\n");
		j++;
	}
	printf("test_cloe_pipes_childern 4\n");
}
// void clear_data(t_cmd *)
static void fork_child(t_cmd **cmd, t_env *env, int i) // pc_fork_child
{
	printf("test_fork_child\n");
	cmd[i]->pid = fork();
	printf("test_fork_child 2\n");
	if (cmd[i]->pid == -1)
		exit(1); // function that clears data and then stops the program have to be written here
	printf("test_fork_child 3\n");
	if (cmd[i]->pid == 0)
	{
		printf("test_fork_child 4\n");
		close_pipes_children(cmd, i);
		printf("test_fork_child 5\n");
		if((i + 1) < cmd[0]->num_of_structs) //segmentation fault was here // may need different condition for this if statement
			{
				printf("if_statement_fork_child");
				dup2(cmd[i]->fd[1], STDOUT_FILENO);
			}
		printf("test_fork_child 6\n");
		if (i != 0)
			dup2(cmd[i - 1]->fd[0], STDIN_FILENO);
		printf("test_fork_child 7\n");
		// redirections_check(cmd, env); for now no redirections
		env->lst_exit_value = execute_fork_command(*cmd, env);
		printf("test_fork_child 8\n");
		close(cmd[i]->fd[1]);
		printf("test_fork_child 9\n");
		if (i != 0)
			close(cmd[i - 1]->fd[0]);
		printf("test_fork_child 10\n");
		exit(env->lst_exit_value % 255);
	}
}
static int execute_not_fork_command(t_cmd *cmd, t_env *env) // pc_execute_not_fork_command // temporary commented out so, everything get redirected to exceve
{
	(void)cmd;
	(void)env;
	//if (ft_strcmp(cmd->command, "export") == 0)
	//	return (ft_export(cmd, env));
// 	// else if (ft_strcmp(cmd.command, "cd", ft_strlen(cmd.command)) == 0)
// 	// 	return (ft_cd(cmd, env));
// 	// else if (ft_strcmp(cmd.command, "pwd", ft_strlen(cmd.command)) == 0) // not sure if it's gonna be that way
// 	// 	return (ft_pwd(cmd, env));
// 	// else if (ft_strcmp(cmd.command, "unset", ft_strlen(cmd.command)) == 0)
// 	// 	return (ft_unset(cmd, env));
// 	// else if (ft_strcmp(cmd.command, "exit", ft_strlen(cmd.command)) == 0)
// 	// 	return (ft_exit(cmd, env));
	return (-1);
}

int execute(t_cmd **cmds, t_env *env)// we need also env to execute our builtins // pc_exec_commands
{
	int i;
	int result;

	i = 0;
	// count = structs_count()
	//printf("test 1\n");
	create_pipes(cmds); // for making child and parent communicate // changed to take double pointer
	// printf("first struct fd:%i\n", *cmds[i].fd);
	//printf("test 2\n");
	print_string_array((*cmds)->arguments);
	while (i < cmds[0]->num_of_structs)
	{	
		
		//printf("test 3\n");
		//printf("command: %s\n", cmds[i]->command);
		//printf("fd 0:%i\n", cmds[i]->fd[0]);
		//printf("fd 1:%i\n", cmds[i]->fd[1]);
//
		result = execute_not_fork_command(cmds[i], env);
		//printf("test 4\n");
		cmds[i]->pid = 0;
		if (result == -1)
		{
			fork_child(cmds, env, i);
			//printf("test 5\n");
		}
		else
			env->lst_exit_value = result;
		i++;
	}
	// printf("test 6\n");
	close_pipes_parent(cmds);
	//printf("test 7\n");
	// wait_for_children(cmds);
	return (wait_for_children(*cmds, env)); // not sure if it's gonna be that way
}
