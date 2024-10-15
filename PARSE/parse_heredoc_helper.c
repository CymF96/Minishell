/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_heredoc_helper.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 20:23:40 by mcoskune          #+#    #+#             */
/*   Updated: 2024/10/15 21:59:48 by mcoskune         ###   ########.fr       */
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
		{
			close(msh->parse->here_fd);
			return (1);
		}
		gnl = get_next_line(fd_temp, msh);
		if (gnl == NULL || (!ft_strncmp(gnl, delim, ft_strlen(delim)) && \
					ft_strlen(delim) == ft_strlen(gnl)))
		{
			if (gnl != NULL)
				free(gnl);
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
	char		*temp;
	static int	num = 0;

	gnl = NULL;
	temp = heredoc_name(msh, &num);
	msh->parse->here_fd = open(temp, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (msh->parse->here_fd == -1)
		exit_cleanup("Problem Encoured Opening Heredoc", msh, errno, 2);
	if (get_doc_helper(msh, gnl, delim, flag) != 0 && msh->interrupted == 0)
	{
		unlink(temp);
		free(temp);
		return (1);
	}
	if (gnl != NULL)
		free(gnl);
	if (!msh->interrupted)
		close(msh->parse->here_fd);
	if (temp != NULL)
		free(temp);
	return (0);
}
