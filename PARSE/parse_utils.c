/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:18:05 by mcoskune          #+#    #+#             */
/*   Updated: 2024/09/03 09:50:12 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	addnode(void *node, void **head, size_t offs_next, size_t offs_prev)
{
	void *current;

	current = *head;
	if (current == NULL)
	{
		*head = node;
		return ;
	}
	while (*(void **)((char *)current + offs_next) != NULL)
		current = *(void **)((char *)current + offs_next);
	*(void **)((char *)current + offs_next) = node;
	*(void **)((char *)node + offs_prev) = current;
	*(void **)((char *)node + offs_next) = NULL;
}

void	copy_input_mod(t_msh *msh, char *to_copy, int start, int end)
{
	char	*temp;
	char	*temp_free;

	if (to_copy == NULL)
		return ;
	temp = malloc (sizeof(char) * (end - start + 1));
	if (temp == NULL)
		exit_cleanup("Malloc Failed", msh, errno, 2);
	ft_strlcpy(temp, &to_copy[start], end - start + 1);
	temp_free = msh->parse->modified;
	msh->parse->modified = ft_strjoin(temp, to_copy);
	if (msh->parse->modified == NULL)
		exit_cleanup("Malloc Failed", msh, errno, 2);
	free (temp_free);
	free (temp);
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
	else if (check_if_qt(str, i) != REGULAR)
		return (check_if_qt(str, i));
	return (REGULAR);
}