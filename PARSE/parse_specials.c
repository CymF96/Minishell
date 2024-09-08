/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_specials.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 15:52:10 by mcoskune          #+#    #+#             */
/*   Updated: 2024/09/08 16:40:38 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Marks point-of-interests in a separate list to avoid confusion between text
// and actual special symbols
static void	input_to_poi(t_msh *msh, t_parse *pars, t_type symbol)
{
	int	i;

	i = 0;
	while (pars->poi[i] != NULL)
		i++;
	pars->poi[i] = malloc(sizeof(int) * 2);
	if (pars->poi[i] == NULL)
		exit_cleanup ("Malloc failed", msh, errno, 2);
	pars->poi[i][0] = symbol;
	pars->poi[i][1] = ft_strlen(pars->modified) - 1;
}

void	handle_redir(t_msh *msh, t_parse *pars, int *i, t_type type)
{
	if (type == INFILE)
	{
		copy_input_mod(msh, "<", 0, 1);
		input_to_poi(msh, pars, INFILE);
	}
	else if (type == HEREDOC)
	{
		copy_input_mod(msh, "<", 0, 2);
		input_to_poi(msh, pars, HEREDOC);
		(*i) += 1;
		handle_heredoc(msh, i);
	}
	else if (type == OUTFILE)
	{
		copy_input_mod(msh, ">", 0, 1);
		input_to_poi(msh, pars, OUTFILE);
	}
	else if (type == APPEND)
	{
		copy_input_mod(msh, ">", 0, 1);
		input_to_poi(msh, pars, APPEND);
		(*i) += 1;
	}
}

void	handle_pipes(t_msh *msh, t_parse *pars, t_type type)
{
	if (type == PIPE)
	{
		copy_input_mod(msh, "|", 0, 1);
		input_to_poi(msh, pars, PIPE);
	}
	msh->pipe_nb++;
}

void	handle_logic(t_msh *msh, t_parse *pars, int *i, t_type type)
{
	if (type == OR)
	{
		copy_input_mod(msh, "|", 0, 1);
		input_to_poi(msh, pars, OR);
		(*i) += 1;
	}
	else if (type == AND)
	{
		copy_input_mod(msh, "&", 0, 1);
		input_to_poi(msh, pars, AND);
		(*i) += 1;
	}
}

void	handle_paran(t_msh *msh, t_parse *pars, t_type type)
{
	if (type == L_PAR)
	{
		copy_input_mod(msh, "(", 0, 1);
		input_to_poi(msh, pars, L_PAR);
	}
	else if (type == R_PAR)
	{
		copy_input_mod(msh, ")", 0, 1);
		input_to_poi(msh, pars, R_PAR);
	}
}
