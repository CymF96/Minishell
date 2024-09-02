/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_specials.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 15:52:10 by mcoskune          #+#    #+#             */
/*   Updated: 2024/08/30 16:47:25 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Marks point-of-interests in a separate list to avoid confusion between text
// and actual special symbols
static void	input_to_poi(t_msh *msh, t_parse *pars, int symbol, int j)
{
	int	i;
	int	k;

	i = 0;
	while (pars->poi[i] != NULL)
		i++;
	pars->poi[i] = malloc(sizeof(int) * 4);
	if (pars->poi[i] == NULL)
		exit_cleanup ("Malloc failed", msh, errno, 2);  //verify which exist is better
	pars->poi[i][0] = symbol;
	pars->poi[i][1] = j;
	pars->poi[i][2] = -1;
	pars->poi[i][3] = -1;
	while (symbol == L_PAR && i >= 0)
	{
		if (pars->poi[i][0] == L_PAR)
			pars->poi[i--][2] += 1;
	}
	k = i;
	while (symbol == R_PAR && i >= 0)
	{
		if (pars->poi[i--][0] == R_PAR)
			pars->poi[k][2] += 1;
	}
}

void	handle_redir(t_msh *msh, t_parse *pars, int *i, int *j)
{
	if (msh->input[*i] == '<' && msh->input[*i + 1] != '<')
	{
		pars->modified[(*j)++] = msh->input[(*i)++];
		input_to_poi(msh, pars, INFILE, (*j) - 1);
	}
	else if (msh->input[*i] == '<' && msh->input[*i + 1] == '<')
	{
		pars->modified[(*j)++] = msh->input[(*i)++];
		input_to_poi(msh, pars, HEREDOC, (*j) - 1);
		handle_heredoc(msh, pars, i , j);
	}
	else if (msh->input[*i] == '>' && msh->input[*i + 1] != '>')
	{
		pars->modified[(*j)++] = msh->input[(*i)++];
		input_to_poi(msh, pars, OUTFILE, (*j) - 1);
	}
	else if (msh->input[*i] == '>' && msh->input[*i + 1] == '>')
	{
		pars->modified[(*j)++] = msh->input[(*i)++];
		input_to_poi(msh, pars, APPEND, (*j) - 1);
	}
}

void	handle_pipes(t_msh *msh, t_parse *pars, int *i, int *j)
{
	if (msh->input[*i] == '|' && msh->input[*i + 1] != '|')
	{
		pars->modified[(*j)++] = msh->input[(*i)++];
		input_to_poi(msh, pars, PIPE, (*j) - 1);
	}
	msh->pipe_nb++;
}

void	handle_logic(t_msh *msh, t_parse *pars, int *i, int *j)
{
	if (msh->input[*i] == '|' && msh->input[*i + 1] == '|')
	{
		pars->modified[(*j)++] = msh->input[(*i)++];
		input_to_poi(msh, pars, OR, (*j) - 1);
	}
}

void	handle_paran(t_msh *msh, t_parse *pars, int *i, int *j)
{
	if (msh->input[*i] == '(')
	{
		pars->modified[(*j)++] = msh->input[(*i)++];
		input_to_poi(msh, pars, L_PAR, (*j) - 1);
	}
	else if (msh->input[*i] == ')')
	{
		pars->modified[(*j)++] = msh->input[(*i)++];
		input_to_poi(msh, pars, R_PAR, (*j) - 1);
	}
}
