/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_heredoc_helper.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofische <cofische@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 20:23:40 by mcoskune          #+#    #+#             */
/*   Updated: 2024/11/18 13:00:26 by cofische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_for_here_dollar(t_msh *msh, char *gnl, int fd_temp, int flag)
{
	int		i;
	char	*temp;

	i = 0;
	if (flag == 1)
	{
		while (gnl[i] != '\0')
		{
			if (gnl[i] != '$')
				ft_putchar_fd(gnl[i], fd_temp);
			else
			{
				i++;
				msh->parse->temp = gnl;
				temp = expand_env(msh, &i, 1);
				i--;
				ft_putstr_fd(temp, fd_temp);
				free(temp);
			}
			i++;
		}
	}
	else if (flag == 2)
		ft_putstr_fd(gnl, fd_temp);
}

static int	get_doc_helper(t_msh *msh, char *gnl, char *delim, int flag)
{
	int			fd_temp;

	fd_temp = STDIN_FILENO;
	while (1)
	{
		write(1, ">", 1);
		if (msh->interrupted)
			return (1);
		gnl = get_next_line(fd_temp, msh);
		if (gnl == NULL && msh->interrupted != 1)
		{
			printf("warning: heredoc at line 1 delimited by EOF (%s)\n", delim);
			break ;
		}
		if (gnl == NULL || (!ft_strncmp(gnl, delim, ft_strlen(delim)) && \
					ft_strlen(delim) == ft_strlen(gnl)))
		{
			free_mallocs(gnl, NULL);
			break ;
		}
		else
			check_for_here_dollar(msh, gnl, msh->parse->here_fd, flag);
		free(gnl);
	}
	return (0);
}

int	get_here_doc(t_msh *msh, char *delim, int flag)
{
	char		*gnl;
	static int	num = 0;

	gnl = NULL;
	msh->hd_temp = heredoc_name(msh, &num);
	heredoc_array(msh, msh->hd_temp);
	msh->parse->here_fd = open(msh->hd_temp, \
		O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (msh->parse->here_fd == -1)
		exit_cleanup("Problem Encoured Opening Heredoc", msh, errno, 2);
	if (get_doc_helper(msh, gnl, delim, flag) != 0 && msh->interrupted == 0)
		return (1);
	if (gnl != NULL)
		free(gnl);
	if (!msh->interrupted && msh->parse->here_fd != -1)
		close(msh->parse->here_fd);
	if (msh->hd_temp != NULL)
	{
		free(msh->hd_temp);
		msh->hd_temp = NULL;
	}
	msh->hr_flag = 1;
	return (0);
}

int	request_more_input(t_msh *msh, t_parse *pars)
{
	char	*temp;

	clean_init_parse(pars);
	write (1, "> ", 2);
	temp = get_next_line(STDIN_FILENO, msh);
	if (msh->interrupted || temp == NULL)
	{
		while (temp != NULL)
		{
			free(temp);
			temp = get_next_line(STDIN_FILENO, msh);
		}
		temp = NULL;
		if (msh->input != NULL)
			free(msh->input);
		msh->input = NULL;
		return (1);
	}
	if (request_more_input_cont(msh, temp) != 0)
		return (1);
	return (0);
}
