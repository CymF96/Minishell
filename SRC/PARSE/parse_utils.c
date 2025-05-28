/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofische <cofische@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:18:05 by mcoskune          #+#    #+#             */
/*   Updated: 2025/05/28 18:00:03 by cofische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"

void	addnode(void *node, void **head, size_t offs_next, size_t offs_prev)
{
	void	*current;

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
	temp = malloc (sizeof(char) * (end - start + 2));
	if (temp == NULL)
		exit_cleanup("Malloc failed", msh, errno, 2);
	ft_strlcpy(temp, to_copy, end - start + 2);
	temp_free = msh->parse->modified;
	msh->parse->modified = ft_strjoin(msh->parse->modified, temp);
	if (msh->parse->modified == NULL)
	{
		free (temp_free);
		free (temp);
		exit_cleanup("Malloc failed", msh, errno, 2);
	}
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
		return (HEREDOC);
	else if (str[*i] == '<' && str[(*i) + 1] != '<')
		return (INFILE);
	else if (str[*i] == '>' && str[(*i) + 1] != '>')
		return (OUTFILE);
	else if (str[*i] == '>' && str[(*i) + 1] == '>')
		return (APPEND);
	else if (str[*i] == '|' && str[(*i) + 1] != '|')
		return (PIPE);
	else
		return (check_if_qt(str, i));
}
