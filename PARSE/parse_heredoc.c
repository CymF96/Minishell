/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 17:36:54 by mcoskune          #+#    #+#             */
/*   Updated: 2024/10/01 13:06:52 by mcoskune         ###   ########.fr       */
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
				ft_putstr_fd(temp, fd_temp);
				ft_putchar_fd('\n', fd_temp);
				free(temp);
			}
			i++;
		}
	}
	else if (flag == 2)
		ft_putstr_fd(gnl, fd_temp);
}

void	get_here_doc(t_msh *msh, char *delim, int flag)
{
	char		*gnl;
	char		*temp;
	static int	num = 0;
	int			fd_temp;
	
	fd_temp = STDIN_FILENO;
	temp = ft_itoa(num);
	gnl = ft_strjoin(".here_doc", temp);
	free(temp);
	temp = ft_strjoin(gnl, ".tmp");
	free(gnl);
	copy_input_mod(msh, temp, 0, ft_strlen(temp));
	msh->parse->here_fd = open(temp, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	free(temp);
	if (msh->parse->here_fd == -1)
		exit_cleanup("fd problem", msh, errno, 2);
	while (1)
	{
		gnl = get_next_line(fd_temp);
		if (gnl == NULL || (!ft_strncmp(gnl, delim, ft_strlen(delim)) && \
					ft_strlen(delim) == ft_strlen(gnl)))
			break ;
		else
			check_for_here_dollar(msh, gnl, msh->parse->here_fd, flag);
		free(gnl);
	}
	if (gnl != NULL)
		free(gnl);
	close(msh->parse->here_fd);
	num++;
}

void	remove_quotes(char *str, int len, char *delim)
{
	int		i;
	int		j;
	int		flag;
	int		count;

	i = 0;
	j = 0;
	flag = 0;
	count = -1;
	while ((str[i] != '\0' && i < len) || (str[i] != '\0' && len < 0))
	{
		if ((str[i] == '\'' || str[i] == '\"') && (flag == 0))
		{
			count = check_quote_ending(str, i);
			i++;
			flag = 1;
			continue ;
		}
		if (i == count)
		{
			i++;
			count = -1;
			flag = 0;
			continue ;
		}
		if ((flag == 0) && (str[i] == ' ' || str[i] == '\t'))
			i++;
		else
			delim[j++] = str[i++];
	}
	delim[j] = '\0';
}

void	handle_heredoc(t_msh *msh, int *i)
{
	int		start;
	int		flag;
	char	*delim;

	flag = 1;
	(*i)++;
	while (msh->input[*i] == ' ' || msh->input[*i] == '\t')
		(*i)++;
	start = (*i);
	while (msh->input[*i] != ' ' && msh->input[*i] != '\t' && msh->input[*i] \
		!= '\0' && (check_special(msh->input, i) == REGULAR || \
		check_special(msh->input, i) == DOLLAR || check_special(msh->input, i) \
		== S_QT || check_special(msh->input, i) == D_QT))
	{
		if (msh->input[*i] == '\'' || msh->input[*i] == '\"')
		{
			flag = 2;
			*i = check_quote_ending(msh->input, *i) + 1;
			continue ;
		}
		(*i)++;
	}
	delim = malloc(sizeof(char) * (*i - start + 1));
	remove_quotes(&msh->input[start], *i - start, delim);
	get_here_doc(msh, delim, flag);
	free (delim);
	(*i)--;
}
