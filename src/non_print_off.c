// experimental function simalar to their in order to make ^C go away while using ctrl + C signal.
//it is still apperaing, so it has to be made

/*
struct termios {
    tcflag_t c_iflag;   // Input modes
    tcflag_t c_oflag;   // Output modes
    tcflag_t c_cflag;   // Control modes
    tcflag_t c_lflag;   // Local modes
    cc_t c_cc[NCCS];    // Control characters
};
*/

//it's working for ctrl + c and ctrl + Z
#include "../inc/minishell.h"
#include <termios.h>

// first verion of the code

// void add_term_attribute(int fd, int flag)
// {
// 	struct termios term_flags;

// 	if (isatty(fd))
// 	{
// 		tcgetattr(fd, &term_flags);
// 		term_flags.c_lflag |= flag; //bitwise operator to add
// 		tcsetattr(fd, TCSANOW, &term_flags);
// 	}
// }

// void remove_term_attribute(int fd, int flag)
// {
// 	struct termios term_flags;

// 	if (isatty(fd))
// 	{
// 		tcgetattr(fd, &term_flags);
// 		term_flags.c_lflag &= ~flag ;// Bitwise AND with complement (~) to remove the flag
// 		tcsetattr(fd, TCSANOW, &term_flags);
// 	}
// }

// void ft_terminal_non_print_off(void)
// {
// 	add_term_attribute(STDIN_FILENO, ECHOCTL);
// 	remove_term_attribute(STDOUT_FILENO, ECHOCTL);
// 	remove_term_attribute(STDERR_FILENO, ECHOCTL);  
// }

//second option //also working

void ft_modify_attribute(int fd, int flag, int operation)
{
	struct termios term_flags;

	 if (isatty(fd)) 
	 {
        tcgetattr(fd, &term_flags);
        if (operation == 1) 
            term_flags.c_lflag |= flag;    // Add the flag 
		else if (operation == 0) 
            term_flags.c_lflag &= ~flag;   // Remove the flag
        tcsetattr(fd, TCSANOW, &term_flags);
    }
}

void ft_terminal_non_print_off(void)
{
	int flag;

	flag = ECHOCTL;
	ft_modify_attribute(STDIN_FILENO, flag, 1);   // Add the flag
    ft_modify_attribute(STDOUT_FILENO, flag, 0);  // Remove the flag
    ft_modify_attribute(STDERR_FILENO, flag, 0);  // Remove the flag
}
