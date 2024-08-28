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

void	check_if_exit(t_msh *msh)
{
	if (ft_strlen(msh->input) == 4 && !ft_strncmp("exit", msh->input, 4))
		exit_cleanup("User says 'Be Gone Thot!'", msh, errno, 1);
}

int	minishell_running(t_msh *msh)
{
	add_history(msh->input);
	check_if_exit(msh);
	if (parse_main(msh) == 0)
		execution(msh);
	if (msh->input != NULL)
	{
		free(msh->input);
		msh->input = NULL;
	}	
	return (EXIT_RESTART);
}

int	minishell_start(t_msh *msh, int ac, char **av, char **envp)
{
	int	loop;

	loop = 1;
	clean_msh_init(msh);
	msh->exit_error = 0;
	signal_handler_init(msh);
	if (input_validate(ac, envp) != 0)
	{
		exit_cleanup("invalid input\n", msh, 0, 1);
		return ;
	}
	while (loop)
	{
		signal_input();
		msh->input = readline("Heart of Gold>> ");
		if (msh->input == NULL)
		{
			exit_cleanup("Problem in user input", msh, errno, 1);  //check what is the use of this function
			return ;
		}
		clean_msh_init(msh);
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
	minishell_start(msh, ac, av, envp);
	if (msh != NULL)
		free(msh);
	return (0);
}
