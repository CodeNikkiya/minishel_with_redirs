#include "../inc/minishell.h"

/*struct sigaction 
{
    void (*sa_handler)(int);       // Pointer to the signal handler function or action
    sigset_t sa_mask;              // Set of signals to be blocked during the handler
    int sa_flags;                  // Flags for signal handling behavior
    void (*sa_sigaction)(int, siginfo_t *, void *); // Pointer to the signal handler function (alternative to sa_handler)
};*/

void sigquit_signal(int signum)
{
    if (signum == SIGQUIT)
    {
        exit(EXIT_FAILURE);
    }
}

void sigint_signal(int signum)
{
    if (signum == SIGINT)
    {
		//rl_replace_line("", 0);
        printf("\n");
        rl_on_new_line();
        rl_redisplay();
    }
}

void manage_signals(void)
{
    struct sigaction sa_int;
    struct sigaction sa_quit;
   
// Configuration the SIGINT signal handler
   sa_int.sa_handler = sigint_signal;
//initializes an empty signal set for the sa_quit signal action. 
//This ensures that no signals are blocked (masked) while the pc_sigquit_handler
// signal handler is running, allowing it to execute without interference from other signals.
   sigemptyset(&sa_int.sa_mask);
   sa_int.sa_flags = 0;
   sigaction(SIGINT, &sa_int, NULL);

    // Configuration of the SIGQUIT signal handler
   sa_quit.sa_handler = sigquit_signal;
   sigemptyset(&sa_quit.sa_mask);
   sa_quit.sa_flags = 0;
   sigaction(SIGQUIT, &sa_quit, NULL);
}
