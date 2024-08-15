/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 18:40:56 by mcoskune          #+#    #+#             */
/*   Updated: 2024/08/14 16:29:54 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av, char **envp)
{
	t_msh	msh;

	(void)av;
	input_validate(ac, envp);
	clean_initialize(&msh);
	while (1)
	{
		msh.input = readline("Heart of Gold>> ");
		if (msh.input == NULL)
			exit_cleanup("Problem in user input", &msh, errno);
		add_history(msh.input);
		check_if_exit(msh);
		parse_input(&msh);
		execution(&msh);
		free(msh.input);
		msh.input = NULL;
	}
	exit_cleanup(NULL, NULL, 0);
}
