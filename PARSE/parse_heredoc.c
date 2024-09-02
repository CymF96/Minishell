/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 17:36:54 by mcoskune          #+#    #+#             */
/*   Updated: 2024/09/02 17:48:56 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_for_here_dollar(t_msh *msh, char *gnl, int fd_temp, int flag)
{
	int		i;
	char	*temp;

	i = 0;
	if (flag == 0)
	{
		while (gnl[i] != '\n' || gnl[i] != '\0')
		{
			if (gnl[i] == '$')
			{
				temp = expand_env(msh, &i);
				ft_putstr_fd(temp, fd_temp);
				free (temp);
			}
		}
	}
	else
		ft_putstr_fd(gnl, fd_temp);
}

char	*remove_quotes(char *str, int len)
{
	int		i;
	int		count;
	char	*temp;

	i = 0;
	count = 0;
	while (str[i] != '\0' && i < len)
	{
		if (check_quote_ending(str, i) != -1)
		{
			i = check_quote_ending(&str[i], i) + 1;
			continue ;
		}
		count++;
	}
	temp = malloc (sizeof(char) * (count + 1));
	if (temp == NULL)
		return (NULL);
	i = 0;
	while (str[i] != '\0' && i <= count)
	{
		if ((str[i] != '\"' && str[i] != '\'') || check_quote_ending(&str[i], i) == -1)
			temp[i] = str[i];
		i++;
	}
	temp[i] = '\0';
	return (temp);
}

void	get_here_doc(t_msh *msh, char *delim, int flag)
{
	int		fd_temp;
	int		fd_stdin;
	char	*gnl;

	fd_temp = 0; //initialise the variable with 0
	msh->parse->here_fd = open(".here_doc.tmp", O_CREAT | O_WRONLY | \
															O_TRUNC, 0644);
	fd_stdin = dup(STDIN_FILENO);
	if (fd_temp == -1)
		exit_cleanup("fd problem", msh, errno, 2); //verify which exist is better
	while (1)
	{
		gnl = get_next_line(fd_stdin);
		if (ft_strlen(delim) + 1 == ft_strlen(gnl)
			&& !ft_strncmp(gnl, delim, ft_strlen(delim + 1)))
		{
			close(fd_stdin);
			break ;
		}
		else
			check_for_here_dollar(msh, gnl, fd_temp, flag);
		free(gnl);
	}
}


void	handle_heredoc(t_msh *msh, int *i)
{
	int		start;
	int		flag;
	char	*delim;

	flag = 0;
	while (msh->input[*i] == ' ' || msh->input[*i] == '\t')
		(*i)++;
	start = ++(*i);
	while (msh->input[*i] != ' ' || msh->input[*i] != '\t')
	{
		if (msh->input[*i] == '\'' || msh->input[*i] == '\"')
		{
			if (check_quote_ending(&msh->input[*i], *i) != -1)
			{
				flag = 1;
				*i = check_quote_ending(&msh->input[*i], *i) + 1;
			}
		}
	}
	delim = remove_quotes(&msh->input[start], *i - start + 1);
	get_here_doc(msh, delim, flag);
	free (delim);
}