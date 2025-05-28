/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofische <cofische@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 10:20:09 by coline            #+#    #+#             */
/*   Updated: 2025/05/28 18:00:40 by cofische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"

int	input_validate(int ac, char **envp)
{
	if (ac > 1)
	{
		exit_cleanup("Invalid Input - too many arguments", NULL, errno, 2);
		return (-1);
	}
	else if (ac < 0)
	{
		exit_cleanup("Invalid Input", NULL, errno, 2);
		return (-1);
	}
	if (envp == NULL || *envp == NULL)
	{
		exit_cleanup("Invalid input - envp is missing", NULL, errno, 2);
		return (-1);
	}
	return (0);
}

t_pexe	*head(t_pexe *current)
{
	while (current->prev != NULL)
		current = current->prev;
	return (current);
}

t_msh	*get_msh_instance(t_msh *new_msh)
{
	static t_msh	*msh_instance = NULL;

	if (new_msh != NULL)
		msh_instance = new_msh;
	return (msh_instance);
}

void	copy_envp(t_msh *msh, char **envp)
{
	int		i;
	int		envp_len;
	char	**temp_envp;

	msh->envp = NULL;
	envp_len = 0;
	while (envp[envp_len] != NULL)
		envp_len++;
	temp_envp = malloc(sizeof(char *) * (envp_len + 1));
	if (temp_envp == NULL)
		exit_cleanup(NULL, msh, errno, 1);
	i = 0;
	while (i < envp_len)
	{
		temp_envp[i] = ft_strdup(envp[i]);
		if (temp_envp[i++] == NULL)
			exit_cleanup(NULL, msh, errno, 1);
	}
	temp_envp[i] = NULL;
	msh->envp = temp_envp;
}
