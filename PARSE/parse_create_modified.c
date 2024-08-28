/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_create_modified.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 10:25:28 by mcoskune          #+#    #+#             */
/*   Updated: 2024/08/28 14:21:01 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Expanding $'s. Specifically checking if it is ? or a space/tab.
void	expand_dollars(t_msh *msh, t_parse *pars, int *i, int *j)
{
	int		k;
	char	*temp;

	k = 0;
	(*i)++;
	if (msh->input[*i] == ' ' || msh->input[*i] == '\t')
		pars->modified[(*j)++] = '$';
	else if (msh->input[*i] == '?')
	{
		temp = ft_itoa(msh->exit_error);
		while (temp[k] != '\0')
			pars->modified[(*j)++] = temp[k++];
		free(temp);
	}
	else
	{
		temp = expand_env(msh, i, j);
		while (temp != NULL && (temp[k] != '\n' || temp [k] != '\0'))
			pars->modified[(*j)++] = temp[k++];
	}
}

// If single quote, prints all as char. In double quote checks for $ and expands
static void	handle_quote(t_msh *msh, t_parse *pars, int *i, int *j)
{
	if (msh->input[(*i) - 1] == '\'')
	{
		while (msh->input[*i] != '\'' && msh->input[*i] != '\0')
			pars->modified[(*j)++] = msh->input[(*i)++];
	}
	if (msh->input[(*i) - 1] == '\"')
	{
		while (msh->input[*i] != '\"' && msh->input[*i] != '\0')
		{
			if (msh->input[*i] == '$')
				expand_dollars(msh, pars, i, j);
			else
				pars->modified[(*j)++] = msh->input[(*i)++];
		}
	}
	pars->modified[(*j)++] = msh->input[(*i)++];
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

// Checks for special characters and direct them to their own functions
static void	check_character(t_msh *msh, t_parse *pars, int *i, int *j)
{
	if (msh->input[*i] == '$')
		expand_dollars(msh, pars, i, j);
	else if (msh->input[*i] == '<' || msh->input[(*i)] == '>')
		handle_redir(msh, pars, i, j);
	else if (msh->input[*i] == '|' && msh->input[(*i) + 1] != '|')
		handle_pipes(msh, pars, i, j);
	else if (msh->input[*i] == '|' || msh->input[*i] == '&')
		handle_logic(msh, pars, i, j);
	else if (msh->input[*i] == '(' || msh->input[*i] == ')')
		handle_paran(msh, pars, i, j);
	else if (msh->input[*i] == '*')
		handle_wild_character(msh, pars, i, j);
	else
		pars->modified[(*j)++] = msh->input[(*i)++];
}

// Checks for $, ' and ". Otherwise just copy everything to modified char *
void	create_modified(t_msh *msh, t_parse *pars)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (msh->input[i] != '\0')
	{
		if (ft_isalnum(msh->input[i]) || msh->input[i] == ' ' || \
														msh->input == '\t')
			pars->modified[j++] = msh->input[i++];
		else if (msh->input[i] == '$')
			expand_dollars(msh, pars, &i, &j);
		else if (msh->input[i] == '\"' || msh->input[i] == '\'')
		{
			pars->modified[j++] = msh->input[i++];
			if (check_quote_ending(msh->input, i - 1) != -1)
				handle_quote(msh, pars, &i, &j);
		}
		else
			check_character(msh, pars, &i, &j);
	}
	pars->modified[j] = '\0';
}
