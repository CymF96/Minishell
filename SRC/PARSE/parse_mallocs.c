/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_mallocs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofische <cofische@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 17:24:52 by mcoskune          #+#    #+#             */
/*   Updated: 2025/05/28 17:59:42 by cofische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"

void	wild_cleanup(t_parse *pars)
{
	int	i;

	i = 0;
	if (pars->w_pos != NULL)
	{
		while (i < pars->w_count && pars->w_pos[i] != NULL)
			free(pars->w_pos[i++]);
		free(pars->w_pos);
		pars->w_pos = NULL;
	}
	i = 0;
	if (pars->w_str != NULL)
	{
		while (i < pars->w_count && pars->w_str[i] != NULL)
			free(pars->w_str[i++]);
		free(pars->w_str);
		pars->w_str = NULL;
	}
}

void	wild_malloc(t_msh *msh, t_parse *pars)
{
	int	i;

	i = 0;
	pars->w_pos = malloc (sizeof(int *) * (pars->w_count + 1));
	pars->w_str = malloc (sizeof(char *) * (pars->w_count + 1));
	if (pars->w_pos == NULL || pars->w_str == NULL)
		wild_cleanup(pars);
	while (i < pars->w_count)
	{
		pars->w_pos[i] = malloc (sizeof(int));
		pars->w_str[i] = NULL;
		if (pars->w_pos[i] == NULL)
		{
			wild_cleanup(pars);
			exit_cleanup("Malloc failed", msh, errno, 2);
		}
		pars->w_pos[i][0] = -1;
		i++;
	}
	pars->w_pos[i] = NULL;
}

t_pexe	*pexe_malloc(t_msh *msh)
{
	t_pexe	*temp;

	temp = malloc(sizeof(t_pexe));
	if (temp == NULL)
		exit_cleanup("Malloc failed", msh, errno, 2);
	clean_init_pexe_node(temp);
	return (temp);
}

t_token	*token_malloc(t_msh *msh)
{
	t_token	*tkn;

	tkn = malloc(sizeof(t_token));
	if (tkn == NULL)
		exit_cleanup("Malloc failed", msh, errno, 2);
	clean_init_token_node(tkn);
	return (tkn);
}

void	parse_malloc(t_msh *msh)
{
	t_parse	*prs;

	prs = malloc(sizeof(t_parse));
	if (prs == NULL)
		exit_cleanup("Malloc failed", msh, errno, 2);
	clean_init_parse(prs);
	msh->parse = prs;
}
