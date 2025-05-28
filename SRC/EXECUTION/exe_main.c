/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofische <cofische@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:00:43 by cofische          #+#    #+#             */
/*   Updated: 2025/05/28 17:59:10 by cofische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"

void	command(t_msh *msh, char *cmd)
{
	if (ft_strlen(cmd) == 4 && !ft_strncmp("echo", cmd, 4))
		cmd_echo(msh);
	else if (ft_strlen(cmd) == 2 && !ft_strncmp("cd", cmd, 2))
		cmd_cd(msh);
	else if (ft_strlen(cmd) == 3 && !ft_strncmp("pwd", cmd, 3))
		cmd_pwd(msh);
	else if (ft_strlen(cmd) == 6 && !ft_strncmp("export", cmd, 6))
		cmd_export(msh);
	else if (ft_strlen(cmd) == 5 && !ft_strncmp("unset", cmd, 5))
		cmd_unset(msh);
	else if (ft_strlen(cmd) == 3 && !ft_strncmp("env", cmd, 3))
		cmd_env(msh);
	else
		exe(msh);
	if (msh->child)
		exit_cleanup(NULL, msh, 0, 1);
}

void	check_type(t_msh *msh)
{
	if (msh->pipe_nb > 0)
	{
		msh->child = 1;
		ft_pipex(msh);
	}
	else if (msh->pexe->type == EXE)
		command(msh, msh->pexe->cmd);
	else if (msh->pexe->type == INFILE)
		red_left(msh);
	else if (msh->pexe->type == OUTFILE)
		red_right(msh);
	else if (msh->pexe->type == APPEND)
		double_red_right(msh);
}

void	check_file_exit(t_msh *msh)
{
	if (access(msh->pexe->cmd, F_OK | X_OK) != 0)
		exit_cleanup("No such file or directory", msh, errno, 0);
}

void	execution(t_msh *msh)
{
	if (msh->pexe == NULL || (!ft_strncmp("", msh->pexe->cmd, 2)))
	{
		exit_cleanup(NULL, msh, errno, 0);
		return ;
	}
	if (ft_strlen(msh->pexe->cmd) == 4 \
			&& !ft_strncmp("exit", msh->pexe->cmd, 4))
	{
		exit_cleanup(NULL, msh, 0, 1);
		return ;
	}
	if (msh->pexe->type != EXE && msh->pexe->next == NULL)
	{
		check_file_exit(msh);
		return ;
	}
	if (sort_pexe(msh))
		return ;
	check_type(msh);
}
