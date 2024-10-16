#include "../minishell.h"

void	sigeof(t_msh *msh)
{
	if (isatty(STDIN_FILENO))
		exit_cleanup("User says 'Be Gone Thot!'", msh, errno, 1);
	else if (msh->pexe != NULL)
	{
		write(STDOUT_FILENO, "\n", 1);
		exit_cleanup(NULL, msh, errno, 0);
	}
	else
		return ;
}

void	sigquit(t_msh *msh, int i)
{
	if (isatty(STDIN_FILENO))
		return ;
	else
	{
		while (msh->chds[i])
			kill(msh->chds[i++]->pid, SIGQUIT);
		exit_cleanup("Quit", msh, errno, 0);
	}
}

void	sig_do(t_msh *msh, int sig, int i)
{
	msh->interrupted = 1;
	if (sig == SIGINT)
	{
		if (msh->pexe != NULL || msh->parse != NULL)
		{
			if (msh->hd_temp)
			{
				close(msh->parse->here_fd);
				unlink(msh->hd_temp);
			}
			exit_cleanup(NULL, msh, errno, 0);
		}
		else
		{
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
		}
	}
	if (sig == SIGQUIT)
		sigquit(msh, i);
}

void	signals_handler(int sig)
{
	t_msh	*msh;
	int		i;

	i = 0;
	msh = get_msh_instance(NULL);
	write(STDOUT_FILENO, "\n", 1);
	sig_do(msh, sig, i);
}

void	signal_handler_init(t_msh *msh)
{
	struct sigaction	sa;

	get_msh_instance(msh);
	sa.sa_handler = signals_handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGINT, &sa, NULL) == -1)
		exit_cleanup(NULL, msh, errno, 2);
	if (isatty(STDIN_FILENO))
		sa.sa_handler = SIG_IGN;
	else
		sa.sa_handler = signals_handler;
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
		exit_cleanup(NULL, msh, errno, 2);
}
