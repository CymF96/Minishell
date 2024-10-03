/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 11:45:44 by mcoskune          #+#    #+#             */
/*   Updated: 2024/10/03 11:51:52 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	swap(t_pexe *node_a, t_pexe *node_b)
{
	t_pexe	temp;

	temp.cmd = node_a->cmd;
	temp.group_id = node_a->group_id;
	temp.p_index = node_a->p_index;
	temp.option = node_a->option;
	temp.type = node_a->type;
	node_a->cmd = node_b->cmd;
	node_a->group_id = node_b->group_id;
	node_a->p_index = node_b->p_index;
	node_a->option = node_b->option;
	node_a->type = node_b->type;
	node_b->cmd = temp.cmd;
	node_b->group_id = temp.group_id;
	node_b->p_index = temp.p_index;
	node_b->option = temp.option;
	node_b->type = temp.type;
}

void	sort_pexe(t_msh *msh)
{
	t_pexe	*current;
	t_pexe	*next;
	int		loop;

	loop = 1;
	while (loop)
	{
		loop = 0;
		current = msh->pexe;
		while (current != NULL && current->next != NULL)
		{
			next = current->next;
			if (current->group_id > next->group_id || (current->group_id == \
				next->group_id && current->p_index > next->p_index))
			{
				swap(current, next);
				loop = 1;
			}
			current = current->next;
		}
	}
}

int	move_node(t_msh *msh)
{
	int	g;

	g = msh->pexe->group_id;
	if (msh->pexe->next != NULL \
			&& msh->pexe->next->group_id == g \
			&& msh->pexe->next->cmd != NULL)
	{
		msh->pexe = msh->pexe->next;
		return (1);
	}
	return (0);
}

void	move_group(t_msh *msh)
{
	int	g;

	g = msh->pexe->group_id;
	while (msh->pexe != NULL \
			&& msh->pexe->group_id == g \
			&& msh->pexe->cmd != NULL)
		msh->pexe = msh->pexe->next;
}
