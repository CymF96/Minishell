/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:01:50 by mcoskune          #+#    #+#             */
/*   Updated: 2024/08/23 12:40:26 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_here_doc(t_msh *msh, char *delim)
{
	int		fd_temp;
	int		fd_stdin;
	char	*gnl;

	msh->parse->here_fd = open(".here_doc.tmp", O_CREAT | O_WRONLY | \
															O_TRUNC, 0644);
	fd_stdin = dup(STDIN_FILENO);
	if (fd_temp == -1)
		exit_cleanup("fd problem", msh, errno);
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
			ft_putstr_fd(gnl, fd_temp);
		free(gnl);
	}
}

// void	check_heredoc(t_msh *msh, t_parse *pars)
// {
// 	int		i;
// 	int		j;
// 	char	*delim;
// 	int		count;

// 	i = 0;
// 	count = 0;
// 	while (msh->input[i] != '\0')
// 	{
// 		if (msh->input[i] == '<' && msh->input[i + 1] == '<')
// 		{
// 			i +=2;
// 			while (msh->input[i] == ' ')
// 				i++;
// 			j = i;
// 			while (msh->input[i] != ' ' && msh->input[i] != '\t')
// 			{
// 				i++;
// 				if (msh->input[i] == '\'')
// 					count +=5;
// 				else if (msh->input == '\"')
// 					count++;
// 			}
// 			delim = malloc (sizeof(char) * (i - j + 2));
// 			ft_strlcpy(delim, msh->input + j, i - j + 1);
// 			get_here_doc(msh, delim);
// 			free (delim);
// 		}
// 		i++;
// 	}
// }


int	parse_main(t_msh *msh)
{
	t_parse	*pars;
	
	if (msh == NULL || msh->input == NULL || msh->input[0] == '\0')
		return (1);
	parse_malloc(msh, pars);
	create_modified(msh, pars);


	
	expand_dollars(msh, pars, 1);
	parse_tokenize(msh, pars);
	
	
	
	return (0);
}
