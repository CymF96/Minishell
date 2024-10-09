/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 15:25:00 by mcoskune          #+#    #+#             */
/*   Updated: 2024/10/09 15:38:30 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// valgrind --suppressions=./OTHER/debugging/rl.supp --leak-check=full --show-
//leak-kinds=all --track-origins=yes --verbose 
//--log-file=valgrind-out.txt ./minishell

static int	check_something_exists(t_msh *msh, int *i, t_type tye)
{
	int		j;
	t_type	type;

	if (tye == HEREDOC || tye == APPEND)
		*i += 2;
	else
		(*i)++;
	j = *i;
	while (msh->input[j] != '\0')
	{
		type = check_special(msh->input, &j);
		if (msh->input[j] == ' ' && msh->input[j] == '\t')
		{
			j++;
			continue ;
		}
		else if (type != REGULAR && type != DOLLAR && \
				type != S_QT && type != D_QT)
			return (1);
		else if (type == REGULAR)
			return (0);
		j++;
	}
	return (1);
}

void	request_more_input(t_msh *msh, t_parse *pars)
{
	char	*gnl_temp;
	int		i;
	char	*temp;

	clean_init_parse(pars);
	i = write (1, "> ", 2);
	(void) i;
	temp = get_next_line(STDIN_FILENO);
	gnl_temp = ft_strjoin(" ", temp);
	free(temp);
	msh->text = ft_strjoin(msh->input, gnl_temp);
	free (gnl_temp);
	free (msh->input);
	msh->input = msh->text;
	msh->text = NULL;
}

int	analyse_input(t_msh *msh, t_parse *pars)
{
	int		i;
	t_type	tye;

	i = -1;
	(void)pars;
	while (msh->input[++i] != '\0')
	{
		tye = check_special(msh->input, &i);
		if (tye == HEREDOC || tye == APPEND || tye == INFILE || \
			tye == OUTFILE || tye == PIPE)
		{
			if (check_something_exists(msh, &i, tye) != 0)
				return (1);
			i--;
		}
		else if (tye == D_QT || tye == S_QT)
		{
			if (check_quote_ending(msh->input, i) == -1)
				return (2);
			i = check_quote_ending(msh->input, i);
		}
	}
	return (0);
}

int	parse_main(t_msh *msh)
{
	int	flag;

	if (msh == NULL || msh->input == NULL || msh->input[0] == '\0')
		return (1);
	parse_malloc(msh);
	flag = analyse_input(msh, msh->parse);
	if (flag == 1)
		return (1);
	while (1)
	{
		if (msh->parse->l_count == msh->parse->r_count && flag == 0)
			break ;
		if (flag == 1)
			return (1);
		request_more_input(msh, msh->parse);
		flag = analyse_input(msh, msh->parse);
	}
	if (create_modified(msh, msh->parse) == 1)
		return (1);
	if (handle_wilds(msh, msh->parse) == 1)
		return (1);
	// printf("Modified string is: %s\n", msh->parse->modified);
	
	parse_tokenize(msh, msh->parse);

	
	// t_token	*tkn = msh->parse->head;
	// while (tkn)
	// {
	// 	int	j = 0;
	// 	while (tkn->token[j] != '\0')
	// 	{
	// 		if (tkn->token[j] == ' ')
	// 			tkn->token[j] = '#';
	// 		j++;
	// 	}
	// 	printf("Token is: %s\n", tkn->token);
	// 	tkn = tkn->next;
	// }


	make_pexe(msh, msh->parse);

	// t_pexe *temp = msh->pexe;
	// while (temp != NULL)
	// {
	// 	int	i = 0;
	// 	while (temp->cmd[i] != '\0')
	// 	{
	// 		if (temp->cmd[i] == ' ')
	// 			temp->cmd[i] = '#';
	// 		i++;
	// 	}
	// 	printf("PEXE-TYPE: %d\n", temp->type);
	// 	printf("PEXE-CMD: %s\n", temp->cmd);
	// 	printf("PEXE-GROUP_ID: %d\n", temp->group_id);
	// 	printf("PEXE-PRIORITY: %d\n", temp->p_index);
	// 	printf("PEXE-MUK_NOTE: %d\n", temp->muk_note);
	// 	printf("PEXE-TEMP: %s\n\n", temp->temp);

	// 	temp = temp->next;
	// }

	return (0);
}