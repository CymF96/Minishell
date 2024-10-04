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

char	*get_path(char **envp)
{
	char	*path;
	int		i;
	int		j;

	i = 0;
	j = 0;
	path = NULL;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH", ft_strlen("PATH")))
		{
			while (envp[i][j] && envp[i][j - 1] != '=')
				j++;
			path = ft_strdup(envp[i] + j);
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
		return (NULL);
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
	exit_cleanup("Invalid path or command", msh, errno, 0);
	return (NULL);
}


// char	*find_executable_path(t_msh *msh)
// {
// 	char	**paths;
// 	char	*path;
// 	int		i;

// 	i = -1;
// 	path = get_path(msh->envp);
// 	if (path == NULL)
// 		return (NULL);
// 	paths = ft_split(path, ':');
// 	if (paths == NULL)
// 		exit_cleanup(NULL, msh, errno, 1);
// 	free(path);
// 	while (paths[++i])
// 	{
// 		path = ft_strjoin(paths[i], "/");
// 		path = ft_strjoin(path, msh->pexe->cmd);
// 		if (access(path, F_OK | X_OK) == 0)
// 			return (free_mallocs(NULL, (void **)paths), path);
// 		free(path);
// 	}
// 	free_mallocs(NULL, (void **)paths);
// 	exit_cleanup("Invalid path or command", msh, errno, 0);
// 	return (NULL);
// }

char	*set_var_name(char *cmd)
{
	int		i;
	char	*var_name;

	i = 0;
	while (cmd[i] && cmd[i] != '=')
		i++;
	var_name = malloc(sizeof(i + 1));
	i = 0;
	while (cmd[i] != '\0' && cmd[i] != '=')
	{
		var_name[i] = cmd[i];
		i++;
	}
	var_name[i] = '\0';
	return (var_name);
}
