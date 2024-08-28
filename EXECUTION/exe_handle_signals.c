#include "../minishell.h"

void	signal_input(t_msh *msh)
{
	if (signal_flags & SIGINT_FLAG)
	{
		signal_flags &= ~SIGINT_FLAG;
		sigint(msh);
	}
	else if (signal_flags & SIGQUIT_FLAG)
	{
		signal_flags &= ~SIGQUIT_FLAG;
		sigquit(msh);
	}
	else if (signal_flags & SIGEOF_FLAG)
	{
		signal_flags &= ~SIGEOF_FLAG;
		sigeof(msh);
	}
}

void	signals_handler(int sig)
{
	if (sig == SIGINT)
		signal_flags |= SIGINT_FLAG;
	else if (sig == SIGQUIT)
		signal_flags |= SIGQUIT_FLAG;
	else if (sig == EOF)
		signal_flags |= SIGEOF_FLAG;
}

void	signal_handler_init(t_msh *msh)
{
	struct sigaction	sa;

	sa.sa_handler = signals_handler;
	sa.sa_flags = SA_RESTART; // | SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGINT, &sa, NULL) == -1
		|| sigaction(EOF, &sa, NULL) == -1
		|| sigaction(SIGQUIT, &sa, NULL) == -1)
		exit_cleanup(NULL, msh, errno, 2);
}
