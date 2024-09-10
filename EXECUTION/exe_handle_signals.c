#include "../minishell.h"

t_msh	*get_msh_instance(t_msh *new_msh) 
{
	static t_msh *msh_instance = NULL;
	
	if (new_msh != NULL)
		msh_instance = new_msh;
	return (msh_instance);
}

void	sigeof(t_msh *msh)
{
	if (msh->pexe != NULL)
		exit_cleanup(NULL, msh, errno, 0);
	else
		exit_cleanup(NULL, msh, errno, 1);

}

void signals_handler(int sig)
{
	t_msh *msh; 
	
	msh = get_msh_instance(NULL);
	if (sig == SIGINT)
	if (write(STDOUT_FILENO, "\n", 1) == -1)
		return ;
	if (msh->pexe != NULL)
		exit_cleanup(NULL, msh, 0, 0);
	else
	{
		rl_clear_history();
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	signal_handler_init(t_msh *msh)
{
	struct sigaction	sa;
	
	get_msh_instance(msh);
	sa.sa_handler = signals_handler;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGINT, &sa, NULL) == -1)
		exit_cleanup(NULL, msh, errno, 2);
	sa.sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
		exit_cleanup(NULL, msh, errno, 2);
}
