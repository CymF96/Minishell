#include "../minishell.h"

static t_msh *global_msh;

void	sigeof(t_msh *msh)
{
	if (msh->pexe != NULL)//prompt in work and pexe initialized
		exit_cleanup(NULL, msh, errno, 0);
	else// nothing in prompt
		exit_cleanup(NULL, msh, errno, 1);

}

void	signals_handler(int sig)
{	
	if (sig == SIGINT)
	if (write(STDOUT_FILENO, "\n", 1) == -1)
		return ;
	if (global_msh->pexe != NULL)
		exit_cleanup(NULL, global_msh, 0, 0);
	else
	{
		rl_replace_line("", 0);  // Clear the current input line in readline
		rl_on_new_line();  // Move to a new line
		rl_redisplay();
	}
}

void	signal_handler_init(t_msh *msh)
{
	struct sigaction	sa;


	global_msh = msh;
	sa.sa_handler = signals_handler;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGINT, &sa, NULL) == -1)
		exit_cleanup(NULL, msh, errno, 2);
	sa.sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
		exit_cleanup(NULL, msh, errno, 2);
}
