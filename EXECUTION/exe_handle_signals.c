/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_handle_signals.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofische <cofische@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 09:22:32 by cofische          #+#    #+#             */
/*   Updated: 2024/11/08 16:30:47 by cofische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_sigint(t_msh *msh)
{
	msh->interrupted = 1;
	write(STDOUT_FILENO, "\n", 1);
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

void	handle_sigquit(t_msh *msh)
{
	int	i;

	i = 0;
	write(STDOUT_FILENO, "\n", 1);
	if (msh->child)
	{
		while (msh->chds[i])
			kill(msh->chds[i++]->pid, SIGQUIT);
	}
	exit_cleanup("Quit - Core Dump", msh, errno, 0);
}

void	signals_handler(int sig)
{
	t_msh	*msh;

	msh = get_msh_instance(NULL);
	if (sig == SIGINT)
	{
		handle_sigint(msh);
		return ;
	}
	if (sig == SIGQUIT)
	{
		handle_sigquit(msh);
		return ;
	}
}

void	signal_handlers_prompt(t_msh *msh)
{
	struct sigaction	sa;

	get_msh_instance(msh);
	sa.sa_handler = SIG_IGN;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
		exit_cleanup(NULL, msh, errno, 2);
	sa.sa_handler = signals_handler;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		exit_cleanup(NULL, msh, errno, 2);
}

void	signal_handlers(t_msh *msh)
{
	struct sigaction	sa;

	get_msh_instance(msh);
	sa.sa_handler = signals_handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGINT, &sa, NULL) == -1)
		exit_cleanup(NULL, msh, errno, 2);
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
		exit_cleanup(NULL, msh, errno, 2);
}
