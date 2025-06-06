/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofische <cofische@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 11:37:28 by mcoskune          #+#    #+#             */
/*   Updated: 2025/05/28 18:00:21 by cofische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"

void	create_path(t_msh *msh, char *exe_cmd)
{
	if (!ft_strncmp("/bin/", msh->pexe->cmd, 5) \
		|| !ft_strncmp("/usr/bin/", msh->pexe->cmd, 9))
	{
		msh->path = ft_strdup(exe_cmd);
		if (access(msh->path, F_OK | X_OK) != 0)
		{
			free(msh->path);
			msh->path = NULL;
		}
	}
	else
		msh->path = find_executable_path(msh);
	if (!msh->path)
	{
		ft_printf("%s: ", exe_cmd);
		return ;
	}
	if (move_node(msh) && !ft_strncmp("cat", exe_cmd, 3))
	{
		if (access(msh->pexe->cmd, F_OK) != 0)
			msh->exit_error = errno;
		if (access(msh->pexe->cmd, X_OK) != 0)
			msh->exit_error = errno;
	}
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

char	**set_paths_envp(t_msh *msh)
{
	char	**paths;
	char	*path;

	path = get_path(msh->envp);
	if (path == NULL)
		return (NULL);
	paths = ft_split(path, ':');
	free(path);
	path = NULL;
	if (paths == NULL)
		exit_cleanup(NULL, msh, errno, 1);
	return (paths);
}

char	*find_executable_path(t_msh *msh)
{
	char	**paths;
	char	*path;
	char	*cmd_path;
	int		i;

	paths = set_paths_envp(msh);
	if (paths == NULL)
		return (NULL);
	i = -1;
	while (paths[++i])
	{
		cmd_path = ft_strjoin(paths[i], "/");
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
