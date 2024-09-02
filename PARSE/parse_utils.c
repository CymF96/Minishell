/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:18:05 by mcoskune          #+#    #+#             */
/*   Updated: 2024/09/02 13:49:56 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*copy_input_modified(t_msh *msh, t_parse *pars, char *to_copy)
{
	char	*temp;

	if (to_copy == NULL)
		return ;
	temp = pars->modified;
	pars->modified = ft_strjoin(temp, to_copy);
	if (pars->modified == NULL)
		exit_cleanup("Malloc Failed", msh, errno, 2);
	free (temp);
	free (to_copy);
}


// Checks if quote has closing end. If none found, it's treated as char
int	check_quote_ending(char *input, int i)
{
	int		fl;
	int		j;

	fl = 0;
	if (input[i] == '\'')
		fl = 1;
	j = i + 1;
	while (input[j] != '\0')
	{
		if ((fl == 0 && input[j] == '\"') || (fl == 1 && input[j] == '\''))
		{
			return (j);
		}
		j++;
	}
	return (-1);
}

// t_type functions are there to find the type of given char. Split into 2
// to satisfy norminette
t_type	check_if_qt(char *str, int *i)
{
	if (str[*i] == '\'')
		return (S_QT);
	if (str[*i] == '\"')
		return (D_QT);
	return (REGULAR);
}

t_type	check_special(char *str, int *i)
{
	if (str[*i] == '$')
		return (DOLLAR);
	else if (str[*i] == '<' && str[(*i) + 1] == '<')
		return ((*i)++, HEREDOC);
	else if (str[*i] == '<' && str[(*i) + 1] != '<')
		return (INFILE);
	else if (str[*i] == '>' && str[(*i) + 1] != '>')
		return ((*i)++, APPEND);
	else if (str[*i] == '>' && str[(*i) + 1] != '>')
		return (OUTFILE);
	else if (str[*i] == '|' && str[(*i) + 1] != '|')
		return (PIPE);
	else if (str[*i] == '|' && str[(*i) + 1] == '|')
		return ((*i)++, OR);
	else if (str[*i] == '&' && str[(*i) + 1] == '&')
		return ((*i)++, AND);
	else if (str[*i] == '(')
		return (L_PAR);
	else if (str[*i] == ')')
		return (R_PAR);
	else if (str[*i] == '*')
		return (WILDCARD);
	if (check_if_qt(str, i) != REGULAR)
		return (check_if_qt(str, i));
	return (REGULAR);
}