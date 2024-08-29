/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokenize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 18:17:56 by mcoskune          #+#    #+#             */
/*   Updated: 2024/08/26 17:32:52 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	copy_text(t_msh *msh, t_parse *pars, t_token *tkn)
{
	int	i;
	int	j;

	i = tkn->start_pos;
	j = 0;
	tkn->token = malloc(sizeof(tkn->end_pos - tkn->start_pos + 2));
	if (tkn->token == NULL)
		exit_cleanup("Malloc failed", msh, errno, 2); //verify which exist is better
	while (i <= tkn->end_pos)
	{
		tkn->token[j] = pars->modified[i];
		i++;
		j++;
	}
	tkn->token[j] = '\0';
}

void	quote_token(char *temp, int *i)
{
	if (check_quote_ending(temp, *i))
	{
		if (temp[*i] == '\'')
		{
			(*i)++;
			while (temp[*i] != '\'')
				(*i)++;
		}
		else if (temp[*i] == '\"')
		{
			(*i)++;
			while (temp[*i] != '\"')
				(*i)++;
		}
		(*i)++;
	}
	else
		(*i)++;
}

void	parse_tokenize(t_msh *msh, t_parse *prs)
{
	int		i;
	int		j;
	t_token	*tkn;
	char	*temp;

	i = 0;
	j = 0;
	temp = prs->modified;
	while (temp[i] != '\0')
	{
		tkn = token_malloc(msh); // prs parameters
		while (prs->modified[i] == ' ' || prs->modified[i] == '\t')
			i++;
		tkn->start_pos = i;
		while (temp[i] != '\0')
		{
			if (temp[i] == '\'' || temp[i] == '\"')
				quote_token(prs->modified, &i);
			if (i + 1 == prs->poi[j][1])
			{
				i++;
				break;
			}
			if (i == prs->poi[j][1])
			{
				tkn->type = prs->poi[j][0];
				i++;
				j++;
				break;
			}
			if (temp[i] == ' ' || temp[i] == '\t')
				break ;
			i++;
		}
		tkn->end_pos = i - 1;
		add_node((void **)&prs->head, (void *)tkn, \
			FIELD_OFFSET(t_token, next), FIELD_OFFSET(t_token, prev));
		copy_text(msh, prs, tkn);
	}
}
