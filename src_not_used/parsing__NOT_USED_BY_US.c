
//just a draft of the code, nothing has been tested

t_command ft_input_handler(t_env *env, char *input) //pc_parse_raw_input
{
	t_command table;
	input = ft_trimmer(input); //trimmmer in trimmer.c file
	input = quotes_not_closed(input);
	if (!*input)
		return (0);
	//removing the part about checking for the varaibles inside the double quotes, that will be checked later
	if (!input)
		ft_quit(env, "failed to interprete var", 2); //function have to be witten, don't know if we need it (probably don't)
	table = ft_get_command_table; //pc_get_command_table
	return (table);
}
char *split_input(char *input) //their takes double pointer of course
{
	// pc_escape_pipe(input); // function is responsible for "escaping" the pipe character (|) in the input string. This means that if the pipe character is within a pair of quotes (single or double), it will be replaced with a special character (in this case, the value 1).
	// splited_input = ft_split(*input, '|'); //splitting the input here by | that is not inside strings
	// splited_input = pc_unescape_pipe(splited_input); finding those numbers (1) and repleacing back with | //can it be done differently?
	while (splited_input[i])
	{
		j = 0;
		only_spaces = 1;
		while (splited_input[i][j])
		{
			if (splited_input[i][j++] != ' ')
				only_spaces = 0;
		}
		if (only_spaces)
			return (0);
		//If the only_spaces flag remains 1, indicating the fragment has only spaces, the function returns 0 to signal an error.
		i++;
	}
	return (splited_input);

}


void ft_initialize_table(t_command *table_elem) //new function to just initialize those outside for better redability of the previous function
{
	table_elem->command = NULL;
	table_elem->arguments = NULL;
	table_elem->flags = NULL;
}

t_command *ft_get_command_table(char *input)
{
	t_command table;
	char *splitted_input;
	int size_of_tab;
	int i;

	splitted_input = ft_split_input(input); //has to be writtem //I ma following the same structure as them so far //their pc_input_validation
	if (!splitted_input)
		return (0);
	size_of_tab = ft_get_words_count(input, '|') // ft_get_number_of_words //has to be writtem
	table = (t_command)malloc(sizeof(t_command) * (size_of_tab + 1));
	i - 0;
	while (splitted_input[i])
	{
		ft_initialize_table(table[i]);
		ft_get_commands(table[i], splitted_input[i]); // pc_get_command //has to be written
		i++;
	}
	table[i].command = 0; 
	free_table(splitted_input); //pc_clear_2d_tab //has to be written
	return (table);
}
