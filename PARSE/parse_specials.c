/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_specials.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 15:52:10 by mcoskune          #+#    #+#             */
/*   Updated: 2024/09/02 18:18:17 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Marks point-of-interests in a separate list to avoid confusion between text
// and actual special symbols
static void	input_to_poi(t_msh *msh, t_parse *pars, int symbol)
{
	int	i;

	i = 0;
	while (pars->poi[i] != NULL)
		i++;
	pars->poi[i] = malloc(sizeof(int) * 4);
	if (pars->poi[i] == NULL)
		exit_cleanup ("Malloc failed", msh, errno, 2);
	pars->poi[i][0] = symbol;
	pars->poi[i][1] = ft_strlen(pars->modified);
	pars->poi[i][2] = -1;
	pars->poi[i][3] = -1;
}

void	handle_redir(t_msh *msh, t_parse *pars, int *i)
{
	if (msh->input[*i] == '<' && msh->input[*i + 1] != '<')
	{
		copy_input_mod(msh, "<", 0, 1);;
		input_to_poi(msh, pars, INFILE);
	}
	else if (msh->input[*i] == '<' && msh->input[*i + 1] == '<')
	{
		copy_input_mod(msh, "<", 0, 1);
		input_to_poi(msh, pars, HEREDOC);
		handle_heredoc(msh, i);
	}
	else if (msh->input[*i] == '>' && msh->input[*i + 1] != '>')
	{
		copy_input_mod(msh, ">", 0, 1);
		input_to_poi(msh, pars, OUTFILE);
	}
	else if (msh->input[*i] == '>' && msh->input[*i + 1] == '>')
	{
		copy_input_mod(msh, ">", 0, 1);
		input_to_poi(msh, pars, APPEND);
	}
}

void	handle_pipes(t_msh *msh, t_parse *pars, int *i)
{
	if (msh->input[*i] == '|' && msh->input[*i + 1] != '|')
	{
		copy_input_mod(msh, "|", 0, 1);
		input_to_poi(msh, pars, PIPE);
	}
	msh->pipe_nb++;
}

void	handle_logic(t_msh *msh, t_parse *pars, int *i)
{
	if (msh->input[*i] == '|' && msh->input[*i + 1] == '|')
	{
		copy_input_mod(msh, "|", 0, 1);
		input_to_poi(msh, pars, OR);
	}
}

void	handle_paran(t_msh *msh, t_parse *pars, int *i)
{
	if (msh->input[*i] == '(')
	{
		copy_input_mod(msh, "(", 0, 1);
		input_to_poi(msh, pars, L_PAR);
	}
	else if (msh->input[*i] == ')')
	{
		copy_input_mod(msh, ")", 0, 1);
		input_to_poi(msh, pars, R_PAR);
	}
}
