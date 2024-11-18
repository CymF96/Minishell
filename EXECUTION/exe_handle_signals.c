/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_handle_signals.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofische <cofische@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 09:22:32 by cofische          #+#    #+#             */
/*   Updated: 2024/11/18 13:07:45 by cofische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_sigint(t_msh *msh)
{
	msh->interrupted = 1;
	write(STDOUT_FILENO, "\n", 1);
	if (msh->pexe != NULL || msh->parse != NULL)
	{
		if (msh->hd_array)
		{
			close(msh->parse->here_fd);
			unlink_hd(msh);
		}
		exit_cleanup(NULL, msh, 130, 0);
	}
	else
	{
		msh->exit_error = 130;
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		msh->interrupted = 0;
	}
}

void	handle_sigquit(t_msh *msh)
{
	int	i;

	i = 0;
	msh->interrupted = 1;
	if (msh->hd_array)
	{
		close(msh->parse->here_fd);
		unlink_hd(msh);
	}
	if (msh->child)
	{
		while (msh->chds[i])
			kill(msh->chds[i++]->pid, SIGQUIT);
	}
	exit_cleanup(NULL, msh, 131, 0);
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
