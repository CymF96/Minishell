/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 17:32:51 by mcoskune          #+#    #+#             */
/*   Updated: 2024/09/08 15:50:49 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	input_validate(int ac, char **envp)
{
	if (ac > 1)
	{
		exit_cleanup("Too many clowns for this party", NULL, errno, 2);
		return (-1);
	}
	else if (ac < 0)
	{
		exit_cleanup("How did you even manage neg AC?", NULL, errno, 2);
		return (-1);
	}
	if (envp == NULL || *envp == NULL)
	{
		exit_cleanup("Where is my ENVP!", NULL, errno, 2);
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

void	remove_node(t_msh *msh, int heredoc, int g)
{
	t_pexe	*current;
	t_pexe	*delme;

	current = msh->pexe;
	while (current != NULL)
	{
		if (current->type == HEREDOC && heredoc > 1 \
				&& current->group_id == g)
		{
			heredoc--;
			delme = current;
			current = current->next;
			current->prev = delme->prev;
			delme->prev->next = current;
			unlink(delme->cmd);
			free(delme->cmd);
			free(delme);
			delme = NULL;
		}
		else
			current = current->next;
	}
}

t_msh	*get_msh_instance(t_msh *new_msh)
{
	static t_msh	*msh_instance = NULL;

	if (new_msh != NULL)
		msh_instance = new_msh;
	return (msh_instance);
}
