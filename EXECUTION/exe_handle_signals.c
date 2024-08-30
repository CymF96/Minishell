#include "../minishell.h"

void	sigeof(t_msh *msh)
{
	if (msh->pexe != NULL)//prompt in work and pexe initialized
		exit_cleanup(NULL, msh, errno, 0);
	else// nothing in prompt
		exit_cleanup(NULL, msh, errno, 1);

}

void	signals_handler(int sig, siginfo_t *info, void *context)
{
	t_msh *msh = (t_msh *)context;
    (void)info;
	
	if (sig == SIGINT)
	if (write(STDOUT_FILENO, "\n", 1) == -1)
		return ;
    rl_replace_line("", 0);  // Clear the current input line in readline
	if (msh->pexe != NULL)
		exit_cleanup(NULL, msh, errno, 0);    
	rl_on_new_line();  // Move to a new line
    rl_redisplay();
}

void	signal_handler_init(t_msh *msh)
{
	struct sigaction	sa;

	sa.sa_sigaction = signals_handler;
	sa.sa_flags = SA_RESTART | SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGINT, &sa, NULL) == -1)
		exit_cleanup(NULL, msh, errno, 2);
    sa.sa_handler = SIG_IGN;
    if (sigaction(SIGQUIT, &sa, NULL) == -1)
        exit_cleanup(NULL, msh, errno, 2);
}
