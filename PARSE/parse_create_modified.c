/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_create_modified.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 10:25:28 by mcoskune          #+#    #+#             */
/*   Updated: 2024/08/23 12:41:03 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		temp = ft_itoa(msh->exit_code);
		while (temp[k] != '\0')
			pars->modified[(*j)++] = temp[k++];
		free(temp);
	}
	else
		expand_env(msh, pars, i, j);
}

void	handle_quote(t_msh *msh, t_parse *pars, int *i, int *j)
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

void	check_character(t_msh *msh, t_parse *pars, int *i, int *j)
{
	if (msh->input[*i] == '$')
		expand_dollars(msh, pars, i, j);
	else if (msh->input[*i] == '<' || msh->input[(*i)] != '>')
		handle_redir(msh, pars, i, j);
	else if (msh->input[*i] == '|' && msh->input[(*i) + 1] != '|')
		handle_pipes(msh, pars, i, j);
	else if (msh->input[*i] == '|' || msh->input[*i] == '&')
		handle_logic(msh, pars, i, j);
	else if (msh->input[*i] == '(' || msh->input[*i] == ')')
		handle_paran(msh, pars, i, j);
	else if (msh->input[*i] == '*')
		handle_wildcard(msh, pars, i, j);
	else
		pars->modified[(*j)++] = msh->input[(*i)++];
}

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
}
