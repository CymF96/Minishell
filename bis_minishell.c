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

void	minishell_child(t_msh *msh)
{
	add_history(msh->input);
	check_if_exit(*msh);
	if (parse_main(msh) == 0)
		execution(msh)
	else
		exit(EXIT_FAILURE);
	free(msh->input);
	msh->input = NULL;
	exit(EXIT_REINITIALISE);
}

int	minishell_parent(t_msh *msh)
{
	int	status;
	int	exit_status;

	waitpid(msh->main_child, &status, 0);
	if (WIFEXITED(status) != 1)
	{
		exit_status = WEXITSTATUS(status);
		if (exit_status == EXIT_REINITIALISE)
			return (EXIT_REINITIALISE);
		else if (exit_status == EXIT_RESTART)
			return (EXIT_RESTART);
		else
		{
			perror("Error");
			exit(EXIT_FAILURE);
		}
	}
	else if (WIFSIGNALED(status))
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
}

void	minishell(t_msh *msh, int ac, char **av, char **envp)
{
	int	reinitialise;

	reinitialise = 1;
	while (reinitialise)
	{
		signal_input();
		msh->input = readline("Heart of Gold>> ");
		if (msh->input == NULL)
		{
			exit_cleanup("Problem in user input", msh, errno, 1);  //check what is the use of this function
			return ;
		}
		msh->main_child = fork();
		if (msh->main_child == 0)
			minishell_child(msh);
		else
		{
			if (minishell_parent(msh) == EXIT_RESTART)
				reinitialise = 0;
			else if (minishell_parent(msh) == EXIT_REINITIALISE)
				clean_msh_init(msh);
			else
				return ;			
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
		perror("Error");
		exit(EXIT_FAILURE);
	}
	clean_msh_init(msh);
	msh->exit_error = -1;
	signal_handler_init(msh);
	if (input_validate(ac, envp) != 0)
	{
		exit_cleanup("invalid input\n", msh, 0, 1);
		return ;
	}
	minishell(msh, ac, av, envp);
	exit_cleanup(NULL, msh, 0, 1);
	exit(EXIT_SUCCESS);
}
