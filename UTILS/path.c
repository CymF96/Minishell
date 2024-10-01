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
	int		i;

	i = 0;
	path = get_path(msh->envp);
	if (path == NULL)
		return (NULL);
	paths = ft_split(path, ':');
	if (paths == NULL)
		exit_cleanup(NULL, msh, errno, 1);
	free(path);
	while (paths[i])
	{
		path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(path, msh->pexe->cmd);

		if (access(path, F_OK | X_OK) == 0)
		{
			free_mallocs(NULL, (void **)paths);
			return (path);
		}
		free(path);
		i++;
	}
	free_mallocs(NULL, (void **)paths);
	exit_cleanup("Invalid path or command", msh, errno, 0);
	return (NULL);
}
