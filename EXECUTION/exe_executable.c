#include "../minishell.h"

void	append_args(t_msh *msh, t_pexe *head, int len_group)
{
	int		i;
	char	**temp_option;

	msh->pexe = head;
	temp_option = malloc(sizeof(char *) * (len_group + 1));
	if (temp_option == NULL)
		exit_cleanup(NULL, msh, errno, 2);
	temp_option[0] = ft_strdup(head->cmd);
	i = 1;
	while (move_node(msh))
	{
		temp_option[i++] = ft_strdup(msh->pexe->cmd);
		if (temp_option == NULL)
			exit_cleanup(NULL, msh, errno, 2);
	}
	temp_option[i] = NULL;
	head->option = temp_option;
}

void	check_wc(t_msh *msh, t_pexe *head)
{
	t_pexe	*current;
	t_pexe	*next;

	current = head;
	next = head->next;
	if (next != NULL && next->type == HEREDOC)
	{
		swap(current, next);
		if (next->next != NULL && next->next->type == HEREDOC)
		{
			swap(next, next->next);
			swap(current, next);
		}
	}
	msh->pexe = head;
	ft_printf("%s\n", head->cmd);
	if (head->type == HEREDOC)
		red_left(msh);
}

void	pipe_exe(t_msh *msh, t_pexe *head)
{
	int	status;

	msh->chds[0] = (t_pipex *)malloc(sizeof(t_pipex));
	clean_init_chds(msh->chds[0]);
	msh->chds[0]->pid = fork();
	if (msh->chds[0]->pid < 0)
		exit_cleanup(NULL, msh, errno, 0);
	if (msh->chds[0]->pid == 0)
	{
		if (execve(msh->path, head->option, NULL) == -1)
		{
			exit_cleanup("execve failed to execute", msh, errno, 0);
			return ;
		}
	}
	else
	{
		waitpid(msh->chds[0]->pid, &status, 0);
		if (WIFSIGNALED(status))
			exit_cleanup(NULL, msh, errno, 0);
	}
}

void	exe(t_msh *msh)
{
	int		len_group;
	t_pexe	*head;

	head = msh->pexe;
	len_group = node_strlen(msh->pexe);
	create_path(msh, head->cmd);
	if (msh->path == NULL)
	{
		exit_cleanup("Command not found", msh, 127, 0);
		return ;
	}
	msh->chds = malloc(sizeof(t_pipex));
	if (msh->path != NULL)
	{
		append_args(msh, head, len_group);
		if (msh->child)
		{
			if (execve(msh->path, head->option, NULL) == -1)
				exit_cleanup(NULL, msh, errno, 0);
		}
		else
		{
			check_wc(msh, head);
			pipe_exe(msh, head);
		}
		exit_cleanup(NULL, msh, 0, 0);
	}
}
