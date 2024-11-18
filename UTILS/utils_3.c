/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofische <cofische@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 10:20:09 by coline            #+#    #+#             */
/*   Updated: 2024/11/18 13:01:29 by cofische         ###   ########.fr       */
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

void	heredoc_array(t_msh *msh, char *new_heredoc)
{
	int		i;
	int		hd_len;
	char	**temp_hd;

	hd_len = 0;
	while (msh->hd_array != NULL && msh->hd_array[hd_len] != NULL)
		hd_len++;
	temp_hd = malloc(sizeof(char *) * (hd_len + 2));
	if (temp_hd == NULL)
		exit_cleanup(NULL, msh, errno, 1);
	i = 0;
	while (i < hd_len)
	{
		temp_hd[i] = ft_strdup(msh->hd_array[i]);
		if (temp_hd[i] == NULL)
			exit_cleanup(NULL, msh, errno, 1);
		i++;
	}
	temp_hd[i] = ft_strdup(new_heredoc);
	if (temp_hd[i++] == NULL)
		exit_cleanup(NULL, msh, errno, 1);
	temp_hd[i] = NULL;
	free_mallocs(NULL, (void **)msh->hd_array);
	msh->hd_array = temp_hd;
}
