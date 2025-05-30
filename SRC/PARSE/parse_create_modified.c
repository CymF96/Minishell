/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_create_modified.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofische <cofische@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 10:25:28 by mcoskune          #+#    #+#             */
/*   Updated: 2025/05/28 17:59:22 by cofische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"

int	handle_dquote(t_msh *msh, int *i, int *start, int *flag)
{
	while (msh->input[*i] != '\"' && msh->input[*i] != '\0')
	{
		while (msh->input[(*i)] != '\"' && msh->input[(*i)] != '\0')
		{
			if (msh->input[*i] == '$')
			{
				copy_input_mod(msh, &msh->input[*start], *start, (*i) - 1);
				*flag = 1;
				break ;
			}
			(*i)++;
		}
		if (*flag == 0)
			copy_input_mod(msh, &msh->input[*start], *start, (*i));
		if (msh->input[(*i)] == '$')
		{
			if (expand_dollars(msh, i) == 1)
				return (1);
			if (msh->input[*i] == '\"')
				copy_input_mod(msh, "\"", 0, 1);
			*flag = 0;
		}
		*start = (*i);
	}
	return (0);
}

// Checks for special characters and direct them to their own functions
static int	check_character(t_msh *msh, t_parse *pars, int *i, t_type type)
{
	if (type == HEREDOC || type == INFILE || type == APPEND || type == OUTFILE)
	{
		if (handle_redir(msh, pars, i, type) == 1)
			return (1);
	}
	else if (type == PIPE)
		handle_pipes(msh, pars, type);
	if (type != DOLLAR)
		(*i)++;
	return (0);
}

static int	modified_helper(t_msh *msh, t_type type, int *i, int *start)
{
	if (dollar_expansion(msh, i, type))
		return (1);
	else if (type == S_QT || type == D_QT)
	{
		if (handle_quote(msh, i) == 1)
			return (1);
	}
	else if (type == REGULAR)
	{
		*start = *i;
		while (msh->input[*i] != '\0' && \
				check_special(msh->input, i) == REGULAR)
			(*i)++;
		copy_input_mod(msh, &msh->input[*start], *start, *i - 1);
	}
	else
	{
		if (check_character(msh, msh->parse, i, type) == 1)
			return (1);
	}
	return (0);
}

// Checks for $, ' and ". Otherwise just copy everything to modified char *
int	input_to_modified(t_msh *msh)
{
	int		start;
	int		i;
	t_type	type;

	start = 0;
	i = 0;
	while (msh->input != NULL && i < (int)ft_strlen(msh->input) \
			&& msh->input[i] != '\0')
	{
		type = check_special(msh->input, &i);
		if (modified_helper(msh, type, &i, &start) == 1)
			return (1);
	}
	return (0);
}

// Main function to create the modified string
int	create_modified(t_msh *msh, t_parse *pars)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (msh->input[i] != '\0')
	{
		if (check_special(msh->input, &i) != REGULAR)
			j++;
		i++;
	}
	pars->poi = malloc(sizeof(int *) * (j + 2));
	if (pars->poi == NULL)
		exit_cleanup("Malloc failed", msh, errno, 2);
	i = 0;
	while (i <= j)
		pars->poi[i++] = NULL;
	pars->size_modified = 0;
	pars->modified = malloc (sizeof(char) * (pars->size_modified + 1));
	if (pars->modified == NULL)
		exit_cleanup ("Malloc failed", msh, errno, 2);
	pars->modified[pars->size_modified] = '\0';
	if (input_to_modified(msh) == 1)
		return (1);
	return (0);
}
