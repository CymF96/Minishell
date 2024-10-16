/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 17:36:54 by mcoskune          #+#    #+#             */
/*   Updated: 2024/10/15 21:21:51 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*heredoc_name(t_msh *msh, int *num)
{
	char	*num_str;
	char	*temp_str;

	num_str = ft_itoa(*num);
	temp_str = ft_strjoin(".here_doc", num_str);
	free(num_str);
	num_str = ft_strjoin(temp_str, ".tmp");
	free(temp_str);
	copy_input_mod(msh, num_str, 0, ft_strlen(num_str));
	(*num)++;
	return (num_str);
}

static bool	remove_quote_helper(int *count, int *i, int *flag, char *str)
{
	if ((str[*i] == '\'' || str[*i] == '\"') && (*flag == 0))
	{
		*count = check_quote_ending(str, *i);
		(*i)++;
		*flag = 1;
		return (true);
	}
	if (*i == *count)
	{
		(*i)++;
		*count = -1;
		*flag = 0;
		return (true);
	}
	return (false);
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
		if (remove_quote_helper(&count, &i, &flag, str))
			continue ;
		if ((flag == 0) && (str[i] == ' ' || str[i] == '\t'))
			i++;
		else
			delim[j++] = str[i++];
	}
	delim[j] = '\0';
}

static void	heredoc_specials(t_msh *msh, int *i, int *flag)
{
	
	while (msh->input[*i] != ' ' && msh->input[*i] != '\t' && msh->input[*i] \
		!= '\0' && (check_special(msh->input, i) == REGULAR || \
		check_special(msh->input, i) == DOLLAR || check_special(msh->input, i) \
		== S_QT || check_special(msh->input, i) == D_QT))
	{
		if (msh->input[*i] == '\'' || msh->input[*i] == '\"')
		{
			*flag = 2;
			*i = check_quote_ending(msh->input, *i) + 1;
			continue ;
		}
		(*i)++;
	}
}

int	handle_heredoc(t_msh *msh, int *i)
{
	int		start;
	int		flag;
	char	*delim;

	flag = 1;
	(*i)++;
	while (msh->input[*i] == ' ' || msh->input[*i] == '\t')
		(*i)++;
	start = (*i);
	heredoc_specials(msh, i, &flag);
	delim = malloc(sizeof(char) * (*i - start + 1));
	remove_quotes(&msh->input[start], *i - start, delim);
	if (get_here_doc(msh, delim, flag) || msh->interrupted)
	{
		free (delim);
		return (1);
	}
	free(delim);
	(*i)--;
	return (0);
}
