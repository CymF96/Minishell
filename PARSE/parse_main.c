/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 15:25:00 by mcoskune          #+#    #+#             */
/*   Updated: 2024/09/03 17:50:07 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//valgrind --suppressions=./OTHER/debugging/rl.supp --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt ./minishell

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

	clean_init_parse(pars);
	gnl_temp = get_next_line(STDIN_FILENO);
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
	while (msh->input[++i] != '\0')
	{
		tye = check_special(msh->input, &i);
		if (tye == HEREDOC || tye == APPEND || tye == INFILE || \
				tye == OUTFILE || tye == PIPE)
		{
			if (check_something_exists(msh, &i, tye) != 0)
				return (1);
		}
		else if (tye == D_QT || tye == S_QT)
		{
			if (check_quote_ending(msh->input, i) == -1)
				return (2);
			i = check_quote_ending(msh->input, i);
		}
		else if (tye == L_PAR)
			pars->l_count++;
		else if (tye == R_PAR)
			pars->r_count++;
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
	create_modified(msh, msh->parse);
	parse_tokenize(msh, msh->parse);
	make_pexe(msh, msh->parse);
	return (0);
}
