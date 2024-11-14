/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_executable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofische <cofische@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:00:00 by cofische          #+#    #+#             */
/*   Updated: 2024/11/14 09:37:47 by cofische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	check_wc(t_msh *msh, t_pexe *head)
{
	t_pexe	*current;
	t_pexe	*next;

	current = head;
	next = head->next;
	if (next != NULL)
	{
		if (!ft_strncmp("wc", current->cmd, 2) && next->type == HEREDOC)
			swap(current, next);
		if (next->next != NULL && next->next->type == HEREDOC)
		{
			swap(next, next->next);
			swap(current, next);
		}
	}
	msh->pexe = head;
	if (head->type == HEREDOC)
	{
		red_left(msh);
		return (1);
	}
	return (0);
}

void	clean_child(t_msh *msh)
{
	int	status;

	status = 0;
	waitpid(msh->chds[0]->pid, &status, 0);
	if (msh->chds != NULL)
	{
		free_pipex(msh);
		msh->chds = NULL;
		exit_cleanup(NULL, msh, 0, 0);
	}
	exit_cleanup(NULL, msh, msh->exit_error, 0);
}

void	pipe_exe(t_msh *msh, t_pexe *head)
{
	msh->chds = malloc(sizeof(t_pipex));
	msh->chds[0] = (t_pipex *)malloc(sizeof(t_pipex));
	clean_init_chds(msh->chds[0]);
	msh->chds[0]->pid = fork();
	if (msh->chds[0]->pid < 0)
		exit_cleanup(NULL, msh, errno, 0);
	if (msh->chds[0]->pid == 0)
	{
		if (execve(msh->path, head->option, msh->envp) == -1)
			exit(EXIT_FAILURE);
	}
	else
		clean_child(msh);
}

void	exe(t_msh *msh)
{
	int		len_group;
	t_pexe	*head;

	head = msh->pexe;
	len_group = node_strlen(msh->pexe);
	if (check_wc(msh, head))
		return ;
	create_path(msh, head->cmd);
	if (msh->path == NULL)
	{
		exit_cleanup("Command not found", msh, 127, 0);
		return ;
	}
	if (msh->path != NULL)
	{
		append_args(msh, head, len_group);
		if (msh->child)
		{
			if (execve(msh->path, head->option, msh->envp) == -1)
				exit_cleanup(NULL, msh, errno, 0);
		}
		else
			pipe_exe(msh, head);
	}
}
