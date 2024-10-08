/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 18:40:56 by mcoskune          #+#    #+#             */
/*   Updated: 2024/10/07 16:50:16 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_if_exit(t_msh *msh)
{
	char	*temp;

	temp = malloc(sizeof(char) * (ft_strlen(msh->input) + 1));
	if (temp == NULL)
		exit_cleanup("Malloc Failed", msh, errno, 2);
	remove_quotes(msh->input, ft_strlen(msh->input), temp);
	if (ft_strlen(temp) == 4 && !ft_strncmp("exit", temp, 4))
	{
		free(temp);
		exit_cleanup("User says 'Be Gone Thot!'", msh, errno, 1);
	}
	free(temp);
}

void	minishell_running(t_msh *msh)
{
	add_history(msh->input);
	check_if_exit(msh);
	if (!ft_strncmp("$$", msh->input, 2))
		return ;
	if (parse_main(msh) == 0)
	{
		//printf("Exec Would ve Happened\n");
		execution(msh);
	}
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
	signal_handler_init(msh);
	if (input_validate(ac, envp) != 0)
		exit_cleanup("invalid input\n", msh, 0, 1);
	while (loop)
	{
		msh->input = readline("Heart of Gold>> ");
		if (msh->input == NULL)
			sigeof(msh);
		minishell_running(msh);
		clean_msh_init(msh);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_msh	*msh;

	(void)av;
	msh = malloc(sizeof(t_msh));
	if (msh == NULL)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
	minishell_start(msh, ac, envp);
	if (msh != NULL)
		free(msh);
	return (0);
}
