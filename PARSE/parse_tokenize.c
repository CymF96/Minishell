/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokenize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 18:17:56 by mcoskune          #+#    #+#             */
/*   Updated: 2024/08/22 18:16:26 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	copy_text(t_msh *msh, t_token *tkn)
{
	int	i;
	int	j;

	i = tkn->start_pos;
	j = 0;
	tkn->token = malloc(sizeof(tkn->end_pos - tkn->start_pos + 2));
	if (tkn->token == NULL)
		exit_cleanup("Malloc failed", msh, errno);
	while (i <= tkn->end_pos)
	{
		tkn->token[j] = msh->input[i];
		i++;
		j++;
	}
	tkn->token[j] = '\0';
}

void	handle_quotes(char *input, int *i)
{
	int		fl;
	int		j;

	fl = 0;
	if (input[*i] == '\'')
		fl = 1;
	j = *i + 1;
	while (input[j] != '\0')
	{
		if ((fl == 0 && input[j] == '\"') || \
			(fl == 1 && input[j] == '\''))
		{
			*i = j;
			return ;
		}
		j++;
	}
	(*i)++;
}

void	parse_tokenize(t_msh *msh, t_parse *prs)
{
	int		i;
	t_token	*tkn;
	char	*temp;

	i = 0;
	temp = msh->input;
	while (temp[i] != '\0')
	{
		tkn = token_malloc(msh, prs);
		while (msh->input[i] == ' ' || msh->input[i] == '\t')
			i++;
		tkn->start_pos = i;
		while (temp[i] != '\0')
		{
			if (temp[i] == '\'' || temp[i] == '\"')
				handle_quotes(msh->input, &i);
			if (temp[i] == ' ' || temp[i] == '\t')
				break ;
			i++;
		}
		tkn->end_pos = i - 1;
		add_node((void **)&prs->head, (void *)tkn, \
			FIELD_OFFSET(t_token, next), FIELD_OFFSET(t_token, prev));
		copy_text(msh, tkn);
	}
}
