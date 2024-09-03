/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 15:25:00 by mcoskune          #+#    #+#             */
/*   Updated: 2024/09/02 18:26:11 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//valgrind --suppressions=./OTHER/debugging/rl.supp --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt ./minishell

static int	check_something_exists(t_msh *msh, int *i)
{
	int		j;
	t_type	type;

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
	char	*temp;
	char	*gnl_temp;

	clean_init_parse(pars);
	if (msh->text == NULL)
		msh->text = ft_strdup(msh->input);
	else
	{
		temp = msh->text;
		gnl_temp = get_next_line(STDIN_FILENO);
		msh->text = ft_strjoin(temp, gnl_temp);
		free (temp);
		temp = NULL;
		free (gnl_temp);
		free (msh->input);
		msh->input = msh->text;
	}
	analyse_input(msh, pars);
}

int	analyse_input(t_msh *msh, t_parse *pars)
{
	int		i;
	t_type	tye;

	i = 0;
	while (msh->input[i] != '\0')
	{
		tye = check_special(msh->input, &i);
		if (tye == HEREDOC || tye == APPEND || tye == INFILE || \
				tye == OUTFILE || tye == PIPE)
		{
			if (tye == HEREDOC || tye == APPEND)
				i += 2;
			else
				i++;
			if (check_something_exists(msh, &i) != 0)
				return (1);
		}
		else if (tye == D_QT || tye == S_QT)
		{
			if (check_quote_ending(msh->input, i) == -1)
				request_more_input(msh, pars);
			i = check_quote_ending(msh->input, i);
		}
		else if (tye == L_PAR)
			pars->l_count++;
		else if (tye == R_PAR)
			pars->r_count++;
		i++;
	}
	return (0);
}

int	parse_main(t_msh *msh)
{
	int		test;

	if (msh == NULL || msh->input == NULL || msh->input[0] == '\0')
		return (1);
	parse_malloc(msh);
	test = analyse_input(msh, msh->parse);
	if (test == 1)
		return (1);
	while (1)
	{
		if (msh->parse->l_count == msh->parse->r_count)
			break ;
		request_more_input(msh, msh->parse);
	}
	create_modified(msh, msh->parse);
	parse_tokenize(msh, msh->parse);
	make_pexe(msh, msh->parse);
	return (0);
}

