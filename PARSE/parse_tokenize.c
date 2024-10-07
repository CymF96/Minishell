/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokenize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 18:17:56 by mcoskune          #+#    #+#             */
/*   Updated: 2024/10/07 15:49:25 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	copy_text(t_msh *msh, t_parse *pars, t_token *tkn)
{
	int		i;
	int		j;
	char	*temp;

	i = tkn->start_pos;
	j = 0;
	temp = malloc(sizeof(char) * (tkn->end_pos - tkn->start_pos + 2));
	if (temp == NULL)
		exit_cleanup("Malloc failed", msh, errno, 2);
	while (i <= tkn->end_pos)
		temp[j++] = pars->modified[i++];
	temp[j] = '\0';
	tkn->token = malloc(sizeof(char) * (ft_strlen(temp) + 1));
	if (tkn->token == NULL)
		exit_cleanup("Malloc Failed", msh, errno, 2);
	remove_quotes(temp, ft_strlen(temp), tkn->token);
	free(temp);
}

void	quote_token(char *temp, int *i)
{
	if (check_quote_ending(temp, *i))
	{
		if (temp[*i] == '\'')
		{
			(*i)++;
			while (temp[*i] != '\'' && temp[*i] != '\0')
				(*i)++;
		}
		else if (temp[*i] == '\"')
		{
			(*i)++;
			while (temp[*i] != '\"' && temp[*i] != '\0')
				(*i)++;
		}
	}
	else
		(*i)++;
}

static void	token_end(t_parse *prs, int *i, int *j, t_token *tkn)
{
	char	*temp;

	temp = prs->modified;
	while (temp[*i] != '\0')
	{
		if (temp[*i] == '\'' || temp[*i] == '\"')
			quote_token(prs->modified, i);
		if (prs->poi[*j] != NULL && *i + 1 == prs->poi[*j][1])
		{
			(*i)++;
			break ;
		}
		if (prs->poi[*j] != NULL && *i == prs->poi[*j][1])
		{
			(*i)++;
			tkn->type = prs->poi[(*j)++][0];
			break ;
		}
		if (temp[*i] == ' ' || temp[*i] == '\t' || temp[*i] == '\0')
			break ;
		(*i)++;
	}
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
		tkn = token_malloc(msh);
		while (prs->modified[i] == ' ' || prs->modified[i] == '\t')
			i++;
		tkn->start_pos = i;
		token_end(prs, &i, &j, tkn);
		tkn->end_pos = i - 1;
		copy_text(msh, prs, tkn);
		addnode((void *)tkn, (void **)&prs->head, offsetof(t_token, next), \
			offsetof(t_token, prev));
	}
}
