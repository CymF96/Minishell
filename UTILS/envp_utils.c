/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 11:37:28 by mcoskune          #+#    #+#             */
/*   Updated: 2024/10/03 11:45:25 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_envp(t_msh *msh)
{
	int	i;

	i = 0;
	if (msh->envp != NULL)
	{
		while (msh->envp[i] != NULL)
			free(msh->envp[i++]);
		free(msh->envp);
	}
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

char	*get_path(char **envp)
{
	char	*path;
	int		i;
	char	*equal_sign;

	i = 0;
	path = NULL;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
		{
			equal_sign = ft_strchr(envp[i], '=');
			if (equal_sign)
				path = ft_strdup(equal_sign + 1);
			break ;
		}
		i++;
	}
	return (path);
}

char	*find_executable_path(t_msh *msh)
{
	char	**paths;
	char	*path;
	char	*cmd_path;
	int		i;

	path = get_path(msh->envp);
	if (path == NULL)
	{
		exit_cleanup("Path or Command not found", msh, 127, 0);
		return (NULL);
	}
	paths = ft_split(path, ':');
	free(path);
	path = NULL;
	if (paths == NULL)
		exit_cleanup(NULL, msh, errno, 1);
	i = -1;
	while (paths[++i])
	{
		cmd_path = ft_strjoin(paths[i], "/");
		if (cmd_path == NULL)
			free_mallocs(NULL, (void **)paths);
		path = ft_strjoin(cmd_path, msh->pexe->cmd);
		free(cmd_path);
		if (path == NULL)
			free_mallocs(NULL, (void **)paths);
		if (access(path, F_OK | X_OK) == 0)
		{
			free_mallocs(NULL, (void **)paths);
			return (path);
		}
		free(path);
	}
	free_mallocs(NULL, (void **)paths);
	return (NULL);
}

char	*set_var_name(char *cmd)
{
	int		i;
	char	*var_name;

	i = 0;
	while (cmd[i] && cmd[i] != '=')
		i++;
	var_name = malloc(i + 1);
	i = 0;
	while (cmd[i] && cmd[i] != '=')
	{
		var_name[i] = cmd[i];
		i++;
	}
	var_name[i] = '\0';
	return (var_name);
}
