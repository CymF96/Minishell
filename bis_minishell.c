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

void	minishell(t_msh *msh, int ac, char **av, char **envp)
{
	if (input_validate(ac, envp) != 0)
	{
		exit_cleanup("invalid input\n", msh, 0, 1);
		return ;
	}
	while (1)
	{
		signal_input();
		msh->input = readline("Heart of Gold>> ");
		if (msh->input == NULL)
			exit_cleanup("Problem in user input", msh, errno);
		msh->main_child = fork();
		if (msh->main_child == 0)
		{
			add_history(msh->input);
			check_if_exit(*msh);
			if (parse_main(msh) == 0)
				execution(msh);
			free(msh->input);
			msh->input = NULL;
		}
		else
		{
			wait(&msh->exit_error);
			kill(msh->main_child, SIGKILL);
			if (msh->exit_parent != 0)
				exit_cleanup(NULL, msh, 0, 1);
		}
	}
}

int main(int ac, char **av, char **envp)
{
	t_msh	*msh;

	(void)av;
	msh = malloc(sizeof(t_msh));
	if (msh == NULL)
	{
		ft_printf("Error\n");
		exit(EXIT_FAILURE);
	}
	clean_msh_init(msh);
	signal_handler_init(msh);
	minishell(msh, ac, av, envp); 
	exit(EXIT_SUCCESS);
}
