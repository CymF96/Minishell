/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 19:02:09 by mcoskune          #+#    #+#             */
/*   Updated: 2024/08/15 13:36:46 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_type(t_msh *msh, int i)
{
	if (msh->input[i] == ' ' || msh->input[i] == '\t')
		return (EMPTY);
	if (ft_isalpha(msh->input[i]))
		return (TEXT);
	if (ft_isdigit(msh->input[i]))
		return (NUM);
}

void	update_parsed_args(t_msh *msh, t_parse *pars)
{
	int	count;
	int	i;
	t_token	*temp;
	
	count = ft_lstsize((t_list *) pars->head);
	pars->parsed_args = malloc (sizeof(char *) * (count + 1));
	if (pars->parsed_args == NULL)
		exit_cleanup("Malloc Failed", msh, errno);
	i = 0;
	temp = pars->head;
	while (i < count)
	{
		pars->parsed_args[i] = temp->token;
		temp = temp->next;
		i++;
	}
	pars->parsed_args[i] = NULL;
	msh->parsed_args = pars->parsed_args;
}

void	parse_main(t_msh *msh)
{
	int		i;
	int		j;
	t_parse	*pars;
	t_token	*tkn;

	if (msh == NULL || msh->input == NULL || msh->input[0] == '\0')
		return ;
	i = 0;
	parse_structure_malloc(msh);
	while (msh->input[i] != '\0')
	{
		tkn = token_structure_malloc(msh);
		add_token_node(pars, tkn);
		tkn->start_pos = i;
		tkn->type = check_type(msh, i);
		while (msh->input[i] != '\0')
		{
			if (tkn->type != check_type(msh, i))
				break ;
			tkn->end_pos = i;
			i++;
		}
		make_token(msh, tkn);
		add_token_node(pars, tkn);
	}
	update_parsed_args(msh, pars);
}
