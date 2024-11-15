/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 18:40:56 by mcoskune          #+#    #+#             */
/*   Updated: 2024/11/15 15:15:22 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell_running(t_msh *msh)
{
	add_history(msh->input);
	if (check_if_exit(msh))
		return ;
	if (!ft_strncmp("$$", msh->input, 2))
		return ;
	if (parse_main(msh) == 0)
		execution(msh);
	exit_cleanup(NULL, msh, 0, 0);
}

void	minishell_start(t_msh *msh, int ac, char **envp)
{
	int	loop;

	loop = 1;
	clean_msh_init(msh);
	copy_envp(msh, envp);
	msh->envp_flag = 0;
	msh->exit_error = 0;
	if (input_validate(ac, envp) != 0)
		exit_cleanup("invalid input\n", msh, 0, 1);
	while (loop)
	{
		signal_handlers_prompt(msh);
		msh->input = readline("Heart of Gold>> ");
		if (msh->input == NULL)
			exit_cleanup("User says 'Be Gone Thot!'", msh, errno, 1);
		signal_handlers(msh);
		minishell_running(msh);
		clean_msh_init(msh);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_msh	msh;

	(void)av;
	minishell_start(&msh, ac, envp);
	return (0);
}
