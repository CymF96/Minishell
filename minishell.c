/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 18:40:56 by mcoskune          #+#    #+#             */
/*   Updated: 2024/08/19 13:53:52 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// #include "./PARSE/parse.h"

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
		if (parse_main(&msh) == 0)
			execution(&msh);
		free(msh.input);
		msh.input = NULL;
	}
}
