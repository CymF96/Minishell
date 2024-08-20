/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:33:13 by mcoskune          #+#    #+#             */
/*   Updated: 2024/08/20 16:10:01 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	handle_dollars(t_msh *msh, char *str, int *i , int flag)
{
	char	*dol;
	
}

static void	handle_dqt_dollars(t_msh *msh, char *str, int *i)
{
	int	j;

	j = *i;
	while (str[j] != '\"')
	{
		if (str[j] == '\0')
			return ;
		j++;
	}
	while (*i < j)
	{
		if (str[*i] == '$')
			handle_dollars(msh, str, i, 1);
		(*i)++;
	}
	*i = j + 1;
}

void	expand_dollars(t_msh *msh, t_parse *pars, int flag)
{
	int		i;
	t_token	*temp;

	temp = pars->head;
	while (temp != NULL)
	{
		i = 0;
		while (temp->token[i] != '\0')
		{
			if (flag == 1 && (temp->token[i] == '\'' || temp->token[i] == '\"'))
				handle_quotes(temp->token, &i);
			else if (flag == 0 && temp->token[i] == '\"')
				handle_dqt_dollars(msh, temp->token, &i);
			else if (flag == 0 && temp->token[i] == '\'')
				handle_quotes(temp->token, &i);
			else if (temp->token[i] == '$')
				handle_dollars(msh, temp->token, &i, 0);
			i++;
		}
	}
}
